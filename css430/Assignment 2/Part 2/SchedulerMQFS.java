import java.util.*;

public class Scheduler extends Thread
{
	//Vector Array to hold the 3 queues
    private Vector [] queues;
    private int timeSlice;
    private static final int DEFAULT_TIME_SLICE = 1000;

    // New data added to p161 
    private boolean[] tids; // Indicate which ids have been used
    private static final int DEFAULT_MAX_THREADS = 10000;

    // A new feature added to p161 
    // Allocate an ID array, each element indicating if that id has been used
    private int nextId = 0;
    private void initTid( int maxThreads ) 
	{
		tids = new boolean[maxThreads];
		for ( int i = 0; i < maxThreads; i++ )
			tids[i] = false;
    }

    // A new feature added to p161 
    // Search an available thread ID and provide a new thread with this ID
    private int getNewTid( ) 
	{
		for ( int i = 0; i < tids.length; i++ ) 
		{
			int tentative = ( nextId + i ) % tids.length;
			if ( tids[tentative] == false ) 
			{
				tids[tentative] = true;
				nextId = ( tentative + 1 ) % tids.length;
				return tentative;
			}
		}
		return -1;
    }

    // A new feature added to p161 
    // Return the thread ID and set the corresponding tids element to be unused
    private boolean returnTid( int tid ) 
	{
		if ( tid >= 0 && tid < tids.length && tids[tid] == true )
		{
			tids[tid] = false;
			return true;
		}
		return false;
    }

    // A new feature added to p161 
    // Retrieve the current thread's TCB from the queue
    public TCB getMyTcb( ) 
	{
		Thread myThread = Thread.currentThread( ); // Get my thread object
		for (int i = 0; i < queues.length; i++)
		{
			synchronized( queues[i] )
			{
				for ( int j = 0; j < queues[i].size( ); j++ ) 
				{
					TCB tcb = ( TCB )queues[i].elementAt( j );
					Thread thread = tcb.getThread( );
					if ( thread == myThread ) // if this is my TCB, return it
						return tcb;
				}
			}
		}
		return null;
    }

    // A new feature added to p161 
    // Return the maximal number of threads to be spawned in the system
    public int getMaxThreads( ) 
	{
		return tids.length;
    }

	private void makeQueues()
	{
		queues = new Vector[3];
		for (int i = 0; i < queues.length; i++) {
			queues[i] = new Vector();
		}
	}

	//When Scheduler get initalize, initalize the 3 queues as well
    public Scheduler( ) 
	{
		timeSlice = DEFAULT_TIME_SLICE;
		makeQueues();
		initTid( DEFAULT_MAX_THREADS );
    }

    public Scheduler( int quantum ) 
	{
		timeSlice = quantum;
		makeQueues();
		initTid( DEFAULT_MAX_THREADS );
    }

    // A new feature added to p161 
    // A constructor to receive the max number of threads to be spawned
    public Scheduler( int quantum, int maxThreads ) 
	{
		timeSlice = quantum;
		makeQueues();
		initTid( maxThreads );
    }

	//Queue 1 Quantum: 500ms, Queue 1 Quantum: 1000ms, Queue 1 Quantum: 2000ms
    private void schedulerSleep( ) 
	{
		try 
		{
			if (queues[0].size() != 0) 
			{
				Thread.sleep(timeSlice / 2);
			}
			else if (queues[1].size() != 0)
			{
		 		Thread.sleep(timeSlice);
			}
			else 
			{
				Thread.sleep(timeSlice * 2);
			}
		} 
		catch ( InterruptedException e ) 
		{
		}
    }

    // A modified addThread of p161 example
    public TCB addThread( Thread t ) 
	{
		TCB parentTcb = getMyTcb( ); // get my TCB and find my TID
		int pid = ( parentTcb != null ) ? parentTcb.getTid( ) : -1;
		int tid = getNewTid( ); // get a new TID
		if ( tid == -1)
			return null;
		TCB tcb = new TCB( t, tid, pid ); // create a new TCB
		queues[0].add( tcb );
		return tcb;
    }

    // A new feature added to p161
    // Removing the TCB of a terminating thread
    public boolean deleteThread( ) 
	{
		TCB tcb = getMyTcb( ); 
		if ( tcb!= null )
			return tcb.setTerminated( );
		else
			return false;
    }

	public void sleepThread( int milliseconds ) 
	{
		try 
		{
			sleep( milliseconds );
		} 
		catch ( InterruptedException e ) { }
    }
    
    // A modified run of p161
	public void run( ) 
	{
		Thread current = null;
		while ( true ) 
		{
			try
			{
				//Checking if queues are empty
				if(queues[0].size() == 0 && queues[1].size() == 0 && queues[2].size() == 0) 
				{
					continue;
				}
				//If queue 1 is not empty then execute threads with 500ms
				if (!queues[0].isEmpty())
				{
					TCB currentTCB = (TCB) queues[0].firstElement();
					if (currentTCB.getTerminated())
					{
						queues[0].remove(currentTCB);
						returnTid(currentTCB.getTid());
						continue;
					}
					current = currentTCB.getThread();
					if (current != null)
					{
						if (current.isAlive()) 
						{
							current.resume();
						}
						else
						{
							current.start();
						} 
					}
					schedulerSleep();
					synchronized (queues[0])
					{
						if (current != null && current.isAlive())
						{
							current.suspend();
						}
						//
						queues[0].remove(currentTCB);
						queues[1].add(currentTCB);
					}
				}
				//If queue 1 is empty and queue 2 is not then execute threads with 1000ms
				if (queues[1].size() != 0 && queues[0].isEmpty())
				{
					TCB currentTCB = (TCB) queues[1].firstElement();
					if (currentTCB.getTerminated())
					{
						queues[1].remove(currentTCB);
						returnTid(currentTCB.getTid());
						continue;
					}
					current = currentTCB.getThread();
					if (current != null)
					{
						if (current.isAlive())
						{
							current.resume();
						}
						else
						{
							current.start();
						}
					}
					schedulerSleep();
					synchronized (queues[1])
					{
						if (current != null && current.isAlive())
						{
							current.suspend();
						}
						queues[1].remove(currentTCB);
						queues[2].add(currentTCB);
					}
				} 
				//Both queue 1 and 2 are empty, execute last threads with 2000ms 
				else
				{
					TCB currentTCB = (TCB) queues[2].firstElement();
					if (currentTCB.getTerminated())
					{
						queues[2].remove(currentTCB);
						returnTid(currentTCB.getTid());
						continue;
					}
					current = currentTCB.getThread();
					if (current != null)
					{
						if (current.isAlive()) 
						{
							current.resume();
						}
						else
						{
							current.start();
						} 
					}
					schedulerSleep();
					synchronized (queues[2])
					{
						if (current != null && current.isAlive())
						{
							current.suspend();
						}
						queues[2].remove(currentTCB);
						queues[2].add(currentTCB);
					}
				} 
			} catch ( NullPointerException e3 ) { };
		}
    }
}