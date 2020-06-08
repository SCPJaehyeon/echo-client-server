#include "header/echo-server.h"
using namespace std;

int main(int argc, char *argv[]){
    if(argc < 2 || argc > 5){
        usage(argv[0]);
        return -1;
    }

    struct sockaddr_in addr_server = {};
    struct sockaddr_in addr_client = {};
    socklen_t addr_client_len = sizeof(addr_client_len);

    memset(&addr_server, 0, sizeof(addr_server));
    addr_server.sin_port = htons(atoi(argv[1]));
    addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_server.sin_family = AF_INET;

    pthread_t pth_t;
    int pth_ck;
    list<int> sock_id;

    int option = getopt(argc, argv, "ebh");
    bool option_echo = false, option_broad = false;
    switch(option){
        case 'e':
            cout << "echo Option Selected!" << endl;
            option_echo = true;
            break;
        case 'b':
            cout << "broadcase Option Selected!" << endl;
            option_broad = true;
            break;
        case 'h':
            cout << "Options : " << endl;
            cout << "-a : echo" << endl;
            cout << "-b : broadcase" << endl;
            cout << "-h : help" << endl;
            exit(1);
        default:
            break;
    }

    int sock_server = socket(PF_INET, SOCK_STREAM, 0);
    int sock_client;

    if(sock_server == -1){
        cout << "socket error" << endl;
        close(sock_server);
        exit(1);
    }

    if(bind(sock_server, (sockaddr*) &addr_server, sizeof(addr_server)) == -1){
        cout << "bind error" << endl;
        close(sock_server);
        exit(1);
    }

    if(listen(sock_server, 3) == -1){
        cout << "listen error" << endl;
        close(sock_server);
        exit(1);
    }

    while(1){
        sock_client = accept(sock_server, (sockaddr*) &addr_client, &addr_client_len);

        if(sock_client == -1){
            cout << "accept error" << endl;
            close(sock_client);
            close(sock_server);
            exit(1);
        }

        sock_id.push_back(sock_client);

        Args *args_v;
        args_v = (Args *)malloc(sizeof(Args));
        args_v->sock_client = sock_client;
        args_v->option_echo = option_echo;
        args_v->option_broad = option_broad;
        args_v->sock_id = &sock_id;

        pth_ck = pthread_create(&pth_t, NULL, th_sock,(void *)args_v);
        if(pth_ck != 0){
            cout << "thread error" << endl;
            exit(1);
        }
        pthread_detach(pth_t);

    }

    close(sock_client);
    close(sock_server);

    return 0;
}


