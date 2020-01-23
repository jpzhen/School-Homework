//Jun Zhen
//CSS432
//HW2
//10-24-2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <iostream>
using namespace std;

//Global variables
const int BUFFSIZE = 1024;
const  char* FILENAME; 
int PORT;
char* SERVERIP;

//HTTP respond in ASCII
//Return false if its not an OK reply
//200 Ok = 146
//400 Bad Request = 148
//401 Unauthorized = 149
//403 Forbidden = 151
//404 Not Found = 152
bool processCode(int code)
{
    if(code == 146)
        return true;
    else
        return false;        
}

//Takes in the client's socket. Send out the request and recv the reply
//If it is a Ok reply then open a file and right to it
bool sendRequest(int fileDesc)
{
    //Setting up the HTTP send message
    char sendM[BUFFSIZE] = {0};
    char recvM[BUFFSIZE] = {0};
    snprintf(sendM, BUFFSIZE, "GET %s " "HTTP/1.1\r\n" "HOST: %s \r\n\r\n", FILENAME, SERVERIP);
    printf("---------------------------------------\n");
    printf("%s", sendM);
    
    //Send is sucessful then wait for a respond
    if( send(fileDesc, sendM, strlen(sendM), 0) > 0 )
    {
        recv(fileDesc, recvM, BUFFSIZE, 0);
        int code = recvM[9] + recvM[10] + recvM[11];
        printf("Return Message: %s", recvM);
        //Only write to file if respond was an OK respond
        if(processCode(code))
        {
            string fn = FILENAME;
            const char* writeFILENAME = fn.substr(1,fn.length()).c_str();
            FILE * fptr = fopen(writeFILENAME, "w");
            if(fptr != NULL)
            {
                //fgets(recvM, strlen(recvM), fptr);
                fputs(recvM, fptr);
                fclose(fptr);
                return true;
            }
            return false;
        }
    }
    else
    {
        printf("ERROR AT WRITE\n");
        return false;
    }
    close(fileDesc);
}

//Setup the socket and establish connection
int main(int argc, char **argv) {
    //Arguments from commandline
    FILENAME = argv[2]; 
    PORT = atoi(argv[3]);
    SERVERIP = argv[1];
  
    //Setting up the data structures and variables
    struct hostent* host = gethostbyname(SERVERIP);
    struct sockaddr_in sendSockAddr;
    bzero((char*)& sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr( inet_ntoa( *(struct in_addr*)*host->h_addr_list ));
    sendSockAddr.sin_port = htons(PORT);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    //Establish the connection with server
    if(connect(clientSd, (sockaddr*)&sendSockAddr,sizeof(sendSockAddr)))
    {
        perror("ERROR on connect\n");
        exit(1);
    }

    //Sending the requets
    if(sendRequest(clientSd))
    {
        printf("Request Sucess\n\n");
        printf("---------------------------------------\n");
    }
    else
    {
        printf("Request Fail\n\n");
        printf("---------------------------------------\n");
    }
    return 0;
}