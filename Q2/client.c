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
#define PORT 9999
#define MAXLINE 1024
int main()
{
    /* ------------------ Variables to Send and Receive the msg ----------------- */
    char msgSend[MAXLINE];
    char msgRecv[MAXLINE];
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("=== Socket Creation Failed ===\n");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_addr.s_addr = INADDR_ANY;
    serverAdress.sin_port = htons(PORT);
    printf("Enter msg to send : ");
    gets(msgSend);
    connect(sockfd, (struct sockaddr *)&serverAdress, sizeof(serverAdress));
    send(sockfd, msgSend, sizeof(msgSend), 0);
    recv(sockfd, msgRecv, sizeof(msgRecv), 0);
    printf("msgRecv : %s", msgRecv);
    close(sockfd);
    return 0;
}