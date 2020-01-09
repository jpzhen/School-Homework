class TestThread3b extends Thread
{
    public TestThread3b()
    {
    }

    @Override
    public void run()
    {
        byte[] buff = new byte[512];

        for (int i = 0; i < 500; i++) {
			SysLib.rawread(i, buff);
		}

		for (int i = 0; i < 500; i++) {
			SysLib.rawwrite(i, buff);
		}
		
        SysLib.cout("Disk Test Finished\n");
		SysLib.exit();
    }
}