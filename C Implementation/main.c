#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "k-nearest-neighbour.h"

#define DATASET_NAME "breast-cancer.csv" 
  
int main() { 
    Instance instances[699];

    /* Read X_train */
    read_instances(DATASET_NAME, instances);

    clock_t begin = clock();

    leave_one_out_cross_validation(instances);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time consumed: %f\n", time_spent);
} 