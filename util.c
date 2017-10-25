/*************************************************************************
	> File Name: util.c
	> Author: 
	> Mail: 
	> Created Time: Sun 22 Oct 2017 08:20:12 PM PDT
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
#define BUFSIZE 1024
#define SERVER_PORT 8080

/***
 * create soket and bind listen
 * return soketfd
 */
int create_tcp_server(unsigned short port)
{
    int server_sockfd;

    struct  sockaddr_in  server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if( (server_sockfd = socket(PF_INET ,SOCK_STREAM , 0)) <0 )
    {
        perror("create_tcp_server: socket"); 
        return -1;
    }
    
    if(bind(server_sockfd , (struct sockaddr *)&server_addr,sizeof(struct sockaddr))<0)
    {
        perror("create_tcp_server: bind");
        return -1;
    }
   
    listen(server_sockfd , 5);
    return  server_sockfd;
}
/***
 * accept client connect 
 * return client socketfd
 */
int accept_tcp_client(int server_sockfd,... )
{
    int client_sockfd;
    struct  sockaddr_in  client_addr;
    int sin_size = sizeof(struct sockaddr_in);
    if( (client_sockfd = accept(server_sockfd , (struct sockaddr*)&client_addr,&sin_size)) <0){
        perror("accept ");
        return -1;
    }
    return client_sockfd; 
}


int write_socket( int socket_fd , char * buffer , int len )
{
    if (len <=0 ) return  -2;
    if ( (len&0xFFFF0000) !=0 ) 
    {
      printf("write_socket overflow\n"); return -3;
    }

    int  temp_len = 0 ;
    while( len >0 )
    {

      //printf(" left : %d \n" , len);
      temp_len =   send( socket_fd , buffer , len ,0 ); 
      if ( -1 ==temp_len )
      {
        if (errno==EAGAIN||errno==EWOULDBLOCK||errno==EINTR)
          continue;
        else
        {
          perror("write_socket send :");
          return  -1;    
        }
      }
      len-=temp_len;
      buffer+= temp_len;
        
    }

    return 0;
}

int read_socket( int socket_fd ,char* buffer , int len  )
{
    if ( len <=0 ) return -2;
    if ( (len&0xFFFF0000) !=0 ) 
    {
      printf("read_socket overflow \n"); return -3;
    }

    int temp_len = 0;
    int read_total = 0 ;

    
    temp_len = recv( socket_fd,buffer , len ,0 );
    //printf("read_socket  temp_len : %d \n" ,temp_len);
    if ( -1 == temp_len )
    {
      if (errno==EAGAIN||errno==EWOULDBLOCK||errno==EINTR)
        return 0;
      else
      {
        perror("read_socket recv :");
        return  -1;    
      }
    }else if(temp_len==0)
    {
        printf("read_socket client has close ");
       return  -2;
    }
   read_total += temp_len;
   len-=temp_len;
   buffer+= temp_len;
    

    return read_total;
}

