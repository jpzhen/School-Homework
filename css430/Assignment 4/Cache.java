import java.util.Vector;

//Cache class to simulate the behavior of how main memory interact with secondary
//to improve memory access by incorperating with enchacned seconad change algorithm
public class Cache
{
    //Data Fields
    private int blockSize;
    private int victimPage;
    private Vector<Page> cachePage; //Vector to hold all our pages

    //Cache Constructor
    public Cache(int blockSize, int cacheBlocks)
    {
        this.blockSize = blockSize;
        victimPage = 0;
        cachePage = new Vector<Page>(cacheBlocks);
        for (int i = 0; i < cacheBlocks; i++) 
        {
            Page temp = new Page(blockSize);
            this.cachePage.add(temp);
        }
    }
    
    //Page struct/class to hold all the unqiue values such as reference bits and dirty bits
    private class Page 
    {
        //begin at -1 indicate it is empty
        public int blockNum = -1;
        //Store the data of the page
        public byte [] pageData;
        //Used to deter if page should be swapped or not
        public boolean refBit = false;
        public boolean dirtyBit = false;
        
        //Constructor
        public Page(int size) {
            pageData = new byte[size];
            blockNum = -1;
            refBit = false;
            dirtyBit = false;
        }
    }
    
    //This method will read into the buffer and look for the specified block id from the second memory.
    // If it found the block, then it will return true otherwise false which mean it is a page fault.
    public synchronized boolean read(int blockId, byte buffer[])
    {
        //loop through the all the pages to a match to our paramter
        for (int i = 0; i < cachePage.size(); i++) 
        {
            if(cachePage.get(i).blockNum == blockId)
            {
                System.arraycopy(cachePage.get(i).pageData, 0, buffer, 0, blockSize);
                cachePage.get(i).refBit = true;
                return true;
            }    
        }

        //check for empty pages
        for (int i = 0; i < cachePage.size(); i++) 
        {
            if(cachePage.get(i).blockNum == -1)
            {
                SysLib.rawread(blockId, cachePage.get(i).pageData);
                System.arraycopy(cachePage.get(i).pageData, 0, buffer, 0, blockSize);
                cachePage.get(i).refBit = true;
                cachePage.get(i).blockNum = blockId;
                return true;
            }
        }
        
        
        int vict = findVictim();
        if( (cachePage.get(vict).dirtyBit == true) && (cachePage.get(vict).blockNum != -1) )
        {
			SysLib.rawwrite(cachePage.get(vict).blockNum, cachePage.get(vict).pageData);
            cachePage.get(vict).dirtyBit = false;
        }

        SysLib.rawread(blockId, buffer);
		System.arraycopy(cachePage.get(vict).pageData, 0, buffer, 0, blockSize);
        cachePage.get(vict).refBit = true;
        cachePage.get(vict).blockNum = blockId;
		return true;
    }

    //find the index of a page that is ready to be swapped out
    private int findVictim()
    {
        //infite loop until we find a good match page
        while(true)
        {
            //loop through the pages and check each pages' reference bit and dirty bit
            for (int i = 1; i < cachePage.size(); i++) 
            {
                int victIndex = (victimPage + i) % this.cachePage.size();
                if( (cachePage.get(victIndex).refBit == false) && (cachePage.get(victIndex).dirtyBit == false) )
                {
                    return victIndex;
                }
            }

            for (int i = 1; i < cachePage.size(); i++) 
            {
                int victIndex = (victimPage + i) % this.cachePage.size();
                if ( (cachePage.get(victIndex).refBit == false) && (cachePage.get(victIndex).dirtyBit) )
				{
					if (cachePage.get(victIndex).dirtyBit == true) 
					{
						return victIndex;
					}
				}
				cachePage.get(victIndex).refBit = false;
            }
        }
    }
    //This method will search for the specific spots in the secondary memory and write data into it. 
    public synchronized boolean write(int blockId, byte buffer[])
    {
        //loop through the all the pages to a match to our paramter
        for (int i = 0; i < cachePage.size(); i++) {
            if (cachePage.get(i).blockNum == blockId) {
                System.arraycopy(buffer, 0, cachePage.get(i).pageData, 0, blockSize);
                cachePage.get(i).refBit = true;
                cachePage.get(i).dirtyBit = true;
                return true;
            }
        }
        for (int i = 0; i < cachePage.size(); i++)  { 
            if (cachePage.get(i).blockNum == -1)  {
                System.arraycopy(buffer, 0, cachePage.get(i).pageData, 0, blockSize);
                cachePage.get(i).refBit = true;
                cachePage.get(i).blockNum = blockId;
                cachePage.get(i).dirtyBit = true;
                return true;
            }
        }
        //If we get to here then it means main memory are full, thus we need to swap out a page 
        int vict = findVictim();
        Page page = cachePage.get(vict);
        if (page.dirtyBit == true)
        {
            SysLib.rawwrite(cachePage.get(vict).blockNum, cachePage.get(vict).pageData);
        }
        System.arraycopy(buffer, 0, cachePage.get(vict).pageData, 0, blockSize);
        cachePage.get(vict).blockNum = blockId;
        cachePage.get(vict).refBit = true;
        cachePage.get(vict).dirtyBit = true;
        return false;
    }
    
    //Write data to disk, invoke right before shutting down
    public synchronized void sync()
    {
        for (int i = 0; i < cachePage.size(); i++)   
        {
            if( (cachePage.get(i).dirtyBit == true) && (cachePage.get(i).blockNum != -1) )
            {
                SysLib.rawwrite(cachePage.get(i).blockNum, cachePage.get(i).pageData);
                cachePage.get(i).dirtyBit = false;
            }
        }
        SysLib.sync();
    }

    //Clean up the copies of block. use for testinng performance
    public synchronized void flush()
    {
        for (int i = 0; i < cachePage.size(); i++) 
        {
            if( (cachePage.get(i).dirtyBit == true) && (cachePage.get(i).blockNum != -1) )
            {
                SysLib.rawwrite(cachePage.get(i).blockNum, cachePage.get(i).pageData);
                cachePage.get(i).dirtyBit = false;
            }
            cachePage.get(i).refBit = false;
            cachePage.get(i).blockNum = -1;
        }
        SysLib.sync();
    }

}