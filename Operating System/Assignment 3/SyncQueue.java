import java.util.*;

public class SyncQueue
{
    private Vector<QueueNode> tQueue;
    private final int MAXSIZE = 10;

    public SyncQueue()
    {
        tQueue = new Vector<QueueNode>(MAXSIZE);
        
        for (int i = 0; i < MAXSIZE; i++) 
        {
            QueueNode tempNode = new QueueNode();
            this.tQueue.add(i,tempNode);
        }
    }

    public SyncQueue(int max)
    {
        tQueue = new Vector<QueueNode>(max);
        for (int i = 0; i < max; i++) 
        {
            QueueNode tempNode = new QueueNode();
            this.tQueue.add(i,tempNode);
        }
    }

    public int enqueueAndSleep(int condi)
    {
        return this.tQueue.get(condi).sleep();
    }

    public void dequeueAndWakeup(int condi)
    {
        this.dequeueAndWakeup(condi, 0);
    }

    public void dequeueAndWakeup(int condi, int tid)
    {
        this.tQueue.get(condi).wakeup(tid);
    }

}