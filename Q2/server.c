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
    printf("\n_______ Server Side _______\n\n");

    /* ----------------------- Variables to Store the Data ---------------------- */
    char msgSend[MAXLINE] = "I got you msg";
    char msgRecv[MAXLINE];

    /* -------------------------------------------------------------------------- */
    /*                               Connection Code                              */
    /* -------------------------------------------------------------------------- */

    /* -------------------------- 1.creation of Socket -------------------------- */
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("=== Socket Creation Failed ===\n");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    /* ------------------------ 2. Binding And Listening ------------------------ */
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    printf("______Binding Successfull______\n");
    listen(server_socket, 0);
    printf("______Server is on Listening Mode______\n ");

    /* -------------------------------------------------------------------------- */
    /*                            Welcomeing Port Code                            */
    /* -------------------------------------------------------------------------- */
    while (1)
    {
        int clientSocket = accept(server_socket, NULL, NULL);
        printf("______Connection Established______\n");
        pid_t pid = fork();
        if (pid == 0)
        {
            printf("new process Created");
            recv(clientSocket, msgRecv, sizeof(msgRecv), 0);
            printf("Msg Received : %s\n", msgRecv);
            send(clientSocket, msgSend, sizeof(msgSend), 0);
        }
    }
    close(server_socket);
    return 0;
}