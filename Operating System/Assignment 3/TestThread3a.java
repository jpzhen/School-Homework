class TestThread3a extends Thread
{
    public TestThread3a()
    {
    }

    @Override
    public void run()
    {
        //Iterative Fibonaci to test
        int ppNum = 0;
        int pNum = 0;
        int currNum = 1;
        for (int i = 1; i < 100000 ; i++) 
        {
            ppNum = pNum;
            pNum = currNum;
            currNum = ppNum + pNum;
        }

        SysLib.cout("Computation Test Finished\n");
		SysLib.exit();
    }
}