#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sched.h>
#include <time.h>
#include <math.h>
#include <errno.h>
double p;
pthread_t tid1;
pthread_t tid2;
pthread_t tid3;

void* countA(void* arg){
    struct timespec start1,finish1;
    double elapsedTime_sched_other;
    clock_gettime(CLOCK_REALTIME,&start1);
    // printf("start1 time: %jd\n",start1.tv_sec);
    double ans=0;
    while(ans!=p){
        ans+=1;
    }
    printf("Inside countA\n");
    clock_gettime(CLOCK_REALTIME,&finish1);
    // printf("finish1 time: %jd\n",finish1.tv_sec);
    elapsedTime_sched_other= (finish1.tv_sec + finish1.tv_nsec*(1e-9))  - (start1.tv_sec + start1.tv_nsec*(1e-9));
    printf("Time for Thr-A(sched_other) is %lf seconds\n",elapsedTime_sched_other);
    pthread_cancel(tid1);
}

void* countB(void* arg){
    struct timespec start2,finish2;
    double elapsedTime_sched_rr;
    clock_gettime(CLOCK_REALTIME,&start2);
    // printf("start2 time: %jd\n",start2.tv_sec);
    double ans=0;
    while(ans!=p){
        ans+=1;
    }
    printf("Inside countB\n");
    clock_gettime(CLOCK_REALTIME,&finish2);
    // printf("finish2 time: %jd\n",finish2.tv_sec);
    elapsedTime_sched_rr = (finish2.tv_sec + finish2.tv_nsec*(1e-9))  - (start2.tv_sec + start2.tv_nsec*(1e-9));
    printf("Time for Thr-B(sched_rr) is %lf seconds\n",elapsedTime_sched_rr);
    pthread_cancel(tid2);
}

void* countC(void* arg){
    struct timespec start3,finish3;
    double elapsedTime_sched_fifo;
    clock_gettime(CLOCK_REALTIME,&start3);
    // printf("start3 time: %jd\n", start3.tv_sec);
    double ans=0;
    while(ans!=p){
        ans+=1;
    }
    printf("Inside countC\n");
    clock_gettime(CLOCK_REALTIME,&finish3);
    // printf("finish3 time: %jd\n",finish3.tv_sec);
    elapsedTime_sched_fifo= (finish3.tv_sec + finish3.tv_nsec*(1e-9))  - (start3.tv_sec + start3.tv_nsec*(1e-9));
    printf("Time for Thr-C(sched_fifo) is %lf seconds\n",elapsedTime_sched_fifo);
    pthread_cancel(tid3);
}

int print_policy(pthread_attr_t attr){
    int policy;
    if(pthread_attr_getschedpolicy(&attr, &policy) != 0)
        fprintf(stderr, "Unable to get policy.\n");
    else{
        if(policy == SCHED_OTHER){
            printf("SCHED_OTHER\n");
            return 1;
        }
        else if(policy == SCHED_RR){
            printf("SCHED_RR\n");
            return 2;
        }   
        else if(policy == SCHED_FIFO){
            printf("SCHED_FIFO\n");
            return 3;
        }
            
    }
}

