/*************************************************************************
> File Name: base_client.c
> Author: 
> Mail: 
> Created Time: Thu 19 Oct 2017 03:15:56 AM PDT
************************************************************************/

#include<stdio.h>

#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <string.h>

#include "buffer.h"
#include "net.h"

#define BUFSIZE  1024


int main(int argc, char *argv[])  
{  
    int client_sockfd;  
    int len;  
    Buffer *buf;//数据传送的缓冲区  
  

    client_sockfd =  create_tcp_client("127.0.0.1",80);
	if(client_sockfd==-1)
    {
        printf("连接服务器失败\n");
        //return  -1;
    }

    printf("connected to server \n");  
    buf = create_buffer( 256 );
    
    buf = create_request_header("/index.php","127.0.0.1");
    printf("%s\n",buf->buffer );
   
    close(client_sockfd);//关闭套接字  
    return 0;  
 }  

