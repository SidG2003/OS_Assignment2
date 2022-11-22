#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sched.h>
#include <time.h>
#include <math.h>


void* countA(void* arg){
    double ans=0;
    while(ans!=pow(2,32)){
        ans+=1;
    }
}

void* countB(void* arg){
    double ans=0;
    while(ans!=pow(2,32)){
        ans+=1;
    }
}

void* countC(void* arg){
    double ans=0;
    while(ans!=pow(2,32)){
        ans+=1;
    }
}

int main(int argc, char **argv){

    if (argc!=1){
        printf("Error, does not accept any arguments");
        exit(-1);
    }

    struct timespec start1,finish1;
    double elapsedTime_sched_other;
    clock_gettime(CLOCK_MONOTONIC,&start1);
    struct sched_param schedparam1;
    schedparam1.sched_priority = 20;
    pthread_t tid1;
    pthread_attr_t attr1;
    pthread_attr_init(&attr1);
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr1, SCHED_OTHER);
    pthread_attr_setschedparam(&attr1, &schedparam1);
    pthread_create(&tid1, &attr1, countA, NULL);
    pthread_join(tid1, NULL);
    clock_gettime(CLOCK_MONOTONIC,&finish1);
    // elapsedTime_sched_other= (finish1.tv_sec - start1.tv_sec);
    elapsedTime_sched_other= (finish1.tv_sec + finish1.tv_nsec*(1e-9))  - (start1.tv_sec + start1.tv_nsec*(1e-9));
    // elapsedTime_sched_other+=(finish1.tv_nsec - start1.tv_nsec)*(1e-9);
    printf("Time for Thr-A(sched_other) is %lf seconds\n",elapsedTime_sched_other);


    struct timespec start2,finish2;
    double elapsedTime_sched_rr;
    clock_gettime(CLOCK_MONOTONIC,&start2);
    // struct sched_param schedparam2;
    // schedparam2.sched_priority = 20;
    pthread_t tid2;
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    // pthread_attr_setschedparam(&attr2, &schedparam2);
    pthread_create(&tid2, &attr2, countB, NULL);
    pthread_join(tid2, NULL);
    clock_gettime(CLOCK_MONOTONIC,&finish2);
    // elapsedTime_sched_other= (finish2.tv_sec - start2.tv_sec);
    elapsedTime_sched_other= (finish2.tv_sec + finish2.tv_nsec*(1e-9))  - (start2.tv_sec + start2.tv_nsec*(1e-9));
    // elapsedTime_sched_other+=(finish2.tv_nsec - start2.tv_nsec)*(1e-9);
    printf("Time for Thr-B(sched_rr) is %lf seconds\n",elapsedTime_sched_rr);


    struct timespec start3,finish3;
    double elapsedTime_sched_fifo;
    clock_gettime(CLOCK_MONOTONIC,&start3);
    struct sched_param schedparam3;
    schedparam3.sched_priority = 20;
    pthread_t tid3;
    pthread_attr_t attr3;
    pthread_attr_init(&attr3);
    pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr3, SCHED_FIFO);
    pthread_attr_setschedparam(&attr3, &schedparam3);
    pthread_create(&tid3, &attr3, countC, NULL);
    pthread_join(tid3, NULL);
    clock_gettime(CLOCK_MONOTONIC,&finish3);
    // elapsedTime_sched_other= (finish3.tv_sec - start3.tv_sec);
    elapsedTime_sched_other= (finish3.tv_sec + finish3.tv_nsec*(1e-9))  - (start3.tv_sec + start3.tv_nsec*(1e-9));
    // elapsedTime_sched_other+=(finish3.tv_nsec - start3.tv_nsec)*(1e-9);
    printf("Time for Thr-C(sched_fifo) is %lf seconds\n",elapsedTime_sched_fifo);
}
