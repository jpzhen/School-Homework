import java.util.Date;
import java.util.Random;

//Test case to test the performance of cached memory access veruse random memory access
class Test4 extends Thread
{
    //data fields
    private boolean enabled = false;
    private int testNum;
    //Timers
    private long startTime;
    private long endTime;
    //Array to write and ready data
    private byte[] writeBytes;
    private byte[] readBytes;
    //Max size for arrays
    private static final int buffSize = 512;
    private Random rand;
    
    //Constructor to initalize the data fields
    public Test4(final String[] args) 
	{
        
        this.enabled = args[0].equals("-enabled");
        this.testNum = Integer.parseInt(args[1]);
        this.writeBytes = new byte[buffSize];
        this.readBytes = new byte[buffSize];
        this.rand = new Random();
    }

    //If enable we use cread, disable we use rawread
    private void read(int index, byte[] buffer) 
	{
        if (this.enabled) 
		{
            SysLib.cread(index, buffer);
        }
        else 
		{
            SysLib.rawread(index, buffer);
        }
    }
    
    //If enable we use crwite, disable we use rawwarite
    private void write(int index, byte[] buffer) 
	{
        if (this.enabled)
		{
            SysLib.cwrite(index, buffer);
        }
        else
		{
            SysLib.rawwrite(index, buffer);
        }
    }
    
    //Read and write many blocks randomly across the disk
    private void randomAccess() 
	{
        int[] buffer = new int[200];
        for (int i = 0; i < 200; i++)
		{
            buffer[i] = Math.abs(this.rand.nextInt() % buffSize);
        }
		//write data to buffer
        for (int i = 0; i < 200; i++) 
		{

            this.write(buffer[i], this.writeBytes);
        }
        //read data from buffer
        for (int i = 0; i < 200; i++) 
		{
            this.read(buffer[i], this.readBytes);
        }
    }
    
    //read and write a small selection of blocks many times to get a high ratio of cache hits
    private void localizedAccess() 
	{
        for (int i = 0; i < 200; i++) 
		{
            for (int j = 0; j < 10; j++) 
			{
                this.write(j, this.writeBytes);
            }


        }
        for (int i = 0; i < 200; i++)
        {
            for (int j = 0; j < 10; j += 1)
            {
                this.read(j, this.readBytes);
            }
        }
    }
    
    //90% localized accesses and 10%  random accesses
    private void mixedAccess() 
	{
        int[] buffer = new int[200];
        for (int i = 0; i < 200; i++) 
		{
            //If its 90%
            if (Math.abs(this.rand.nextInt() % 10) > 8) 
			{
                buffer[i] = Math.abs(this.rand.nextInt() % buffSize);
            }
            //10%
            else 
			{
                buffer[i] = Math.abs(this.rand.nextInt() % 10);
            }
        }
		//write data to buffer
        for (int i = 0; i < 200; i++) 
		{
            this.write(buffer[i], this.writeBytes);
        }
        //read data from buffer
        for (int i = 0; i < 200; i++) 
		{
            this.read(buffer[i], this.writeBytes);
        }
    }

    //Cause cache enable algorithm
    private void adversaryAccess() 
	{
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < buffSize; j++)
			{
				this.writeBytes[j] = (byte) j;
			}
        }
        for (int i = 0; i < buffSize; i++)
        {
            this.write(i, this.writeBytes);
        }
        for (int i = 0; i < buffSize; i++)
        {
            this.read(i, this.readBytes);
        }
    }

    //Override run function of Thread's run function
    @Override
    //Depending on user input on the commandline, we will print the result gain from
    //runnng our test case. 
    public void run() 
	{
        //Clear out the data to ensure clean performance
        SysLib.flush();
        //Start timer
        this.startTime = new Date().getTime();
        switch(testNum)
        {
            case 1:
                this.randomAccess();
                this.endTime = new Date().getTime();
                if (enabled)
                {
                    SysLib.cout("Test started with " + "Random Accesses" + "\nCache: enabled: \n Execution time: " +
                    (this.endTime - this.startTime) + "\n");
                }
                else
                {
                    SysLib.cout("Test started with " + "Random Accesses" + "\nCache: disabled: \n Execution time: " +
                    (this.endTime - this.startTime) + "\n");
                }
                break;
            case 2:
                this.localizedAccess();
                this.endTime = new Date().getTime();
                if (enabled)
                {
                    SysLib.cout("Test started with " + "Localized Accesses" + "\nCache: enabled: \n Execution time: " +
                    (this.endTime - this.startTime) + "\n");
                }
                else
                {
                    SysLib.cout("Test started with " + "Localized Accesses" + "\nCache: disabled: \n Execution time: " +
                    (this.endTime - this.startTime) + "\n");
                }
                break;
            case 3:
                this.mixedAccess();
                this.endTime = new Date().getTime();
                if (enabled)
                {
                    SysLib.cout("Test started with " + "Mixed Accesses" + "\nCache: enabled: \n Execution time: " +
                    (this.endTime - this.startTime) + "\n");
                }
                else
                {
                    SysLib.cout("Test started with " + "Mixed Accesses" + "\nCache: disabled: \n Execution time: " +
                    (this.endTime - this.startTime) + "\n");
                }
                break;
            case 4:
                this.adversaryAccess();
                this.endTime = new Date().getTime();
                if (enabled)
                    SysLib.cout("Test started with " + "Adversary Accesses" + "\nCache: enabled: \n Execution time: " +
                    (this.endTime - this.startTime) + "\n");
                else
                {
                    SysLib.cout("Test started with " + "Adversary Accesses" + "\nCache: disabled: \n Execution time: " +
                    (this.endTime - this.startTime) + "\n");
                }
                break;
        }
        SysLib.exit();
    }
}