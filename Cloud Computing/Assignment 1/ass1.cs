using System;
using System.Net;
using System.Net.Http;
using System.Text.RegularExpressions;
using System.Collections.Generic;

namespace HTTPGet
{
    // Global Variables
    static class Global
    {
        public static HashSet<string> vistedURIs = new HashSet<string>();
        public static Regex parser = new Regex("(?<=<a href=\")(.*?)(?=\")");
        public static Stack<string> tempURIs = new Stack<string>();
        public static Stack<string> vistedHTML = new Stack<string>();
        public static bool run = true;
    }
    class Program
    {
        //Take care of uri that either trailing fowardslash or doesn't
        static bool trailingCheck(string current)
        {
            if(current[current.Length-1] == '/')
            {
                string temp = current.Substring(0, current.Length - 1);
                if (Global.vistedURIs.Contains(temp))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            else
            {
                string temp = current;
                temp = temp.Insert(temp.Length, "/");
                if (Global.vistedURIs.Contains(temp))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }

        //Goes through the html page and find the next uri
        static string crawl(string htmlContent)
        {
            // only crawl when the its a 200 respond
            Match mat = Global.parser.Match(htmlContent);
            string current = "";
            while (mat.Success)
            {
                current = mat.Value.ToString();
                if (current.Length > 4 && current.Substring(0,4) == "http" && (!Global.vistedURIs.Contains(current)) && trailingCheck(current))
                {

                    Global.vistedURIs.Add(current);
                    Global.tempURIs.Push(current);
                    return current;
                }
                else
                {
                    mat = mat.NextMatch();
                }
            }
            return current;
        }

        static string backTrack()
        {
            if(Global.tempURIs.Count != 0)
            {
                return Global.tempURIs.Pop();
            }
            else
            {
                Global.run = false;
                return "";
            }
        }

        //Main fuction
        static void Main(string[] args)
        {
            if (args.Length != 2)
            {
                Console.WriteLine("Invalid Input");
                return;
            }
            using (var client = new HttpClient(new HttpClientHandler { AutomaticDecompression = DecompressionMethods.GZip | DecompressionMethods.Deflate }))
            {
                string currentURI = args[0];
                int maxHops = Int32.Parse(args[1]);
                Console.WriteLine("Starting URI: " + args[0] + " Max Hops: " + args[1]);
                Global.vistedURIs.Add(currentURI);
                Global.tempURIs.Push(currentURI);
                string nextURI = currentURI;
                while (maxHops >= 0 && Global.run)
                {
                    try
                    {
                        //Visiting website
                        HttpResponseMessage response = client.GetAsync(nextURI).Result;
                        string result = response.Content.ReadAsStringAsync().Result;
                        Global.vistedHTML.Push(result);
                        int status = (int)response.StatusCode;
                        if(status == 200)
                        {
                            // Console.WriteLine(status);
                            currentURI = nextURI;
                            nextURI = crawl(result);
                            if(nextURI == "")
                            {
                                nextURI = backTrack();
                            }
                            Console.WriteLine(maxHops+ " NEXT URL: " + nextURI);
                            maxHops--;
                        }
                        else if (status == 301)
                        {
                            // Console.WriteLine(status);
                            nextURI = backTrack();
                        }
                        else
                        {
                            Console.WriteLine(status);
                            return;
                        }
                    }
                    //404 expections
                    catch (System.AggregateException) 
                    {
                        Console.WriteLine("REDIRECTING");
                        nextURI = backTrack();
                    }
                    
                }

                //Printing out the results
                while (Global.vistedHTML.Count > 0)
                {
                    Console.WriteLine(Global.vistedHTML.Pop());
                }
                foreach (var item in Global.vistedURIs)
                {
                    Console.WriteLine(item);
                }
                
            }
        }
    }
}
