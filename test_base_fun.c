/*************************************************************************
	> File Name: test_base_fun.c
	> Author: 
	> Mail: 
	> Created Time: Tue 17 Oct 2017 07:40:12 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main()
{
  int a = 217;
  char b;
  printf("before toascii() b value=%d(%c)\n ",a,b);
  b = toascii(a);
  printf("after toascii() b value=%d(%c)\n",b,b);

 return 0;
}
