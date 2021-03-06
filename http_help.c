#include "buffer.h"
#include "net.h"
#include "http_help.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define SERVER_STRING "Server: gw_httpd/0.1.0\r\n"

int parse_http_header(Buffer * buffer)
{
   char *p1, *p2;
   //printf("%s\n", "explode=====>");
   Array *headers = explode("\r\n",buffer->buffer);
   //printf("headers len :%d\n",headers->len );
   //printf("%s\n",buffer->buffer );
   //while( p1 = array_shift(headers) )
   p1 = array_shift(headers);
   Array *header_item = explode(" ",p1);
   //printf("method: %s\n", p1);
   if(header_item->len>=2)
   {
    char *method = array_shift(header_item);
    char *query  = array_shift(header_item);
    printf("method: %s\n", method);
    printf("query: %s\n", query);

   }else{
    return -1;
   }

   array_free(header_item);
   char *key ;
   char *value ;
   while( (p1 = array_shift(headers)) !=0)
   {
      //printf("header: %s\n", p1);
       if( (*p1) ==0 )
       {
         free(p1); break;
       }
       
       header_item  = explode(": ",p1);
       char *key    = array_shift(header_item);
       char *value  = array_shift(header_item);
       printf("%s  => %s\n", key , value);
       free(p1);
   }

   //
   p1 = array_shift(headers);
   free(p1);
   //开始解析post 数据

   array_free(headers);

}

int set_http_header_status(Buffer * buffer,int http_status)
{
    //Buffer * buffer = create_buffer(1024);
    char *str="" ;
    switch(http_status)
    {
        case HTTP_200:
          str = "HTTP/1.0 200 OK\r\n";
        break;
        case HTTP_302:
          str = "HTTP/1.0 302 OK\r\n";
        break;
        case HTTP_404:
          str = "HTTP/1.0 404 OK\r\n";
        break;
        case HTTP_503:
          str = "HTTP/1.0 503 OK\r\n";
        break;
    }
   
    write_buffer(buffer ,str , strlen(str));

    str = SERVER_STRING;
    write_buffer(buffer ,str , strlen(str));

    return 0;
}

int set_http_header_content_type(Buffer *buffer,int content_type)
{
    char *str ="";
    switch(content_type)
    {
        case HTTP_TYPE_HTML:
             str = "text/html; charset=utf-8\r\n";
         break;
        case HTTP_TYPE_JSON:
             str = "Content-Type: application/json\r\n";
         break;
        case HTTP_TYPE_PNG:
             str = "Content-Type: text/html\r\n";
         break;
        default:
            str = "Content-Type: image/png\r\n";
    }
   
    write_buffer(buffer,str , strlen(str));
}

int set_http_header_end(Buffer *buffer)
{
  write_buffer(buffer, "\r\n", strlen("\r\n"));
}

int  send_404_page(int client_sockfd)
{
    Buffer * buffer = create_buffer(1024);
    //send(client, buf, strlen(buf), 0);
    char *str ;
    str = "HTTP/1.0 404 NOT FOUND\r\n";
    write_buffer(buffer,str , strlen(str));

    str = SERVER_STRING;
    write_buffer(buffer,str , strlen(str));

    str = "Content-Type: text/html\r\n";
    write_buffer(buffer,str , strlen(str));

    write_buffer(buffer, "\r\n", strlen("\r\n"));

    str = "<HTML><TITLE>Not Found</TITLE>\r\n";
    write_buffer(buffer,str , strlen(str));

    str = "<BODY><P>The server could not fulfill</P>\r\n";
    write_buffer(buffer, str, strlen(str));

    str = "</BODY></HTML>";
    write_buffer(buffer, str, strlen(str));
   
    write_socket(client_sockfd, buffer->buffer, buffer->pos);
    free_buffer(buffer);
    return 0;
}

int  add_503()
{

}

int  add_302()
{

}


/*******************客户端头********************/


Buffer* create_request_header(char *queryStr ,char *host)
{
    char *temp_str;
    Buffer *buf  = create_buffer(256);
   
     //请求方式 路径 http 协议版本
    temp_str = "GET ";
    write_buffer( buf ,temp_str,strlen(temp_str) );
    write_buffer( buf ,queryStr,strlen(queryStr) );
    temp_str = " HTTP/1.1\r\n";
    write_buffer( buf ,temp_str,strlen(temp_str) );
    
    //设置host 
    temp_str = "Host: ";
    write_buffer( buf ,temp_str,strlen(temp_str) );
    write_buffer( buf ,host ,strlen(host) );
    temp_str = "\r\n";
    write_buffer( buf ,temp_str,strlen(temp_str) );

    //是否为长连接（ http1.0 默认为 close  ， http1.1 默认为Keep-alive）
    temp_str = "Connection: Close\r\n";
    write_buffer( buf ,temp_str,strlen(temp_str) );

    // header 结尾
    temp_str = "\r\n";
    write_buffer( buf ,temp_str,strlen(temp_str) );
    
   return buf;
}

/*  queryStr 一定要以 / 开头 如： /index.html **/
Buffer* send_http_request(char* host,unsigned short port,char* queryStr)
{  
    Buffer *buf;
    char hostIp[16];
    if( getHostIp(host,hostIp) !=0 )
    {
       printf("can't resolve host ip: %s\n",host);
       return NULL;     
    }

    int client_sockfd =  create_tcp_client( hostIp,port);
    if(client_sockfd==-1)
    {
        printf("连接服务器失败\n");
        free_buffer( buf );
        return  NULL;
    }

    printf("连接到服务器 \n");

    buf = create_request_header( queryStr , host);

    //printf("request header: \n%s\n",buf->buffer );
    write_socket( client_sockfd,buf->buffer,buf->pos);
    //free_buffer(  buf );
    reset_buffer( buf );
    read_http_response(client_sockfd ,buf);
    //printf("recv len:%d \n recv content:\n%s\n END=== \n" ,buf->pos,buf->buffer);
    close(client_sockfd);   
   return buf;
}

Buffer* send_get_request(char * url)
{
   Buffer *buffer;
   char *p = url; 
   char *host ;
   int host_len=0;
   char portStr[6]={0};
   unsigned short port=80;
   char *queryStr;
   int queryStr_len=0;
   char *temp ; 
   if( strncmp(p,"http://",7 ) !=0 )
   {
     printf("only supose http \n");
     return NULL;
   }
    
   p += strlen("http://");
   host = p;
   while( (*p)!=0 && (*p)!='/' && (*p)!=':' )
   {
     p++;
     host_len++;
   }
   
   temp = malloc(host_len+1);
   memcpy(temp,host,host_len);
   temp[host_len]=0;
   host=temp;
   //   printf("%s\n",host); 

   if( *p == ':' ) 
   { 
     p++;
     int i=0;
     while( i<6 && (*p)!='/' && (*p)!=0 )
     {
       portStr[i++]=*p; p++;
     }
     port = atoi(portStr);
   }   
   //   printf("port: %d\n" ,port);
 
   queryStr = p;
   while( (*p)!=0  )
   {
     p++;
     queryStr_len++;
   }
   
   temp = malloc(queryStr_len+1);  
   memcpy(temp,queryStr,queryStr_len);
   temp[queryStr_len]=0;
   queryStr =temp;
 
   //printf("host:%s  queryStr:%s \n port:%d \n",host,queryStr,port);

   buffer =send_http_request(host,port,queryStr);
   free(host);
   free(queryStr);
   return buffer;
}



