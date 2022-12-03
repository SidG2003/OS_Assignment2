#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <assert.h>



int main(){

    //////////////////////////////////////////////////
    struct timespec start1,finish1;
    double time1;
    
    pid_t pid1;
    clock_gettime(CLOCK_MONOTONIC,&start1);
    pid1 = fork();
   
    int status;
   
    if (pid1 < 0){
        puts("Forking Error");
        exit(EXIT_FAILURE);
    }
    else if (pid1 == 0){         // child process
        printf("in child process\n");
        struct sched_param param1;
        param1.sched_priority=0;
        sched_setscheduler(pid1, SCHED_OTHER, &param1);
        //execl("/bin/sh","sh","-c", "script1.sh", (char*)NULL);
        execl("/bin/sh","sh", "/home/sid/SiddharthGupta2021355_OS2/OS_Assignment2/script1.sh", (char*)NULL);
        //execl("/bin/sh","sh", "/home/sid/SiddharthGupta2021355_OS2/OS_Assignment2/script1.sh", (char*)NULL);
        
        //execl("/bin/sh","sh", "/home/uday/uday/OS_Assignment2/script1.sh", (char*)NULL);
        // execvp(args[0], args); 
        exit(EXIT_FAILURE);	   
    }
    else{                       // parent process
        printf("in parent process\n");
        waitpid(pid1, &status, WUNTRACED);
        assert(WIFEXITED(status)); 
        clock_gettime(CLOCK_MONOTONIC,&finish1);
        time1 = (finish1.tv_sec + finish1.tv_nsec*(1e-9))  - (start1.tv_sec + start1.tv_nsec*(1e-9));
        printf("Time for process 1 is %lf seconds\n",time1);
    }
    //////////////////////////////////////////////////

    struct timespec start2,finish2;
    double time2;

    int status2;
    
    pid_t pid2;
    clock_gettime(CLOCK_MONOTONIC,&start2);
    pid2 = fork();
   
    if (pid2 < 0){
        puts("Forking Error");
        exit(EXIT_FAILURE);
    }
    else if (pid2 == 0){         // child process
        printf("in child process\n");
        execl("/bin/sh","sh", "/home/sid/SiddharthGupta2021355_OS2/OS_Assignment2/script2.sh", (char*)NULL);
        //execl("/bin/sh","sh", "/home/uday/uday/OS_Assignment2/script2.sh", (char*)NULL);
        // execvp(args[0], args); 
        exit(EXIT_FAILURE);	   
    }
    else{                       // parent process
        printf("in parent process\n");
        struct sched_param param2;
        param2.sched_priority=3;
        sched_setscheduler(pid2, SCHED_RR, &param2);
        waitpid(pid2, &status2, WUNTRACED);
        assert(WIFEXITED(status2)); 
        clock_gettime(CLOCK_MONOTONIC,&finish2);
        time2 = (finish2.tv_sec + finish2.tv_nsec*(1e-9))  - (start2.tv_sec + start2.tv_nsec*(1e-9));
        printf("Time for process 2 is %lf seconds\n",time2);
    }
    //////////////////////////////////////////////////

    struct timespec start3,finish3;
    double time3;

    int status3;
    
    pid_t pid3;
    clock_gettime(CLOCK_MONOTONIC,&start3);
    pid3 = fork();
   
    if (pid3 < 0){
        puts("Forking Error");
        exit(EXIT_FAILURE);
    }
    else if (pid3 == 0){         // child process
        printf("in child process\n");
        struct sched_param param3;
        param3.sched_priority=3;
        sched_setscheduler(pid3, SCHED_FIFO, &param3);
        execl("/bin/sh","sh", "/home/sid/SiddharthGupta2021355_OS2/OS_Assignment2/script3.sh", (char*)NULL);
        //execl("/bin/sh","sh", "/home/uday/uday/OS_Assignment2/script3.sh", (char*)NULL);
        // execvp(args[0], args); 
        exit(EXIT_FAILURE);	   
    }
    else{                       // parent process
        printf("in parent process\n");
        waitpid(pid3, &status3, WUNTRACED);
        assert(WIFEXITED(status3)); 
        clock_gettime(CLOCK_MONOTONIC,&finish3);
        time3 = (finish3.tv_sec + finish3.tv_nsec*(1e-9))  - (start3.tv_sec + start3.tv_nsec*(1e-9));
        printf("Time for process 3 is %lf seconds\n",time3);
    }



}
