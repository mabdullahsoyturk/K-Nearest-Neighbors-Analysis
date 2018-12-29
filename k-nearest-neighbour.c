#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

// Represents one patient's data
typedef struct Instance { 
    double id;
    double clump_thickness;
    double uniformity_of_cell_size;
    double uniformity_of_cell_shape;
    double marginal_adhesion;
    double single_epithelial_cell_size;
    double bare_nuclei;
    double bland_chromation;
    double normal_nucleoli;
    double mitoses;
    double class;
    double distance;
} Instance; 

// This functions reads a feature of the instance
void get_features(char* line, int *features) {
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
        int features[11];
        get_features(line, features);
        instances[counter].id = features[0];
        instances[counter].clump_thickness = features[1];
        instances[counter].uniformity_of_cell_size = features[2];
        instances[counter].uniformity_of_cell_shape = features[3];
        instances[counter].marginal_adhesion = features[4];
        instances[counter].single_epithelial_cell_size = features[5];
        instances[counter].bare_nuclei = features[6];
        instances[counter].bland_chromation = features[7];
        instances[counter].normal_nucleoli = features[8];
        instances[counter].mitoses = features[9];
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
    memcpy(train_set,arr, 699 * sizeof(Instance));
    // Fill distances of all points from the instance 
    for (int i = 0; i < n; i++) {
        if(i != exclude) {
            train_set[i].distance = 
                sqrt((train_set[i].clump_thickness - train_set[exclude].clump_thickness) * (train_set[i].clump_thickness - train_set[exclude].clump_thickness) + 
                    (train_set[i].uniformity_of_cell_size - train_set[exclude].uniformity_of_cell_size) * (train_set[i].uniformity_of_cell_size - train_set[exclude].uniformity_of_cell_size) + 
                    (train_set[i].uniformity_of_cell_shape - train_set[exclude].uniformity_of_cell_shape) * (train_set[i].uniformity_of_cell_shape - train_set[exclude].uniformity_of_cell_shape) +
                    (train_set[i].marginal_adhesion - train_set[exclude].marginal_adhesion) * (train_set[i].marginal_adhesion - train_set[exclude].marginal_adhesion) +
                    (train_set[i].single_epithelial_cell_size - train_set[exclude].single_epithelial_cell_size) * (train_set[i].single_epithelial_cell_size - train_set[exclude].single_epithelial_cell_size) +
                    (train_set[i].bare_nuclei - train_set[exclude].bare_nuclei) * (train_set[i].bare_nuclei - train_set[exclude].bare_nuclei) +
                    (train_set[i].bland_chromation - train_set[exclude].bland_chromation) * (train_set[i].bland_chromation - train_set[exclude].bland_chromation) +
                    (train_set[i].normal_nucleoli - train_set[exclude].normal_nucleoli) * (train_set[i].normal_nucleoli - train_set[exclude].normal_nucleoli)                 
                    );   
        }else {
            train_set[exclude].distance = INT_MAX;
        }
    } 

    // Sort the instances by distance from the test instance 
    qsort(train_set, 699, sizeof(train_set[0]), compare_function); 
   
    int freq2 = 0;     // Frequintency of group 2 
    int freq4 = 0;     // Frequency of group 4 

    for (int i = 0; i < k; i++)   // Consider only the first k elements
    { 
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
    read_instances("breast-cancer.csv", instances);

    int k = 5;      // Number of neighbors to check
    double prediction_results_sum = 0;

    for(int i = 0; i < 699; i++) {
        if(classifyAPoint(instances, 699, k, i) == instances[i].class) {
            prediction_results_sum += 1;
        }
    }

  printf("Accuracy is: %f\n ", prediction_results_sum / 699);
} 