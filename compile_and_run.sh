#!/bin/bash
IMAGE=eoslaomao/eos:1.1.4
# change it to your local ip
HOST=192.168.1.68

NAME=bankofmemory

docker ps | grep $NAME-eos-dev
if [ $? -ne 0 ]; then
    echo "Run eos dev env "
    docker run --name $NAME-eos-dev -dit --rm -v  `(pwd)`:/$NAME lemonswang/eos-dev
fi

docker exec $NAME-eos-dev eosiocpp -o /$NAME/$NAME.wast /$NAME/$NAME.cpp
echo ".................................build complete!"

docker cp ../bankofmemory nodeosd:/

#docker exec $NAME-eos-dev cleos -u http://$HOST:8888 --wallet-url http://$HOST:8900 set contract $NAME /$NAME/hello -p $NAME@active
#echo ".................................hello deployed!"
#docker exec $NAME-eos-dev cleos -u http://$HOST:8888 --wallet-url http://$HOST:8900 set contract $NAME /$NAME -p $NAME@active
#echo ".................................$NAME deployed!"
