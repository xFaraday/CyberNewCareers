#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 15
#define PORT 8888
#define SA struct sockaddr 

void fullsend(int connfd, char newstr[]) { 
    size_t i = 0;
    while(newstr[i] != '\0') {
        i++;
    }
    printf("Name adjusted for scoreboard: %s\n", newstr);
    write(connfd, newstr, i);
    //send(connfd, newstr, strlen(newstr), 0);
} 

void inputcheck(char str[]) {
    size_t i = 0;
    while(str[i] != '\0') {
        if(str[i] < 97 || str[i] > 122) {
            printf("Name can only be lowercase letters. Sending Nothing.\n");
            exit(0);
        }
        i++;
    }
}

//entrypoint
int main(int argc, char *argv[]) { 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
    
    if (argc == 2) {
        printf("Name Entered: %s\n", argv[1]);
    } else if (argc > 2) {
        printf("\tToo many arguments. Please just state your name for the scoreboard and nothing else.\n");
        exit(0);
    } else {
        printf("State your name for the scoreboard.\n\tEx: ./king xfaraday");
        exit(0);
    }

    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else {
        printf("Socket successfully created..\n"); 
    }
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else {
        printf("Socket successfully binded..\n"); 
    }
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else {
        printf("Server listening..\n"); 
    }
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else {
        printf("server acccept the client...\n"); 
    }

    //string handling
    char buff[MAX];
    snprintf(buff, sizeof(buff), "%s", argv[1]);
    //strncpy(buff, argv[1], MAX);
    inputcheck(buff);
    int i;
    i = 0;
    const char *L;
    char *newstr = buff;
    L = buff;
    int lol = 0;
    while (*L != '\0') {
        L++;
        lol++;
    }

    while (i < lol) {
        newstr[i] = buff[i]-32;
        i+=2;
    }

    fullsend(connfd, newstr);
    // After chatting close the socket 
    close(sockfd); 
} 