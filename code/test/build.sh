#!/bin/bash

CFLAGS="-std=c++14 -O2 -Wall -g "
LDFLAGS="-lpthread -lmysqlclient"

g++ -o test test.cpp ../buffer/buffer.cpp ../log/log.cpp ../pool/*.cpp  ${LDFLAGS}