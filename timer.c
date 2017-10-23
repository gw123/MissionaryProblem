/*************************************************************************
	> File Name: timer.c
	> Author: 
	> Mail: 
	> Created Time: Tue 17 Oct 2017 07:56:53 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<event.h>

void onTime(int sock,short event,void *arg)
{
    printf("on timer \n");
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec =0;
    event_add( (struct event*)arg,&tv);
}

int main(){
    event_init();
    struct  event evTime;
    evtimer_set(&evTime,onTime ,&evTime);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec=0;
    event_add(&evTime,&tv);
     
    event_dispatch();
    return 0;
}


