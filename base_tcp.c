/*************************************************************************
	> File Name: base_tcp.c
	> Author: 
	> Mail: 
	> Created Time: Thu 19 Oct 2017 01:46:51 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>
#include"util.h"
#define BUFSIZE 1024
#define SERVER_PORT 8080

struct App {
    int  server_sockfd;
    int  port;
} app;

int start_server(){
    
}

int stop_server(){
   close(app.server_sockfd);
}


void signal_handel(int signo)
{
    printf(" signal_handel signo: %d \n", signo);
    if ( signo==SIGINT )
    {
        stop_server();
        exit(-1);
    }
}

int main(int argc ,char *argv[])
{
    int server_sockfd;
    int client_sockfd;
    int len;
    char buf[BUFSIZE];
    
    int port =  8080;
    signal( SIGHUP, signal_handel);
    signal( SIGINT, signal_handel);
    server_sockfd = create_tcp_server( port);
    client_sockfd = accept_tcp_client(server_sockfd);
    app.server_sockfd = server_sockfd;

    char *send_content = "welcome to myserver\n";
    write_socket(client_sockfd ,send_content,strlen(send_content));
    
    while(1)
    {
        memset(buf,0,sizeof(buf));
        if( (len=read_socket(  client_sockfd , buf ,BUFSIZE -1 )) <0 )     
        {
            perror(" read socket :");
            break;
        }

        printf("recv len %d , content: %s \n",len,buf);
        if( write_socket( client_sockfd , buf ,len )<0 )
        {
            perror(" write ");
        }
    }
    close( client_sockfd );
    close( server_sockfd );
   return 0 ;
}





