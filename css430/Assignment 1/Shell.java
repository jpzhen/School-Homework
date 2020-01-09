/* Jun Zhen
    CSS430
    Shell.java
*/
import java.util.*;

public class Shell extends Thread
{
    //Default Constructor
    public Shell()
    {
    }
    
    //Run method from thread
    public void run() 
    {
        int count = 1;
        while (true) 
        {
            //Hold the user's input
            StringBuffer input = new StringBuffer();
            SysLib.cout("Shell[" + count + "]% ");
            count++;
            SysLib.cin(input);

            //Parse the data if there is a semicolon
            for (String parse1 : input.toString().split(";")) 
            {
                //List to keep track all the threads
                List<Integer> list = new Vector<Integer>();
                //Parse the data if there is an ampersand
                for(String parse2 : parse1.split("&"))
                {
                    //Put the data into an array for execution
                    String [] commands = SysLib.stringToArgs(parse2);

                    //If process successfully spawned then put it's id into the list.
                    int tid = SysLib.exec(commands);
                    if(tid != -3) 
                    {
                        list.add(tid);
                    }
                }
                //Wait for all the threads to finish running before exiting
                while(list.size() > 0)
                {
		            int exists = SysLib.join();
		            int theIndex = list.indexOf(exists);
                    if(theIndex != -1) 
                    {
                        list.remove(theIndex);
                    }
                }
            }
        }        
    }
}
