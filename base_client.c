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
#include "http_help.h"
#include "net.h"

#define BUFSIZE  1024


int main(int argc, char *argv[])  
{  
    int client_sockfd;  
    int len;  
    Buffer *buf;//数据传送的缓冲区  
    char *url = "http://17ky.xyt:80/index.php?user=1";
    buf =send_get_request(url);
    // return 0; 
    // buf = send_http_request("17ky.xyt",80,"/index.html");  
    // printf("recv buffer_size :%d \n", buf->buffer_size  );
    printf("recv len :%d \n", buf->pos   );
    // printf("recv content:%s \n", buf->buffer   );
    close(client_sockfd);//关闭套接字  
    return 0;  
 }  

