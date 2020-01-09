import java.util.*;
public class QueueNode
{
    private Vector<Integer> tidQueue;

    public QueueNode()
    {
        this.tidQueue = new Vector<Integer>();
    }
    
    public synchronized int sleep() 
    {
        if(this.tidQueue.isEmpty())
        {
            try 
            {
                this.wait();
            }
            catch (InterruptedException e)
            {
                SysLib.cerr("ERROR at QueueNode\n");
            }

        }
        return this.tidQueue.remove(0);
    }

    public synchronized void wakeup(int tid)
    {
        this.tidQueue.add(tid);
        this.notify();
    }
}