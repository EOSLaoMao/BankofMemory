#!/bin/bash
IMAGE=johnnyzhao/eos:mainnet-1.0.7
#HOST=192.168.86.28
HOST=192.168.1.34

docker run --rm -v `(pwd)`:/bankofmemory lemonswang/eos-dev eosiocpp -o /bankofmemory/bankofmemory.wast /bankofmemory/bankofmemory.cpp
docker run -it --rm -v `(pwd)`:/bankofmemory $IMAGE cleos -u http://$HOST:8888 --wallet-url http://$HOST:8900 set contract bankofmemory ../bankofmemory/helloworld -p bankofmemory@active
docker run -it --rm -v `(pwd)`:/bankofmemory $IMAGE cleos -u http://$HOST:8888 --wallet-url http://$HOST:8900 set contract bankofmemory ../bankofmemory -p bankofmemory@active