int main(int argc, char **argv){

    int policy, s;
    p = pow(2,32);
    
    struct sched_param schedparam1;  // priority for OTHER {0}
    schedparam1.sched_priority = 0;

    struct sched_param schedparam2;     // priority for RR [1 - 99]
    schedparam2.sched_priority = 60;

    struct sched_param schedparam3;     // priority for FIFO [1 - 99]
    schedparam3.sched_priority = 40;

    //////////Thread1/////////////////////////////////////////////////////////////////////////////////
    // struct timespec start1,finish1;
    // double elapsedTime_sched_other;
    // clock_gettime(CLOCK_MONOTONIC,&start1);
    int success1 = 0;
 
    
 
    // pthread_t tid1;
    
    pthread_attr_t attr1;
    success1 = pthread_attr_init(&attr1);
    if (success1 != 0){
        printf("1: pthread_attr_init failed. Error: %d\n", success1);
    }
    success1 = pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    if (success1 != 0){
        printf("1: pthread_attr_setinheritsched failed. Error: %d\n", success1);
    }
    success1 = pthread_attr_setschedpolicy(&attr1, SCHED_OTHER);
    if (success1 != 0){
        printf("1: pthread_attr_setinheritsched failed. Error: %d\n", success1);
    }
    success1 = pthread_attr_setschedparam(&attr1, &schedparam1);
    if (success1 != 0){
        printf("1: pthread_attr_setschedparam failed. Error: %d\n", success1);
    }
    success1 = pthread_create(&tid1, &attr1, countA, NULL);
    if (success1 != 0){
        printf("1: pthread_create failed. Error: %d\n", success1);
    }
    print_policy(attr1);
    
 
    // clock_gettime(CLOCK_MONOTONIC,&finish1);
    // elapsedTime_sched_other= (finish1.tv_sec + finish1.tv_nsec*(1e-9))  - (start1.tv_sec + start1.tv_nsec*(1e-9));
    // printf("Time for Thr-A(sched_other) is %lf seconds\n",elapsedTime_sched_other);

    ////////Thread2///////////////////////////////////////////////////////////////////////////////

    // struct timespec start2,finish2;
    // double elapsedTime_sched_rr;
    // clock_gettime(CLOCK_MONOTONIC,&start2);
    

    int success2 = 0;

    // pthread_t tid2;
    pthread_attr_t attr2;
    
    success2 = pthread_attr_init(&attr2);
    if (success2 != 0){
        printf("2: pthread_attr_init failed. Error: %d\n", success2);
    }

    success2 = pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    if (success2 != 0){
        printf("2: pthread_attr_setinheritsched failed. Error: %d\n", success2);
    }

    success2 = pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    if (success2 != 0){
        printf("2: pthread_attr_setschedpolicy failed. Error: %d\n", success2);
    }

    pthread_attr_setschedparam(&attr2, &schedparam2);
    success2 = pthread_create(&tid2, &attr2, countB, NULL);
    if (success2 != 0){
        printf("2: pthread_create failed. Error: %d\n", success2);
    }
    print_policy(attr2);
    

    

    // clock_gettime(CLOCK_MONOTONIC,&finish2);
    // elapsedTime_sched_rr = (finish2.tv_sec + finish2.tv_nsec*(1e-9))  - (start2.tv_sec + start2.tv_nsec*(1e-9));
    // printf("Time for Thr-B(sched_rr) is %lf seconds\n",elapsedTime_sched_rr);

    ///////Thread3////////////////////////////////////////////////////////////////////////////////

    // struct timespec start3,finish3;
    // double elapsedTime_sched_fifo;
    // clock_gettime(CLOCK_MONOTONIC,&start3);
    int success3 = 0;

    
    // pthread_t tid3;
    pthread_attr_t attr3;

    success3 = pthread_attr_init(&attr3);
    if (success3 != 0){
        printf("3: pthread_attr_init failed. Error: %d\n", success3);
    }

    success3 = pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);
    if (success3 != 0){
        printf("3: pthread_attr_setinheritsched failed. Error: %d\n", success3);
    }

    success3 = pthread_attr_setschedpolicy(&attr3, SCHED_FIFO);
    if (success3 != 0){
        printf("3: pthread_attr_setschedpolicy failed. Error: %d\n", success3);
    }

    success3 = pthread_attr_setschedparam(&attr3, &schedparam3);
    if (success3 != 0){
        printf("3: pthread_attr_setschedparam failed. Error: %d\n", success3);
    }

    success3 = pthread_create(&tid3, &attr3, countC, NULL);
    if (success3 != 0){
        printf("3: pthread_create failed. Error: %d\n", success3);
    }
    print_policy(attr3);
    

    

    // clock_gettime(CLOCK_MONOTONIC,&finish3);
    // elapsedTime_sched_fifo= (finish3.tv_sec + finish3.tv_nsec*(1e-9))  - (start3.tv_sec + start3.tv_nsec*(1e-9));
    // printf("Time for Thr-C(sched_fifo) is %lf seconds\n",elapsedTime_sched_fifo);
    // joining all
    success1 = pthread_join(tid1, NULL);
    if (success1 != 0){
        printf("1: pthread_join failed. Error: %d\n", success1);
    }
    success2 = pthread_join(tid2, NULL);
    if (success2 != 0){
        printf("2: pthread_create failed. Error: %d\n", success2);
    }
    success3 = pthread_join(tid3, NULL);
    if (success3 != 0){
        printf("3: pthread_join failed. Error: %d\n", success3);
    }
    ///////////////////////////////////////////////////////////////////////////////////////


}
