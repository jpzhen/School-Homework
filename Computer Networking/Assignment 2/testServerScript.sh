#!/bin/bash

cd retrieverDir/

# 200 Ok
./retriever.out csslab3.uwb.edu /getThis.txt 1499
# 400 Bad Request
./retriever.out csslab3.uwb.edu /abcdefghijklmnopqrtsuvwxyz.txt 1499
# 401 Unauthorized
./retriever.out csslab3.uwb.edu ../getThis.txt 1499
# 403 Forbidden
./retriever.out csslab3.uwb.edu /SecretFile.html 1499
# 404 Not Found
./retriever.out csslab3.uwb.edu /getThis2.txt 1499
