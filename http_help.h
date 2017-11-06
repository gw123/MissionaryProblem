
#define HTTP_101 101
#define HTTP_200 200
#define HTTP_300 300
#define HTTP_301 301
#define HTTP_302 302
#define HTTP_400 400
#define HTTP_403 403
#define HTTP_404 404
#define HTTP_500 500
#define HTTP_502 502
#define HTTP_503 503
#define HTTP_504 504

#define HTTP_TYPE_HTML  1
#define HTTP_TYPE_TEXT  2
#define HTTP_TYPE_XML   3
#define HTTP_TYPE_GIF   4
#define HTTP_TYPE_JPEG  5
#define HTTP_TYPE_PNG   6
#define HTTP_TYPE_JSON  7
#define HTTP_TYPE_PDF   8
#define HTTP_TYPE_MSWORD  9

typedef struct  HttpHeader 
{
  char  *head ;
  char  *middle;
}HttpHeader;

int send_404_page(int client_sockfd);

int set_http_header_status(Buffer * buffer,int http_status);

int set_http_header_content_type(Buffer *buffer,int conent_type);

int set_http_header_end(Buffer *buffer);

Buffer* create_request_header(char *queryStr ,char *hostIp);

Buffer* send_http_request(char* host,unsigned short port,char* queryStr);

Buffer* send_get_request(char *url);


