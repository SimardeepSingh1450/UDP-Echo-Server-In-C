#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc,char* argv[]){
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        error("Error opening socket...");
    }

    struct sockaddr_in server_addr,client;
    socklen_t clientlen;

    //clearing out the server_addr
    bzero((char*)&server_addr,sizeof(server_addr));

    int portno;
    portno = atoi(argv[1]);

    //setting server_addr values
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portno);

    if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        error("Error binding the sockfd to server...");
    }

    //Listen
    // listen(sockfd,5);
    clientlen = sizeof(client);

    // //new sockfd after listening for accepting the connection
    // int newSockFd = accept(sockfd,(struct sockaddr*) &client,&clientlen);
    //
    // if(newSockFd<0){
    //     error("Server was unable to open accept...");
    // }

    int n;//dummy variable for read and write
    char buffer[255];

    while(1){
        bzero(buffer,255);

        n = recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*) &client,&clientlen);
        if(n<0) error("Error receiving message on server-side...");

        printf("Message from Client: %s\n",buffer);

        n = sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*) &client,clientlen);
        if(n<0) error("There was an error sending message on server side...");


        if(strncmp("exit",buffer,4)==0){
            printf("Client made an exit...");
            break;
        }
    }

    //closing the sockfd
    // close(newSockFd);
    close(sockfd);
    return 0;
}
