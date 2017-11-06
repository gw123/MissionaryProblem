
#ifndef Buffer_Struct
#define Buffer_Struct
typedef  struct  
{
  char *buffer;
  int  buffer_size;
  int  pos;
  int  pre_pos;
  int  read_pos;
  
} Buffer;
#endif

Buffer* create_buffer(int  buffer_size );

int   write_buffer(Buffer * buffer ,char *temp , int len);

void  reset_buffer(Buffer *buffer);

void  free_buffer(Buffer *buffer);



