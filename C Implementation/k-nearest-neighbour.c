#include "k-nearest-neighbour.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <time.h>

// This function finds classification of an instance using 
// k nearest neighbour algorithm. It assumes only two 
// groups and returns 2 if it belongs to benign group, else 
// 4 (belongs to group malignant). 
int classifyAPoint(Instance* instances, int n, int k, int exclude) { 
    Instance* train_set = malloc(sizeof(Instance) * NUMBER_OF_ELEMENTS);
    memcpy(train_set, instances, NUMBER_OF_ELEMENTS * sizeof(Instance));
    // Fill distances of all points from the instance 
    for (int i = 0; i < n; i++) {
        if(i != exclude) {
            double sum = 0;

            for(int k = 1; k < NUMBER_OF_FEATURES; k++) { // exclude id and class
                sum += (train_set[i].features[k] - train_set[exclude].features[k]) * (train_set[i].features[k] - train_set[exclude].features[k]);
            }

            train_set[i].distance = sqrt(sum);   
        }else {
            train_set[exclude].distance = INT_MAX;
        }
    } 

    // Sort the instances by distance from the test instance 
    qsort(train_set, NUMBER_OF_ELEMENTS, sizeof(train_set[0]), compare_function); 
   
    int freq2 = 0;     // Frequintency of group 2 
    int freq4 = 0;     // Frequency of group 4 

    for (int i = 0; i < k; i++) {    // Consider only the first k elements
        if (train_set[i].label == 2) {
            freq2++;    // Benign
        }
        else {
            freq4++;   // Melignant
        }  
    }

    free(train_set); 
  
    return (freq2 > freq4 ? 2 : 4); 
}

void leave_one_out_cross_validation(Instance* instances) {
    int k = 1;      // Number of neighbors to check
    double prediction_results_sum = 0;

    for(int i = 0; i < NUMBER_OF_ELEMENTS; i++) { // Leave one out cross validation
        if(classifyAPoint(instances, NUMBER_OF_ELEMENTS, k, i) == instances[i].label) {
            prediction_results_sum += 1;
        }
    }

    printf("Accuracy is: %f\n ", prediction_results_sum / NUMBER_OF_ELEMENTS);
}