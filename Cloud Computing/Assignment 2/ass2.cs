/*
    Jun Zhen
    CSS 436 Cloud Computing
    A program that takes in a city name as an arguement and will consume at least 2 RESTful API to
    make a meaningful report about the city. The program utilize an exponetial backoff
    mechanism when it fails to reach an API endpoint to ensure no crashing.
*/

using System;
using System.Net.Http;
using Newtonsoft.Json;
using System.Threading;
using System.Collections.Generic;

namespace Program
{
    public class ass2
    {
        static void Main(string[] args)
        {
            //Data fields
            string city = System.Web.HttpUtility.UrlPathEncode(args[0]);
            string weatherURI = "http://api.openweathermap.org/";
            string geoURI = "http://geodb-free-service.wirefreethought.com/";

            //Try Catch to ensure failed api requests
            try
            {
                //Requesting Open Weather Map's api to get information regarding to the weather 
                WeatherReport weatherDetails = JsonConvert.DeserializeObject<WeatherReport>(getCityInfo(city,"", weatherURI, 2));
                Console.WriteLine("Weather Report of " + weatherDetails.name + " " + weatherDetails.sys.country);
                Console.WriteLine("      Coordinates: " + weatherDetails.coord.lat + ", " + weatherDetails.coord.lon);
                Console.WriteLine("      Weather: " + weatherDetails.weather[0].description);
                Console.WriteLine("      Temperature: " + ((int) ((weatherDetails.main.temp - 273.15) * 1.8 + 32)) + " degrees Fahrenhit");
                Console.WriteLine("      Feels Like: " + ((int) ((weatherDetails.main.feels_like - 273.15) * 1.8 + 32)) + " degrees Fahrenhit");
                Console.WriteLine("      Humidity: " + weatherDetails.main.humidity + "%");
                Console.WriteLine("      Wind Speed: " + weatherDetails.wind.speed);
		
    		//Requesting the GeoDB's API to the city's details
                RootObject cityDetails = JsonConvert.DeserializeObject<RootObject>(getCityInfo(city,"", geoURI, 0));
                CityInfo cityInfo = cityDetails.data[0];
                
                string latlon = getCoords(cityInfo);
                NearByCitiesList cityList = JsonConvert.DeserializeObject<NearByCitiesList>(getCityInfo(city, latlon, geoURI,1));
                Console.WriteLine("Cities Near By " + weatherDetails.name + " " + weatherDetails.sys.country);
                for (int i = 1; i < cityList.data.Count; i++)
                {
                    Console.WriteLine("      City " + i + ": " + cityList.data[i].name + " " + cityList.data[i].countryCode + ", distance from " + weatherDetails.name + " " + weatherDetails.sys.country + ": " + cityList.data[i].distance + " miles");
                }
                Console.WriteLine("");
            }
            catch (Newtonsoft.Json.JsonReaderException)
            {
                Console.WriteLine("NO DATA RETURN");
            }
            catch (System.NullReferenceException)
            {
                Console.WriteLine("NO DATA RETURN");
            }
        }
        
	// Return the full coordinates a city
        static string getCoords(CityInfo c)
        {
            string s = "";
            string latlon = "";
            if(c.longitude > 0)
                latlon = c.latitude.ToString(s) + "+" + c.longitude.ToString(s);
            else
                latlon = c.latitude.ToString(s) + c.longitude.ToString(s);
            return latlon;
        }

