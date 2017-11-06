#include "buffer.h"

int create_tcp_server(unsigned short port);

int accept_tcp_client(int server_sockfd,... );

int write_socket( int socket_fd , char * buffer , int len );

int read_socket( int socket_fd ,char* buffer , int len  );

int create_tcp_client();

//int read_http_header( int socket_fd ,Buffer * buffer );

Buffer* read_socket_all( int socket_fd , Buffer * buf );

int read_http_response( int socket_fd ,Buffer * buffer );
/**
  host 主机名
  ip_str 的长度必须大于等于16字节
 */

int getHostIp(char* host ,char* ip_str);
