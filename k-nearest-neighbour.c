#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

typedef struct Instance { 
     int clump_thickness;
     int uniformity_of_cell_size;
     int uniformity_of_cell_shape;
     int marginal_adhesion;
     int single_epithelial_cell_size;
     int bare_nuclei;
     int bland_chromation;
     int normal_nucleoli;
     int mitoses;
     int class;
     int distance;
} Instance; 

// This functions reads a feature of the instance
void get_features(char* line, int *features) {
    // printf("%s", line);
    char *tok = strtok(line, ",");
    int count = 0;
    features[count] = atoi(tok);

    while (tok != NULL) {
        count++;
        tok = strtok(NULL, ",");
        if(tok != NULL) {
            features[count] = atoi(tok);
        }
    }
}

// This functions reads an instance from the csv file
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
        int features[10];
        get_features(line, features);
        instances[counter].clump_thickness = features[0];
        instances[counter].uniformity_of_cell_size = features[1];
        instances[counter].uniformity_of_cell_shape = features[2];
        instances[counter].marginal_adhesion = features[3];
        instances[counter].single_epithelial_cell_size = features[4];
        instances[counter].bare_nuclei = features[5];
        instances[counter].bland_chromation = features[6];
        instances[counter].normal_nucleoli = features[7];
        instances[counter].mitoses = features[8];
        instances[counter].class = features[9];

        counter++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}

// Sort the array of instances by increasing order of distance 
int compare_function(const void *a,const void *b) {
    int l = ((struct Instance*)a)->distance;
    int r = ((struct Instance*)b)->distance;  
    return (l - r); 
}
  
// This function finds classification of an instance using 
// k nearest neighbour algorithm. It assumes only two 
// groups and returns 2 if it belongs to benign group, else 
// 4 (belongs to group malignant). 
int classifyAPoint(Instance arr[], int n, int k, Instance instance) 
{ 
    // Fill distances of all points from the instance 
    for (int i = 0; i < n; i++) {
        arr[i].distance = 
            sqrt((arr[i].clump_thickness - instance.clump_thickness) * (arr[i].clump_thickness - instance.clump_thickness) + 
                 (arr[i].uniformity_of_cell_size - instance.uniformity_of_cell_size) * (arr[i].uniformity_of_cell_size - instance.uniformity_of_cell_size) + 
                 (arr[i].uniformity_of_cell_shape - instance.uniformity_of_cell_shape) * (arr[i].uniformity_of_cell_shape - instance.uniformity_of_cell_shape) +
                 (arr[i].marginal_adhesion - instance.marginal_adhesion) * (arr[i].marginal_adhesion - instance.marginal_adhesion) +
                 (arr[i].single_epithelial_cell_size - instance.single_epithelial_cell_size) * (arr[i].single_epithelial_cell_size - instance.single_epithelial_cell_size) +
                 (arr[i].bare_nuclei - instance.bare_nuclei) * (arr[i].bare_nuclei - instance.bare_nuclei) +
                 (arr[i].bland_chromation - instance.bland_chromation) * (arr[i].bland_chromation - instance.bland_chromation) +
                 (arr[i].normal_nucleoli - instance.normal_nucleoli) * (arr[i].normal_nucleoli - instance.normal_nucleoli)                 
                 );
    } 

    // Sort the instances by distance from the test instance 
    qsort(arr, 559, sizeof(arr[0]), compare_function); 
   
    int freq2 = 0;     // Frequency of group 2 
    int freq4 = 0;     // Frequency of group 4 

    for (int i = 0; i < k; i++)   // Consider only the first k elements
    { 
        if (arr[i].class == 2) {
            freq2++;
        } 
        else {
            freq4++;
        }  
    } 
  
    return (freq2 > freq4 ? 2 : 4); 
} 
  
int main() { 
    Instance instances[559];

    /* Read X_train */
    read_instances("X_train.csv", instances);

    /* Test instance 4,2,1,1,1,2,3,2,1 */
    Instance instance;
    instance.clump_thickness = 4;
    instance.uniformity_of_cell_size = 2;
    instance.uniformity_of_cell_shape = 1;
    instance.marginal_adhesion = 1;
    instance.single_epithelial_cell_size = 1;
    instance.bare_nuclei = 2;
    instance.bland_chromation = 3;
    instance.normal_nucleoli = 2;
    instance.mitoses = 1;

    int k = 5;
    printf ("The value classified to unknown point"
           " is %d.\n", classifyAPoint(instances, 559, k, instance)); 
} 