	// Return the result after an api call. Depending on the api number paramter,
	// it will return either OpenWeather or GeoDB results
        static string getCityInfo(string cityName, string coords, string uri, int apiNum)
        {
            int status = 0;
            for (int i = 0; i < 5; i++)
            {
                HttpClient client = new HttpClient();
                client.BaseAddress = new Uri(uri);
                HttpResponseMessage response = new HttpResponseMessage();
                int waitTimer = 1;
                string results = "";
                // Call the city information API
                if (apiNum == 0)
                {
                    response = client.GetAsync("v1/geo/cities?namePrefix=" + cityName).Result;
                    results = response.Content.ReadAsStringAsync().Result;
                }
                // Call the nearby cities API
                else if (apiNum == 1)
                {
                    response = client.GetAsync("v1/geo/locations/" + coords + "/nearbyCities?limit=5&offset=0&radius=100").Result;
                    results = response.Content.ReadAsStringAsync().Result;
                }
                // Call the weather API
                else if (apiNum == 2)
                {
                    response = client.GetAsync("data/2.5/weather?q=" + cityName + "&APPID=yourkey").Result;
                    results = response.Content.ReadAsStringAsync().Result;
                }
                status = (int)response.StatusCode;
                if (status == 200)
                {
                    return results;
                }
                else
                {
                    waitTimer = backOff(waitTimer);
                }
            }
            Console.WriteLine(status + " FAILED API CALL AT: " + uri);
            return "NULL";
        }

	// Return the total time waited, will put process to sleep
	// if the HTTP request is not 200
        static int backOff(int time)
        {
            if(time > 30000)
            {
                return 0;
            }
            Thread.Sleep(time);
            Random rnd = new Random();
            time *= 2;
            time += rnd.Next(500);
            return time;
        }
    }
}

// ----- Near By Cities ------
public class NearByCities
{
    public int id { get; set; }
    public string wikiDataId { get; set; }
    public string type { get; set; }
    public string city { get; set; }
    public string name { get; set; }
    public string country { get; set; }
    public string countryCode { get; set; }
    public string region { get; set; }
    public string regionCode { get; set; }
    public double latitude { get; set; }
    public double longitude { get; set; }
    public double distance { get; set; }
}

public class Link
{
    public string rel { get; set; }
    public string href { get; set; }
}

public class NearByCitiesList
{
    public List<NearByCities> data { get; set; }
    public List<Link> links { get; set; }
    public Metadata metadata { get; set; }
}


// ----- GeoDB ------
public class CityInfo
{
    public int id { get; set; }
    public string wikiDataId { get; set; }
    public string type { get; set; }
    public string city { get; set; }
    public string name { get; set; }
    public string country { get; set; }
    public string countryCode { get; set; }
    public string region { get; set; }
    public string regionCode { get; set; }
    public double latitude { get; set; }
    public double longitude { get; set; }
}

public class Metadata
{
    public int currentOffset { get; set; }
    public int totalCount { get; set; }
}

public class RootObject
{
    public List<CityInfo> data { get; set; }
    public Metadata metadata { get; set; }
}


// ----- openweatherapi ------

public class Coord
{
    public double lon { get; set; }
    public double lat { get; set; }
}

public class Weather
{
    public int id { get; set; }
    public string main { get; set; }
    public string description { get; set; }
    public string icon { get; set; }
}

public class Main
{
    public double temp { get; set; }
    public double feels_like { get; set; }
    public double temp_min { get; set; }
    public double temp_max { get; set; }
    public int pressure { get; set; }
    public int humidity { get; set; }
}

public class Wind
{
    public double speed { get; set; }
    public int deg { get; set; }
}

public class Rain
{
    public double __invalid_name__1h { get; set; }
}

public class Clouds
{
    public int all { get; set; }
}

public class Sys
{
    public int type { get; set; }
    public int id { get; set; }
    public string country { get; set; }
    public int sunrise { get; set; }
    public int sunset { get; set; }
}

public class WeatherReport
{
    public Coord coord { get; set; }
    public List<Weather> weather { get; set; }
    public string @base { get; set; }
    public Main main { get; set; }
    public int visibility { get; set; }
    public Wind wind { get; set; }
    public Rain rain { get; set; }
    public Clouds clouds { get; set; }
    public int dt { get; set; }
    public Sys sys { get; set; }
    public int timezone { get; set; }
    public int id { get; set; }
    public string name { get; set; }
    public int cod { get; set; }
}

    
