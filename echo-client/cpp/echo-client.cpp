#include "header/echo-client.h"
using namespace std;

void usage(char *argv){
    printf("Usage : %s [ip] [port] \n", argv);
    printf("Example) %s 192.168.0.12 1234 \n", argv);
}

void *th_read(void *args){
    int socket_client = *((int *)args);
    char r_buff[256];
    while(1){
        memset(r_buff,0,256);
        if(read(socket_client, r_buff, 256)>2){
            cout << r_buff << endl;
        }
    }
}
