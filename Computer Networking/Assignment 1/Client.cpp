//Jun Zhen
//CSS432
//HW1 
//10-11-2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main(int argc, char **argv) {
    //Arguments from commandline
    int PORT = atoi(argv[1]);
    int repetition = atoi(argv[2]);
    int NBUFF = atoi(argv[3]);
    int BUFFSIZE = atoi(argv[4]);
    char* serveIp = argv[5];
    int type = atoi(argv[6]);
  
    
    //Establish the connection with server
    struct hostent* host = gethostbyname(argv[5]);
    struct sockaddr_in sendSockAddr;
    bzero((char*)& sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr( inet_ntoa( *(struct in_addr*)*host->h_addr_list ));
    sendSockAddr.sin_port = htons(PORT);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    if(connect(clientSd, (sockaddr*)&sendSockAddr,sizeof(sendSockAddr)))
    {
        perror("ERROR on connect");
        exit(1);
    }

    //Once connection establish, marking the time of transmittion
    struct timeval begin, lap, finish;
    gettimeofday(&begin, NULL);
    char buffer [NBUFF][BUFFSIZE];

    //Using loop to write big amount of data. Depending on the argument, 
    //it will use different method of writing to the server
    for(int i = 0; i <= repetition; i++)
    {
        if(type == 1)
        {
            for ( int j = 0; j < NBUFF; j++ )
            {
                write(clientSd, buffer[j], sizeof(buffer[j]));
            }
        }
        else if(type == 2)
        {
            struct iovec vector[NBUFF];
            for ( int j = 0; j < NBUFF; j++ ) 
            {
                vector[j].iov_base = buffer[j];
                vector[j].iov_len = BUFFSIZE;
            }
            writev(clientSd, vector, NBUFF);
        }
        else if(type == 3)
        {
             write(clientSd, buffer, NBUFF *BUFFSIZE);
        } 
        else
        {
            printf("ERROR on Input\n");
            exit(-1);
        }
    }
    //Record the time of writing
    gettimeofday(&lap, NULL);

    //Server writing back and record the time
    int n;
    read(clientSd,&n,sizeof(int));    
    gettimeofday(&finish, NULL);

    //Formatting the output
    long lapn = (lap.tv_sec - begin.tv_sec) * 1000000 + lap.tv_usec - begin.tv_usec;
    long finishn = (finish.tv_sec - begin.tv_sec) * 1000000 + finish.tv_usec - begin.tv_usec;
    
    printf("Type: %d Lap: %d Finish: %d ",type,lapn,finishn);
    printf("Time Server Read: %d\n",n);
    return 0;
}