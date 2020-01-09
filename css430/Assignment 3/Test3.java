import java.util.*;

public class Test3 extends Thread
{
    private int tNums;

    public Test3(String [] argv)
    {
        this.tNums = Integer.parseInt(argv[0]);
    }

    public void run()
    {
        Date dateStart = new Date();
        Date dateEnd = new Date();
        
        double start = dateStart.getTime();

        for (int i = 0; i < this.tNums; ++i) {
            SysLib.exec(SysLib.stringToArgs("TestThread3a"));
            SysLib.exec(SysLib.stringToArgs("TestThread3b"));
        }

        for (int j = 0; j < this.tNums * 2; ++j) {
            SysLib.join();
        }

        double end = dateEnd.getTime();

        SysLib.cout("Total Time = " + (end - start) + "ms\n");
        SysLib.exit();
    }
}