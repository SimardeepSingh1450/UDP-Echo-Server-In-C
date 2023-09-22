#include<netdb.h>
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
    if(sockfd<0) error("Error opening socket");

    char buffer[255];

    struct sockaddr_in server_addr;

    bzero((char*)&server_addr,sizeof(server_addr));

    //assigning values
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int len = sizeof(server_addr);

    printf("Enter String:\n");
    int n =0;

    while((buffer[n++]=getchar())!='\n');

    sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&server_addr,len);
    bzero(buffer,sizeof(buffer));
    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&server_addr,&len);
    printf("Msg from server: %s\n",buffer);

    close(sockfd);
    return 0;
}
