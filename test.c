#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#define SYS_kernel_2d_memcpy 451



int main() {
    float matrix1[3][3] = {{1.0,1.0,1.0},{2.0,2.0,2.0},{3.0,3.0,3.0}};
    float matrix2[3][3] = {{7.0,7.0,7.0},{7.0,7.0,7.0},{7.0,7.0,7.0}};

    printf("Initial matrix 1:\n");

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%lf ", matrix1[i][j]);
            }
        printf("\n");
    }
    printf("\n");

    printf("Initial matrix 2:\n");;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%lf ", matrix2[i][j]);
            }
        printf("\n");
    }
    printf("\n");

    int suc = syscall(SYS_kernel_2d_memcpy, matrix1, matrix2, 3, 3);

    if(suc < 0){
        printf("ERROR! system call unsuccessful");
        exit(1);
    }

    printf("Final matrix 1:\n");

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%lf ", matrix1[i][j]);
            }
        printf("\n");
    }
    printf("\n");

    printf("Final matrix 2:\n");

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%lf ", matrix2[i][j]);
            }
        printf("\n");
    }
    printf("\n");

    return 0;
}