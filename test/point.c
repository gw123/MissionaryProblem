/*************************************************************************
	> File Name: point.c
	> Author: 
	> Mail: 
	> Created Time: Thu 02 Nov 2017 12:30:34 AM PDT
 ************************************************************************/

#include<stdio.h>
typedef  struct  user {
    char* username;
    int   brithday;
    char* addr;
    char* passwd;
} user;

int main()
{
   user *u ;
   printf(" sizeof  user:%d \n " , sizeof(user));
   printf(" sizeof  *user:%d \n " , sizeof(*u));
    
}
