#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define NUMBER_OF_FEATURES 10
#define DATASET_NAME "breast-cancer.csv"

// Represents one patient's data
typedef struct Instance { 
    double features[NUMBER_OF_FEATURES];
    double class;
    double distance;
} Instance; 

// This functions reads a feature of the instance
void get_features(char* line, double *features) {
    // printf("%s", line);
    char *tok = strtok(line, ",");
    int count = 0;
    features[count] = atof(tok);

    while (tok != NULL) {
        count++;
        tok = strtok(NULL, ",");
        if(tok != NULL) {
            features[count] = atof(tok);
        }
    }
}

// This functions reads all instances from the csv file
void read_instances(char* file_name, Instance* instances) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    int counter = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        Instance instance;
        double features[11];
        get_features(line, features);
        for(int i = 0; i < NUMBER_OF_FEATURES; i++) {
            instances[counter].features[i] = features[i];
        }
        instances[counter].class = features[10];

        counter++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}

// Sort the array of instances by increasing order of distance 
int compare_function(const void *a,const void *b) {
    double l = ((struct Instance*)a)->distance;
    double r = ((struct Instance*)b)->distance;
    return (l - r); 
}
  
// This function finds classification of an instance using 
// k nearest neighbour algorithm. It assumes only two 
// groups and returns 2 if it belongs to benign group, else 
// 4 (belongs to group malignant). 
int classifyAPoint(Instance arr[], int n, int k, int exclude) { 
    Instance train_set[699];
    memcpy(train_set, arr, 699 * sizeof(Instance));
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
    qsort(train_set, 699, sizeof(train_set[0]), compare_function); 
   
    int freq2 = 0;     // Frequintency of group 2 
    int freq4 = 0;     // Frequency of group 4 

    for (int i = 0; i < k; i++) {    // Consider only the first k elements
        if (train_set[i].class == 2) {
            freq2++;    // Benign
        }
        else {
            freq4++;   // Melignant
        }  
    } 
  
    return (freq2 > freq4 ? 2 : 4); 
} 
  
int main() { 
    Instance instances[699];

    /* Read X_train */
    read_instances(DATASET_NAME, instances);

    int k = 1;      // Number of neighbors to check
    double prediction_results_sum = 0;

    clock_t begin = clock();

    for(int i = 0; i < 699; i++) {
        if(classifyAPoint(instances, 699, k, i) == instances[i].class) {
            prediction_results_sum += 1;
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time consumed: %f\n", time_spent);
    printf("Accuracy is: %f\n ", prediction_results_sum / 699);
} 