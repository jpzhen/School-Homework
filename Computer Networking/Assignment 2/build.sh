#! /bin/bash
cd serverDir/
g++ -pthread -std=c++11 server.cpp -o server.out -g

cd ../retrieverDir/ 
g++ -std=c++11 retriever.cpp -o retriever.out -g

cd ../serverDir/
./server.out 1499