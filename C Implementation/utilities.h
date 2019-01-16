#define NUMBER_OF_ELEMENTS 699
#define NUMBER_OF_FEATURES 10

// Represents one patient's data
typedef struct Instance { 
    double features[NUMBER_OF_FEATURES];
    double label;
    double distance;
} Instance;

void read_instances(char* file_name, Instance* instances);
void get_features(char* line, double *features);
int compare_function(const void *a,const void *b);