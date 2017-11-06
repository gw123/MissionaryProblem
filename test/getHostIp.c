#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>

/**
  host 主机名
  ip_str 的长度必须大于等于16字节
*/
int getHostIp(char* host ,char* ip_str )
{
   struct hostent  *hptr;
   memset( ip_str ,0,16);	
   if( (hptr = gethostbyname(host)) == NULL)
   {
     return -1;
   } 
  inet_ntop( hptr->h_addrtype, hptr->h_addr, ip_str, 16 );
  //printf("ip_str: %s \n",ip_str);
  return 0;
}


int main(int argc ,char* argv[])
{  
    
     char *host = argv[1];
     printf("%s \n",host);	
     char ip_str[16];
     if( 0==getHostIp(host,ip_str) )
       printf( "ip_str: %s \n" , ip_str );
     else
       printf( "主机(%s) ip解析失败" , host );
     return 1;
}
