#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
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
void manu()
{
    printf("\n1. For Cancatination of Strings\n");
    printf("2. For Occurance of Characters\n");
    printf("3. For Comparing Two Strings \n");
    printf("4. For Checking Palindrom String\n");
    printf("5. For Adding String Numbers\n\n");
}
int stringsComparison(char *str1, char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (tolower(str1[i]) != tolower(str2[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}
int occuranceOfChar(char *str, char ch)
{
    int i = 0;
    int index = -1;
    while (str[i] != '\0')
    {
        if (str[i] == ch)
        {
            printf("i : %d", i);
            index = i;
            break;
        }
        i++;
    }
    return index;
}
int main()
{
    printf("\n_______ Server Side _______\n\n");

    /* ----------------------- Variables to Store the Data ---------------------- */
    char msgSend[MAXLINE];
    char msgRecv[MAXLINE];
    char choice[MAXLINE];
    char str1[MAXLINE];
    char str2[MAXLINE];
    int occurance;

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
    manu();
    while (1)
    {
        int clientSocket = accept(server_socket, NULL, NULL);
        printf("______Connection Established______\n");
        pid_t pid = fork();
        if (pid == 0)
        {
            recv(clientSocket, choice, sizeof(choice), 0);
            printf("Choice Received : %s\n", choice);
            if (!strcmp(choice, "1"))
            {
                send(clientSocket, "Send Two Strings For Cancatination", 36, 0);
                recv(clientSocket, str1, sizeof(str1), 0);
                recv(clientSocket, str2, sizeof(str2), 0);
                printf("String 1 : %s\n", str1);
                printf("String 2 : %s\n", str2);
                strcat(str1, str2);
                strcpy(msgSend, str1);
                send(clientSocket, msgSend, sizeof(msgSend), 0);
            }
            else if (!strcmp(choice, "2"))
            {
                send(clientSocket, "Send a string and a Character to find its Occurance", 53, 0);
                recv(clientSocket, str1, sizeof(str1), 0);
                recv(clientSocket, str2, sizeof(str2), 0);
                printf("String : %s\n", str1);
                printf("Character : %c\n", str2[0]);
                occurance = occuranceOfChar(str1, str2[0]);
                printf("Occurance : %d\n", occurance);
                sprintf(msgSend, "%d", occurance);
            }
            else if (!strcmp(choice, "3"))
            {
                send(clientSocket, "Send Two Strings For comparison", 33, 0);
                recv(clientSocket, str1, sizeof(str1), 0);
                recv(clientSocket, str2, sizeof(str2), 0);
                printf("String 1 : %s\n", str1);
                printf("String 2 : %s\n", str2);
                int check = stringsComparison(str1, str2);
                if (check == 0)
                {
                    strcpy(msgSend, "False");
                }
                else
                {
                    strcpy(msgSend, "True");
                }
                send(clientSocket, msgSend, sizeof(msgSend), 0);
            }
            else if (!strcmp(choice, "4"))
            {
                send(clientSocket, "Send One String to find whether it is palindrom or not", 56, 0);
            }
            else if (!strcmp(choice, "5"))
            {
                send(clientSocket, "Send Two string values to find sum", 36, 0);
            }
            else
            {
                send(clientSocket, "____ Invalid Choice Entered ____", 34, 0);
            }
        }
    }
    close(server_socket);
    return 0;
}