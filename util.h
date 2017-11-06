#ifndef Struct_array
#define Struct_array
typedef struct {
    char *str;
    int len;
} str;

typedef struct {
    void **array;
    int  r_pos;  //读指针
    int  w_pos;  // 指向下一个写位置
    int  len;    //数据内容长度
    int  size;   //数组索引分配内存大小
} Array;
#endif

Array*  create_array();

int  array_push( Array* array ,void *value);

/***
*  弹出数组第一个元素
*/
void*  array_shift( Array*array  );

void* array_pop( Array*array);

void  array_free(Array *array);

/**
 * @brief explode 字符串切割函数
 * @param delim   分隔符
 * @param str     待切割字符
 * @return        返回 Array *
 */
Array* explode(char *delim ,char  *str);
