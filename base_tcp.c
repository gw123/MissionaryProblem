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
#include <pthread.h>
#include"util.h"
#include"buffer.h"
#include "http_help.h"
#define BUFSIZE 1024
#define SERVER_PORT 8080
#define APP_NAME 123

struct App {
    int  server_sockfd;
    int  port;
} app;

void signal_handel(int signo)
{
    printf(" signal_handel signo: %d \n", signo);
    if ( signo==SIGINT )
    {
        stop_server();
        exit(-1);
    }
}

int start_server(int port){
    //int port =  8080;
    signal( SIGHUP, signal_handel);
    signal( SIGINT, signal_handel);
    int server_sockfd = create_tcp_server( port);
    if (server_sockfd <0)
    {
        return  -1;
    }
    app.server_sockfd = server_sockfd;
    return server_sockfd;
}

int stop_server(){
   close(app.server_sockfd);
}

void accept_client(void* arg)
{
    int  len;
    char buf[BUFSIZE];
    int  client_sockfd =  *((int*)arg);
   
    memset(buf,0,sizeof(buf));
    if( (len=read_socket(  client_sockfd , buf ,BUFSIZE -1 )) <0 )     
    {
        perror(" read socket :");
    }

    printf("recv len %d , content:\n%s\n",len,buf);
    Buffer *buffer =  create_buffer(1024);
    set_http_header_status(buffer ,HTTP_404);
    set_http_header_content_type(buffer, HTTP_TYPE_HTML);
    set_http_header_end(buffer);
    char *str = "<BODY><P> 404</P></BODY>\r\n";
    write_buffer(buffer, str, strlen(str));
    write_socket(client_sockfd, buffer->buffer, buffer->pos);
    free_buffer(buffer);
    //send_404_page(client_sockfd);
    //char *send_content = "welcome to myserver\n";
    //write_socket(client_sockfd ,send_content,strlen(send_content));
    
    close( client_sockfd );
}

int main(int argc ,char *argv[])
{
    int server_sockfd;
    int client_sockfd;
    pthread_t newthread;

    server_sockfd = start_server( 8080 );

    while(1)
    {
      client_sockfd = accept_tcp_client(server_sockfd);
      if (pthread_create(&newthread , NULL, (void *)accept_client, (void *)&client_sockfd) != 0)
        perror("pthread_create");
    }
    
    close( server_sockfd );
   return 0 ;
}





