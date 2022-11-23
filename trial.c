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

void* countA(void* arg){
    double ans=0;
    while(ans!=p){
        ans+=1;
    }
    printf("ok A\n");
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

int main(){
    p = pow(2,32);
    double time_taken;
    clock_t t;

    /////////////////////////////////////////////////////////////////////

    pthread_t tid1;
    struct sched_param param1;
    int priority1 = 0;

    param1.sched_priority = priority1;
    int policy1 = SCHED_OTHER;

    pthread_attr_t attr1;
    if (pthread_attr_init(&attr1) != 0){
        printf("1: pthread_attr_init faileds\n");
    }

    if(pthread_create(&tid1, &attr1, countA, NULL) != 0){
        printf("1: pthread_attr_setinheritsched failed.\n");
    }
    t = clock();

    print_policy(attr1);
    /* scheduling parameters of target thread */
    if (pthread_setschedparam(tid1, policy1, &param1) != 0){
        printf("1: pthread_setschedparam failed\n");
    }
    print_policy(attr1);

    if (pthread_join(tid1, NULL) != 0){
        printf("1: pthread_join failed\n");
    }
    t = clock() - t;

   
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Thread A took %f seconds to execute \n", time_taken);

    /////////////////////////////////////////////////////////////////////

    pthread_t tid2;
    struct sched_param param2;
    int priority2 = 10;

    param2.sched_priority = priority2;
    int policy2 = SCHED_RR;

    pthread_attr_t attr2;
    if (pthread_attr_init(&attr2) != 0){
        printf("2: pthread_attr_init faileds\n");
    }

    if (pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED) != 0){
        printf("2: pthread_attr_setinheritsched failed.");
    }

    if(pthread_create(&tid2, &attr2, countA, NULL) != 0){
        printf("2: pthread_attr_setinheritsched failed.\n");
    }
    t = clock();

    print_policy(attr2);
    /* scheduling parameters of target thread */
    if (pthread_setschedparam(tid2, policy2, &param2) != 0){
        printf("1: pthread_setschedparam failed\n");
    }
    while(print_policy(attr2)!=2){
        continue;
    }
    print_policy(attr2);

    if (pthread_join(tid2, NULL) != 0){
        printf("1: pthread_join failed\n");
    }
    t = clock() - t;

   
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Thread B took %f seconds to execute \n", time_taken);

    /////////////////////////////////////////////////////////////////////


}
 