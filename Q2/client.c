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
    printf("\n_______ Client Side _______\n\n");
    /* ------------------ Variables to Send and Receive the msg ----------------- */
    char msgSend[MAXLINE];
    char msgRecv[MAXLINE];
    char str1[MAXLINE];
    char str2[MAXLINE];
    char choice[5];

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
    connect(sockfd, (struct sockaddr *)&serverAdress, sizeof(serverAdress));
    printf("Enter msg to send : ");
    gets(choice);
    send(sockfd, choice, sizeof(choice), 0);
    recv(sockfd, msgRecv, sizeof(msgRecv), 0);
    printf("[__ %s __]\n", msgRecv);
    if (!strcmp(choice, "1"))
    {
        printf("Enter First String  : ");
        gets(str1);
        printf("Enter Second String  : ");
        gets(str2);
        send(sockfd, str1, sizeof(str1), 0);
        send(sockfd, str2, sizeof(str2), 0);
        recv(sockfd, msgRecv, sizeof(msgRecv), 0);
        printf("Result : %s\n", msgRecv);
    }
    else if (!strcmp(choice, "2"))
    {
        printf("Enter String : ");
        gets(str1);
        printf("Enter Character : ");
        gets(str2);
        send(sockfd, str1, sizeof(str1), 0);
        send(sockfd, str2, sizeof(str2), 0);
        recv(sockfd, msgRecv, sizeof(msgRecv), 0);
        printf("Result : %s\n", msgRecv);
    }
    else if (!strcmp(choice, "3"))
    {
        printf("Enter String : ");
        gets(str1);
        printf("Enter Character : ");
        gets(str2);
        send(sockfd, str1, sizeof(str1), 0);
        send(sockfd, str2, sizeof(str2), 0);
        recv(sockfd, msgRecv, sizeof(msgRecv), 0);
        printf("Result : %s\n", msgRecv);
    }
    else if (!strcmp(choice, "4"))
    {
    }
    else if (!strcmp(choice, "5"))
    {
    }
    else
    {
    }

    close(sockfd);
    return 0;
}