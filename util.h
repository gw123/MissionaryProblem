
int create_tcp_server(unsigned short port);

int accept_tcp_client(int server_sockfd,... );

int write_socket( int socket_fd , char * buffer , int len );

int read_socket( int socket_fd ,char* buffer , int len  );

