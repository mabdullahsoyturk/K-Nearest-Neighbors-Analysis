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
    Instance* instances = malloc(sizeof(Instance) * NUMBER_OF_ELEMENTS);

    read_instances(DATASET_NAME, instances); /* Read X_train */

    leave_one_out_cross_validation(instances);

    free(instances);
} 