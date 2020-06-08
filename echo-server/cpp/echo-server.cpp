#include "header/echo-server.h"
using namespace std;

void usage(char *argv){
    printf("Usage : %s [port] [+options] \n", argv);
    printf("Example) %s 1234 -e -b \n", argv);
}

void *th_sock(void *arg_v){
    Args *arg_use = (Args *)arg_v;
    int socket_client = *((int *)&arg_use->sock_client);
    int buff_len;
    char buff[256];
    list<int>* sock_id = arg_use->sock_id;
    list<int>::iterator socketit;

    while(1){
        memset(buff, 0, 256);
        buff_len = read(socket_client, buff, 256);
        if(buff_len <= 0){
            cout << "read end" << endl;
            break;
        }
        cout << buff << endl;

        if(arg_use->option_echo == true){
            cout << "echo!" << endl;
            write(socket_client, buff, int(strlen(buff)));
        }else{
            write(socket_client, "", 1);
        }

        if(arg_use->option_broad == true){
            for(socketit = sock_id->begin(); socketit != sock_id->end(); socketit++){
                cout << "broad!" << endl;
                write(*socketit, buff, int(strlen(buff)));
            }
        }else{
            write(socket_client, "", 1);
        }

    }

    return 0;
}
