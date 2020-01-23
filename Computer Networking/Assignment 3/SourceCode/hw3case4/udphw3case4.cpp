#include "udphw3case4.h"

// Test4: client sliding window (same as test 3 because only the retriever is dropping the packet) -----------------------------------
int udphw3case4::clientSlidingWindow( UdpSocket &sock, const int max, int *message, int windowSize )
{
    //count to keep track of the amount we need to retransmit, 
    //ack - keep track of the amount of already acked sequence #,
    //nonAcked - keep track of the amount of non yet acked sequence #
    int count = 0;
    int acked = 0;
    int nonAcked = 0;
    for (int i = 0; i < max; i++)
    {
        //Timer at the beginning to keep track all transmitted sequence number
        //It will reset everytime we get a new ack
        Timer t;
        t.start(); 
        //Only transmit when below the window size limit
        if(nonAcked < windowSize) 
        {
            message[0] = i; 
            sock.sendTo((char*)message, MSGSIZE); 
            //Keep track of the all our non ack sequence number
            nonAcked++; 
        }
        //Trap state that allow us to wait for the correct ack number
        if(nonAcked == windowSize) //2 == 2
        {
            while(true)
            {
                if (sock.pollRecvFrom() > 0) 
                {
                    //Leave the trap state if get the correct ack number
                    sock.recvFrom((char *) message, MSGSIZE);
                    if (message[0] == acked) 
                    {
                        acked++; 
                        nonAcked--;
                        break;
                    }
                }
                //Time out and collect the amount we need to retransmit
                if(t.lap() > 1500)
                {
                    count = count + (i + windowSize - acked);
                    i = acked; 
                    nonAcked = 0; 
                    continue;
                }
            }
        }
    }
    return count; 
}

// Test4: server sliding window with drop -----------------------------------
void udphw3case4::serverEarlyRetrans(UdpSocket &sock, const int max, int *message, int windowSize, int dropChance) 
{
    //For-loop to match the sequence number of the sender
    for (int i = 0; i < max; i++) 
    {
      //Trapping state to enusre we get the correct corresponading number
        while (true) 
        {
            if (sock.pollRecvFrom() > 0) 
            {
                int chance = rand() % 101;
                //Only drop the packet if we roll the chance lower than the drop chance
                if (dropChance > chance) 
                {
                    continue;
                }
                //This won't excute if we drop because of continue
                //By utltizing continue, we can skip transmitting back
                sock.recvFrom((char *) message, MSGSIZE);
                sock.ackTo((char *) &i, sizeof(i));
                if (message[0] == i) 
                {
                    //Get out of the trap state and move onto the next sequence number
                    break;
                }
            }
        }
    }
}