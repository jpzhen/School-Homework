#pragma
#include "udphw3.h"

// Test2: client stop and wait message send -----------------------------------
int udphw3:: clientStopWait( UdpSocket &sock, const int max, int *message )
{
    //For loop, using i as our sequence number
    int count = 0;
    for (int i = 0; i < max; i++)
    {
        message[0] = i;
        sock.sendTo((char*)message, MSGSIZE);
        //Move foward if ack is equal to i
        if(sock.pollRecvFrom() > 0)
        {
            sock.recvFrom((char*) message, MSGSIZE);
            //Reset i back if ack does not match
            if(message[0] != i)
            {
                i--;
                count++;
                continue;
            }
        }
        else
        {
            //A incompaitable ack indicate a chance of packet lost
            //So we start the timer
            Timer t;
            t.start();
            while(sock.pollRecvFrom() <= 0)
            {
                if(t.lap() > 1500)
                {
                    break;
                }
            }
            //Only arrive here when there is a time out occurs
            if(t.lap() >= 1500)
            {
                i--;
                count++;
                continue;
            }
        }
    }
    return count;
}

// Test2: server stop and wait message send -----------------------------------
void udphw3:: serverReliable(UdpSocket &sock, const int max, int *message) 
{
    //For-loop to match the sequence number of the sender
    for(int i = 0; i < max; i++)
    {
        //This loop will enscapsulate the function until condition is met
        while(sock.pollRecvFrom() >= 0)
        {
            sock.recvFrom((char *) message, MSGSIZE);
            //Only break out of the loop if the sequence number matches
            if(message[0] == i)
            {
                //Only send back the correct ack
                sock.ackTo((char *) &i, sizeof(i));
                break;
            }
        }
    }
}

// Test3: client sliding window -----------------------------------
int udphw3::clientSlidingWindow( UdpSocket &sock, const int max, int *message, int windowSize )
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
                if(t.lap() > 1500)
                {
                    //collect the current sequence # and window size then rid of all already acknowledged sequence #
                    //start again where the most recent acked sequence number
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

// Test3: server sliding window -----------------------------------
void udphw3::serverEarlyRetrans(UdpSocket &sock, const int max, int *message, int windowSize) 
{
    //For-loop to match the sequence number of the sender
    for(int i = 0; i < max; i++)
    { 
        //Only increment the sequence number if the sequence number matches
        sock.recvFrom((char *) message, MSGSIZE);
        if(message[0] == i)
        {
            sock.ackTo((char *) &i, sizeof(i));
        }
        //Reset i as long the sequence number doesn't match 
        else
        {
            i--;
            sock.ackTo((char *) &i, sizeof(i));
        }
    }
}