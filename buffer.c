/*************************************************************************
	> File Name: base_tcp.c
	> Author: 
	> Mail: 
	> Created Time: Thu 19 Oct 2017 01:46:51 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>
#include <pthread.h>
//#include"util.h"

const  int  buffer_size = 1024;

typedef  struct  
{
  char *buffer;
  int  buffer_size;
  int  pos;
  int  pre_pos;
} Buffer;

Buffer* create_buffer(int  buffer_size )
{
   
   Buffer * buf = malloc(sizeof(Buffer));
   if ( buf ==0 ) return 0;

   memset(buf, 0 ,sizeof(Buffer));
   buf->buffer = malloc(buffer_size);
   if(buf->buffer == 0 ) return 0;

   memset(buf->buffer, 0 ,buffer_size);
   buf->buffer_size = buffer_size;

   return  buf;
}
 
int  write_buffer(Buffer * buffer ,char *temp , int len)
{
    if( (buffer->pos+len) > buffer->buffer_size  )
      return -1;

    memcpy(buffer->buffer+ buffer->pos,temp,len );
    buffer->pre_pos = buffer->pos;
    buffer->pos+=len;

    return 0;
}

void  reset_buffer(Buffer *buffer)
{
   int buffer_size = buffer->buffer_size;

   memset(buffer->buffer, 0 ,buffer_size);
   buffer->pos=0;
   buffer->pre_pos = 0;

}

void free_buffer(Buffer *buffer)
{
  free(buffer->buffer);
  free(buffer);
  buffer = 0;
}

/** just  for test */
#ifndef  APP_NAME

int main()
{
   //	char *buffer[buffer_size] = 0;
    Buffer * buffer = create_buffer(buffer_size);
    char *temp = "1234567812345678123456781234567\n";
    while(write_buffer( buffer ,temp , strlen(temp) ) ==0)
    { }

    printf(" size:%d pos:%d content: \n%s\n len:%d \n",
      buffer->buffer_size , buffer->pos ,buffer->buffer ,strlen(buffer->buffer));
    
    /** test rest buffer */
    reset_buffer(buffer);

    printf(" size:%d pos:%d content: \n%s\n len:%d \n",
    buffer->buffer_size , buffer->pos ,buffer->buffer ,strlen(buffer->buffer));
    
     /** rewrite  buffer */
    temp = "x234567812345678123456781234567\n";
    while(write_buffer( buffer ,temp , strlen(temp) ) ==0)
    { }

    printf(" size:%d pos:%d content: \n%s\n len:%d \n",
    buffer->buffer_size , buffer->pos ,buffer->buffer ,strlen(buffer->buffer));
    free_buffer(buffer);
    return 0;
}
#endif