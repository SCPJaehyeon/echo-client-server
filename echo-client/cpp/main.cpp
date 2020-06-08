#include "header/echo-client.h"
using namespace std;

int main(int argc, char *argv[]){
    if(argc != 3){
        usage(argv[0]);
        return -1;
    }

    struct sockaddr_in addr_server = {};

    memset(&addr_server, 0, sizeof(addr_server));
    addr_server.sin_family = AF_INET;
    addr_server.sin_addr.s_addr = inet_addr(argv[1]);
    addr_server.sin_port = htons(atoi(argv[2]));

    char buff[256];
    int buff_len;
    pthread_t pth_t;
    int pth_ck;

    int sock_client = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_client == -1){
        cout << "socket error" << endl;
        close(sock_client);
        exit(1);
    }

    if(connect(sock_client, (struct sockaddr*) &addr_server, sizeof(addr_server)) == -1){
        cout << "connect error" << endl;
        close(sock_client);
        exit(1);
    }

    pth_ck = pthread_create(&pth_t, NULL, th_read, (void *)&sock_client);
    if(pth_ck != 0){
        cout << "thread error" << endl;
        exit(1);
    }
    pthread_detach(pth_t);

    while(1){
        memset(buff, 0, 256);
        cin >> buff;
        buff_len = write(sock_client, buff, int(strlen(buff)));
        if(buff_len <= 0){
            cout << "write end" << endl;
            break;
        }
    }
    close(sock_client);

    return 0;
}
