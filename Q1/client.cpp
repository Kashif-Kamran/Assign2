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
    char check;
    cout << "[__ Client Side __]" << endl;
    char msgSend[MAXLINE];
    char msgRecv[MAXLINE];

    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0)
    {
        cout << "[__ Error in Socket Creation of Client __]" << endl;
        exit(EXIT_FAILURE);
    }
    socklen_t serverAdressLen;
    struct sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_addr.s_addr = INADDR_ANY;
    serverAdress.sin_port = htons(PORT);
    cout << "Enter Msg : ";
    cin.get(msgSend, MAXLINE - 1);
    sendto(clientSocket, (const char *)msgSend, strlen(msgSend), 0, (const struct sockaddr *)&serverAdress, sizeof(serverAdress));
    recvfrom(clientSocket, (char *)msgRecv, MAXLINE, 0, (struct sockaddr *)&serverAdress, &serverAdressLen);
    if (!strcmp(msgRecv, "1"))
    {
        // Logic of Card Entering
        cout << "Press ( Y ) to Enter Card  ";
        cin >> check;
        if (check != 'y' || check == 'Y')
        {
        }
    }
    else if (!strcmp(msgRecv, "2"))
    {
        // Logic of Card Varification
    }
    else if (!strcmp(msgRecv, "3"))
    {
        // Logic of Withdraw
    }
    close(clientSocket);
    return 0;
}