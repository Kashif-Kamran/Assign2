#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

#define MAXLINE 1024
#define PORT 5050
int main()
{
    /* ---------------------------- Input Parametter ---------------------------- */
    char msgSend[MAXLINE];
    char msgRecv[MAXLINE];
    cout << "___ Server Side ___" << endl;
    /* ----------------------------- Connection Code ---------------------------- */
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0)
    {
        cout << "[__ Server Socket Creation Failed __]" << endl;
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET; // IPv4
    serverAdress.sin_addr.s_addr = INADDR_ANY;
    serverAdress.sin_port = htons(PORT);
    struct sockaddr_in clientsAdres[3];
    // Client Adresses
    socklen_t clintAdrLen[3];

    int bindcheck = bind(serverSocket, (const struct sockaddr *)&serverAdress, sizeof(serverAdress));
    if (bindcheck < 0)
    {
        cout << "___ Binding Failed ___" << endl;
        exit(EXIT_FAILURE);
    }
    recvfrom(serverSocket, msgRecv, sizeof(msgRecv), 0, (struct sockaddr *)&clientsAdres[0], &clintAdrLen[0]);
    recvfrom(serverSocket, msgRecv, sizeof(msgRecv), 0, (struct sockaddr *)&clientsAdres[0], &clintAdrLen[2]);
    recvfrom(serverSocket, msgRecv, sizeof(msgRecv), 0, (struct sockaddr *)&clientsAdres[0], &clintAdrLen[3]);
    cout << "[__ All three Clients Are Connected __]" << endl;
    close(serverSocket);
    return 0;
}