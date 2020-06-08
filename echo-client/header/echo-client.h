#pragma once
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <list>

void usage(char *argv);
void *th_read(void *args);
