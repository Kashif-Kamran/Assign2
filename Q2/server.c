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
#define PORT 4444
#define MAXLINE 1024
int main()
{
    printf("\n_______ Server Side _______\n\n");
    int sockfd, ret;
    int newSocket;

    socklen_t addr_size;
    struct sockaddr_in serverAddr;
    struct sockaddr_in newAddr;

    char buffer[1024];
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf(" [__ Error Socket Creation __]\n");
        exit(1);
    }
    printf("[__ Socket Created __]\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    if (ret < 0)
    {
        printf("[__ Error in binding __]\n");
        exit(1);
    }
    printf("[__ Bind to port __] \n");

    int listn = listen(sockfd, 3);
    printf("[__ Listening __]\n");

    while (1)
    {
        newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);
        if (newSocket < 0)
        {
            printf("[__ New Connection Not Connected __]\n");
            exit(1);
        }
        printf("[__ New Connection Accepted __]\n");
        pid_t pid = fork();
        if (pid == 0)
        {
            wait(NULL);
        }
        else if (pid != 0)
        {
            recv(newSocket, buffer, 1024, 0);
        }
    }
    return 0;
}