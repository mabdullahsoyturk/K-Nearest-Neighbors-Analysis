#include <stdio.h>
#include "utilities.h"
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

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
        double* features = malloc(sizeof(double) * (NUMBER_OF_FEATURES + 1));
        get_features(line, features);
        for(int i = 0; i < NUMBER_OF_FEATURES; i++) {
            instances[counter].features[i] = features[i];
        }
        instances[counter].label = features[10];
        free(features);

        counter++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}

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

// Sort the array of instances by increasing order of distance 
int compare_function(const void *a,const void *b) {
    double l = ((struct Instance*)a)->distance;
    double r = ((struct Instance*)b)->distance;
    return (l - r); 
}