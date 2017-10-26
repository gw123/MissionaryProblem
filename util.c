#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


Array*  create_array(){
    Array * array = malloc(sizeof(Array));
    memset( array,0,sizeof(Array) );
    array->array = malloc(128);
    array->len = 0;
    array->size = 128;
    return array;
}

int  array_push( Array* array ,void *value)
{
    if(array->len>=array->size) return -1;
    *(array->array+array->w_pos)= value;
    array->w_pos++;
    array->len++;
    return 0;
}
/***
*  弹出数组第一个元素
*/
void*  array_shift( Array*array  )
{
    int i;
    if(array->w_pos==0)
        return 0;
     void * value = *(array->array);
     for( i = 0 ;i<array->len;i++)
     {
         *(array->array+i)=*(array->array+i+1);
     }
     array->w_pos--;
     array->len--;
     return  value;
}

void* array_pop( Array*array)
{
    if(array->w_pos==0)
        return 0;
     array->w_pos--;
     array->len--;
     return  *(array->array+array->w_pos);
}

void  array_free(Array *array)
{
  int i ;
   for( i=0 ;i<array->len;i++)
      free(*(array->array+i));
   free(array->array);
   free(array);
}

/**
 * @brief explode 字符串切割函数
 * @param delim   分隔符
 * @param str     待切割字符
 * @return        返回 Array *
 */
Array* explode(char *delim ,char  *str)
{
    Array *array = create_array();
    char *p1,*p2,*endp;
    int   delim_len= strlen( delim );
    endp = str+strlen(str);
    p1=str;
    char *buf;
    while( (p2=strstr(p1,delim))!= 0&& (p1+delim_len <= endp) )
    {
       buf = malloc(p2-p1+1);
       strncpy(buf,p1,p2-p1);
       buf[p2-p1]=0;
       p1=p2+delim_len;
       array_push(array,buf);
       //printf("%s\n" , buf);
    }

    buf = malloc(endp-p1+1);
    buf[endp-p1]=0;
    strncpy(buf,p1,endp-p1);
    //printf("%s\n" , buf);
    array_push(array,buf);
    return array;
}
