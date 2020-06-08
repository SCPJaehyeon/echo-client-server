#pragma once
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <list>

struct Args{
    int sock_client;
    bool option_echo;
    bool option_broad;
    std::list<int> *sock_id;
};

void usage(char *argv);
void *th_sock(void *arg_v);
