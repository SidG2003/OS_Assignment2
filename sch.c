#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sched.h>
#include <time.h>
#include <math.h>
#include <errno.h>

void* countA(void* arg){
    double ans=0;
    double p = pow(2,32);
    while(ans!=p){
        ans+=1;
    }
    printf("ok A\n");
}

int main(){

    setrlimit(RLIMIT_RTPRIO);
    
    pthread_t tid1;
    pthread_attr_t custom_sched_attr;
    int fifo_max_prio, fifo_min_prio;
    struct sched_param fifo_param;

    if (pthread_attr_init(&custom_sched_attr)!=0){
        perror("pthread_attr_init");
    }
    if (pthread_attr_setinheritsched(&custom_sched_attr, PTHREAD_EXPLICIT_SCHED) != 0){
        perror("pthread_attr_setinheritsched");
    }
    if(pthread_attr_setschedpolicy(&custom_sched_attr, SCHED_FIFO) != 0){
        perror("pthread_attr_setschedpolicy");
    }

    fifo_max_prio = sched_get_priority_max(SCHED_FIFO);
    fifo_min_prio = sched_get_priority_min(SCHED_FIFO);
    int fifo_mid_prio = (fifo_min_prio + fifo_max_prio)/2;
    fifo_param.sched_priority = fifo_mid_prio;

    if(pthread_attr_setschedparam(&custom_sched_attr, &fifo_param)!=0){
        perror("pthread_attr_setschedparam");
    }
    if(pthread_create(&tid1, &custom_sched_attr, countA, NULL)!=0){
         perror("pthread_create");
    }
    if(pthread_join(tid1, NULL)!=0){
        perror("pthread_join");
    }
}