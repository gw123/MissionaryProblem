/*************************************************************************
	> File Name: base_tcp.c
	> Author: 
	> Mail: 
	> Created Time: Thu 19 Oct 2017 01:46:51 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>
#include "buffer.h"
//#include"net.h"

const  int  buffer_size = 512;
// 
const  int  buffer_max_size = 1048576 ;
//#define  BUFFER_TEST  1 //for test


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
    if( ( buffer->pos+len) > buffer->buffer_size )
      {
        //printf("need_buffer_size :%d, current_buffer_size:%d\n", buffer->pos+len ,buffer->buffer_size );
        if (increase_buffer( buffer ,buffer->pos+len) !=0)
         return -1;
      }

    memcpy(buffer->buffer+ buffer->pos,temp,len );
    buffer->pre_pos = buffer->pos;
    buffer->pos+=len;

    return 0;
}

int read_buffer(Buffer *buffer,char *buffer1 ,int len,char *end)
{
  //if()
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

int  increase_buffer( Buffer *buffer,int size)
{
   int new_size = ( size/1024+1 )*1024;
   //printf(" new_size: %d ,old_size :%d \n", new_size,buffer->buffer_size );
   
   if( (new_size>buffer_max_size)  )
   {
     return -2;
   }
   
   char *new_buffer_addr = realloc(buffer->buffer , new_size);
   //char *new_buffer_addr = malloc(new_size);
   if(new_buffer_addr==0)
    return -1;
   //memset(new_buffer_addr, 0 ,new_size);
   //memcpy(new_buffer_addr,buffer->buffer,buffer->pos);
   //free(buffer->buffer);
   
   buffer->buffer_size = new_size;
   buffer->buffer = new_buffer_addr;
   return 0;
}

void print_buffer( Buffer * buffer)
{
    int  i = 0;
    while(i<buffer->pos)
    {
       printf("%c", *(buffer->buffer+i));
       i++;
    }
}

/** just  for test */
#ifdef BUFFER_TEST

int main()
{
   //	char *buffer[buffer_size] = 0;
    Buffer * buffer = create_buffer(buffer_size);
    char *temp = "1x3456781234567812345678123456781x34567812345678123456781234567\n";
    while(write_buffer( buffer ,temp , strlen(temp) ) ==0)
    { 
       //if( buffer->pos >4000 ) break;
    }

    printf("size:%d pos:%d content:\n",buffer->buffer_size , buffer->pos );
    print_buffer(buffer);
  
    /** test rest buffer */
    reset_buffer(buffer);

    printf("size:%d pos:%d content:\n",buffer->buffer_size , buffer->pos );
    print_buffer(buffer);
    
     /** rewrite  buffer */
    //temp = "x234567812345678123456781234567\n";
    while(write_buffer( buffer ,temp , strlen(temp) ) ==0)
    {
       if( buffer->pos >4200 ) break;
    }

    printf(" size:%d pos:%d content:\n",buffer->buffer_size , buffer->pos );
    print_buffer(buffer);
    free_buffer(buffer);
    return 0;
}
#endif