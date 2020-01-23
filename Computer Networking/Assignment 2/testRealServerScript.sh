#!/bin/bash

cd retrieverDir/

# 200 Ok
./retriever.out www.httpbin.org /get 80
# 300 Moved
./retriever.out www.google.com /gmail 80
# 400 Bad Request
./retriever.out www.abc.go.com %/ 80