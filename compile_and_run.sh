#!/bin/bash
IMAGE=johnnyzhao/eos:mainnet-1.0.7
#HOST=192.168.86.28
HOST=192.168.1.34
NAME=bankofmemory

docker ps | grep eos-dev
if [ $? -ne 0 ]; then
    echo "Run eos dev env "
    docker run --name $NAME-eos-dev -dit --rm -v  `(pwd)`:/$NAME lemonswang/eos-dev
fi

docker exec $NAME-eos-dev eosiocpp -o /$NAME/$NAME.wast /$NAME/$NAME.cpp
echo ".................................build complete!"
docker exec $NAME-eos-dev cleos -u http://$HOST:8888 --wallet-url http://$HOST:8900 set contract $NAME /$NAME/helloworld -p $NAME@active
echo ".................................helloworld deployed!"
docker exec $NAME-eos-dev cleos -u http://$HOST:8888 --wallet-url http://$HOST:8900 set contract $NAME /$NAME -p $NAME@active
echo ".................................$NAME deployed!"
