//Jun Zhen
//CSS432
//HW2
//10-25-2019

#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <unistd.h> 
#include <netinet/tcp.h> 
#include <stdio.h> 
#include <sys/uio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <errno.h> 
#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


//Global variables for HTTP responses
const char* HTTP200 = "HTTP/1.1 200 OK\n";
const char* HTTP404 = "HTTP/1.1 404 Not Found\n";
const char* HTTP400 = "HTTP/1.1 400 Bad Request\n";
const char* HTTP401 = "HTTP/1.1 401 Unauthorized\n";
const char* HTTP403 = "HTTP/1.1 403 Forbidden\n";
const int BUFFSIZE = 1500;

//Parse the request and place them into a vector with size of 2
//1. HTTP Request 2. File Name 
bool requestString(int fileDesc, vector<string>& vecStr)
{
    string s = "";
    char buffer[BUFFSIZE];
    if(recv(fileDesc , buffer , BUFFSIZE , 0) < 0)
    {
        printf("ERROR At READ");
        return false;
    }
    int len = strlen(buffer);
    //Read each character one by one to weed out the white space and special characters
    for (int i = 0; i < len; i++)
    {
        if (buffer[i] == ' ')
        {
            vecStr.push_back(s);
            s = "";
        }
        else if ((buffer[i] == '\r' || buffer[i] == '\n'))
        {
            //\r\n\r\n signals the end of request
            if(buffer[i] == 'r' || buffer[i] == '\n')
            {
                vecStr.push_back(s);
                break;
            }
        }
        else
        {
            //Put the string together
            s += buffer[i];
        }
    }
    return true;
}

//This is where we would take the request and respond
bool requestCommand(int fileDesc, vector<string>& requestVector, char* buffer)
{
    string httpReq = requestVector[0];
    string fileReq = requestVector[1];
    cout << httpReq << " " << fileReq << endl;
    //Accepting only GET request 
    if( httpReq == "GET" && fileReq.size() < 20)
    {
        //Check for out of current directory
        if(fileReq.substr(0,2) == "..")
        {
            cout << HTTP403 << endl;
            send(fileDesc, HTTP403, strlen(HTTP403),0);
            return false;
        }
        //Check for unauthorize file
        else if(fileReq == "/SecretFile.html")
        {
            cout << HTTP401 << endl;
            send(fileDesc, HTTP401, strlen(HTTP401),0);
            return false;
        }
        else
        {
            string fileName = "." + fileReq;
            FILE* file;
            char c;
            file = fopen(fileName.c_str(), "r");
            //Valid file request
            if(file != NULL)
            {
                while(1)
                {
                    if(feof(file))
                    {
                        break;
                    }
                    fread(buffer, 1000, 1, file);
                }
                fclose(file);
                cout << HTTP200 << endl;
                send(fileDesc, HTTP200, strlen(HTTP200),0);
                send(fileDesc, buffer, strlen(buffer), 0);
                return true;
            }
            //File must not found
            else if(file == NULL)
            {
                cout << HTTP404 << endl;
                send(fileDesc, HTTP404, strlen(HTTP404),0);
                return false;
            }
        }
    }
    //Bad Request
    else
    {
        cout << HTTP400 << endl;
        send(fileDesc, HTTP400, strlen(HTTP400),0);
        return false;
    }
}

//Takes in a void pointer to the File Descriptor, 
//the function's argument is where we will read and write the data to/from
void* action(void* args)
{
    //Casting the void pointer back to int pointer so we can deference to get the file descriptor
    int* sockPtr = (int*) args;
    vector<string> requestVector; 
    requestString(*sockPtr, requestVector);
    char fileContent[BUFFSIZE] = {0}; 
    requestCommand(*sockPtr, requestVector, fileContent);
    close(*sockPtr);
}

int main(int argc, char **argv)
{
    //Setting up the server 
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