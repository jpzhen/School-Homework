//Jun Zhen
//CSS432
//HW1 
//10-11-2019

#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <unistd.h> 
#include <string.h>
#include <netinet/tcp.h> 
#include <stdio.h> 
#include <sys/uio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <errno.h> 

//Global variables for the thread function
const int BUFFSIZE = 1500;
int repetition;

//Takes in a void pointer to the File Descriptor, 
//the function's argument is where we will read and write the data to/from
void* action(void* args)
{
    //Casting the void pointer back to int pointer so we can deference to get the file descriptor
    int* sockPtr = (int*) args;
    char buffer[BUFFSIZE];
    int count = 0;

    //Marking the amount of time to read the batch of data
    struct timeval timer, endTimer;
    gettimeofday(&timer, NULL);
    for ( int i = 0; i <= repetition; i++ )
    {
        //This loop is to ensure we read all the data from client
        for ( int numberRead = 0;
            (numberRead += read(*sockPtr , buffer , BUFFSIZE - numberRead)) < BUFFSIZE; 
            ++count);
        count++;
    }
    //Formating the time
    gettimeofday(&endTimer,NULL);
    long a = (endTimer.tv_sec - timer.tv_sec) * 1000000 + endTimer.tv_usec - timer.tv_usec;

    //Write back to client and print out information
    write(*sockPtr, &count , sizeof(int));
    printf("Amount read: %d\n",count);
    printf("Lap-trip time: %d\n", a);
    close(*sockPtr);
}

int main(int argc, char **argv)
{
    //Setting up the server 
    repetition = atoi(argv[2]);
    int on = 1;
    int serSock, cliSock;
    struct sockaddr_in server, client;
    if((serSock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error at Socket");
        exit(-1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 0);

    //Request the OS to release the socket once program finish running
    setsockopt(serSock, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(int));
    if( bind(serSock,(struct sockaddr*)&server, sizeof(server)) == -1)
    {
        perror("Error at Bind");
        exit(-1);
    }
    socklen_t len = sizeof(client);

    //Infinite loop because we want the server to continue to serve any client coming in 
    while(1)
    {
        if((listen(serSock,5)) == -1)
        {
            perror("Error at Listen");
            exit(-1);
        }
        printf("Listening\n");
        if((cliSock = accept(serSock,(struct sockaddr*)&client, &len)) == -1)
        {
            perror("Error at Accept");
            exit(-1);
        }
        printf("Connected to: %s\n",inet_ntoa(client.sin_addr));

        //Create a new thread per client conncted to the server
        //The program will wait until all the threads finish excuting before closing
        pthread_t newthread;
        if((pthread_create(&newthread, NULL, action, &cliSock)) < 0)
        {
            perror("Error at pThread");
            exit(-1);
        };
        pthread_join(newthread, NULL);
        printf("\n");
    }
    return 0;
}
