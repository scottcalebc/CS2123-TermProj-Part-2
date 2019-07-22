#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "projectHeader.h"


char ** createStringArr(int dataSize)
{
    char **arr = malloc(dataSize * sizeof(char*));
    if (arr == NULL)
    {
        printf("array not created\n");
        return NULL;
    }
    int i;
    for(i = 0; i < dataSize; i++);
        *(arr + i) = malloc(MAX_LEN * sizeof(char));
    
    return arr;
    
}

void releaseArr(char **arr, int dataSize)
{
    int i;
    for(i = 0; i < dataSize; i++)
        free(arr[i]);
    free(arr);
}

void fillArray_int(int arr[], int dataSize)
{
    int i = 0;
    srand(time(0));
    while ( i < dataSize)
    {
        arr[i] = 0;
        
        int r = rand();
        arr[i] = r;
        i++;   
    }
}

double runSort_int(int dataSize, void (*sort1)(int[], int, int), void (*sort2)(int[],int))
{
    int arr[dataSize];

    fillArray_int(arr, dataSize);

    clock_t t;
    t = clock();
    if (sort1 != NULL)
        sort1(arr, 0, dataSize - 1);
    else if (sort2 != NULL)
        sort2(arr, dataSize);
    t = clock() - t;

    return ((double)t)/CLOCKS_PER_SEC;
}

void writeData(char *algo, int dataSize, double time_taken)
{
    FILE *file;

    if ((file = fopen("data.txt", "r")) != NULL)
    {
        file = freopen("data.txt", "a", file);
        
        fprintf(stdout, "%s, %d, %lf\n", algo, dataSize, time_taken);
        fprintf(file, "%s, %d, %lf\n", algo, dataSize, time_taken);

        fclose(file);
    } else{
        file = fopen("data.txt", "w");
        fprintf(stdout, "algorithm, data_size, avg_time_taken\n");
        fprintf(file, "algorithm, data_size, avg_time_taken\n");
        fclose(file);
        writeData(algo, dataSize, time_taken);
    }
}

void Run_int(char *algo, void (*sort1)(int[],int,int), void(*sort2)(int[],int))
{
    int arr[] = {1000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000};
    int i, j;
    double avgTime = 0;
    for(i = 0; i < 8; i++)
    {  
        for(j = 0; j < 5; j++)
        {
            if (sort1 != NULL)
                avgTime += runSort_int(arr[i], sort1, NULL);
            else if (sort2 != NULL)
                avgTime += runSort_int(arr[i], NULL, sort2);
            
        }
        
        writeData(algo, arr[i], avgTime/5);
    }
    
}

char ** fill(int dataSize)
{
    FILE* fp = fopen("new_name.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "FILE NOT FOUND");
    }
    char **names = malloc(dataSize * sizeof(char**));
    if (names == NULL)
    {
        printf("Array not Allocated\n");
    }

    int i = 0;
    char name[MAX_LEN + 1];


    while(i < dataSize && fgets(name, MAX_LEN, fp) != NULL)
    {
        names[i] = malloc(MAX_LEN * sizeof(char));
        strcpy(names[i], name);
        int j = strcspn(names[i], "\n\r");
        names[i][j] = '\0';
        i++;
        
    }

    fclose(fp);
    return names;
}

double runSort_str(char **names, int dataSize, void (*sort1)(char *[], int, int), void (*sort2)(char*[],int))
{
    
    clock_t t;
    t = clock();
    if (sort1 != NULL)
        sort1(names, 0, dataSize -1);
    else if (sort2 != NULL)
        sort2(names, dataSize);
    t = clock() - t;

    return ((double)t)/CLOCKS_PER_SEC;

}

void Run_str(char *algo, void (*sort1)(char *[],int,int), void(*sort2)(char *[],int))
{
    int dataSize[] = {10000,78000,156353};
    int i,j;
    char **names;

    double avgTime;

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 5; j++)
        {    
            names = fill(dataSize[i]);

            if (sort1 != NULL)
                avgTime += runSort_str(names,dataSize[i], sort1, NULL);
            else if (sort2 != NULL)
                avgTime += runSort_str(names,dataSize[i], sort1, NULL);

            releaseArr(names, dataSize[i]);
        }  
        writeData(algo, dataSize[i], avgTime/5); 
    }
}

int main(){

    
    Run_int("Quick", quickSort_int, NULL);
    Run_int("Merge", mergeSort_int, NULL);
    Run_int("Radix", NULL,radixSort_int);
    Run_int("Heap", NULL, heapSort_int);
    Run_int("Insertion", NULL, insertionSort_int);
    Run_int("Selection", NULL, selectionSort_int);
    

    //sorting algorithms on string smash stack
   /* 
    Run_str("Merge", mergeSort_str, NULL);
    */ 
    Run_str("Radix", NULL,radixSort_str);
   
    Run_str("Heap", NULL, heapSort_str);
    Run_str("Quick", quickSort_str, NULL);
    Run_str("Insertion", NULL, insertionSort_str);
    Run_str("Selection", NULL, selectionSort_str);
    
    return 0;

}



