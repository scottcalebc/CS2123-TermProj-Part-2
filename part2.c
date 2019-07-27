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



double runSort_int(int **retarr, int dataSize, void (*sort1)(int[], int, int), void (*sort2)(int[],int))
{
    int *arr = malloc(dataSize * sizeof(int));

    fillArray_int(arr, dataSize);

    clock_t t;
    t = clock();
    if (sort1 != NULL)
        sort1(arr, 0, dataSize - 1);
    else if (sort2 != NULL)
        sort2(arr, dataSize);
    t = clock() - t;

    if (*retarr != NULL)
        *retarr = arr;
    else
        free(arr);

    return ((double)t)/CLOCKS_PER_SEC;
}

void writeData(char *algo, int dataSize, double time_taken, char *fileName)
{
    FILE *file;

    if ((file = fopen(fileName, "r")) != NULL)
    {
        file = freopen(fileName, "a", file);
        
        fprintf(stdout, "%s, %d, %lf\n", algo, dataSize, time_taken);
        fprintf(file, "%s, %d, %lf\n", algo, dataSize, time_taken);

        fclose(file);
    } else{
        file = fopen(fileName, "w");
        fprintf(stdout, "algorithm, data_size, avg_time_taken\n");
        fprintf(file, "algorithm, data_size, avg_time_taken\n");
        fclose(file);
        writeData(algo, dataSize, time_taken, fileName);
    }
}

void Run_int(char *algo, void (*sort1)(int[],int,int), void(*sort2)(int[],int))
{
    int arr[] = {1000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000};
    int i, j;
    double avgTime = 0;
    for(i = 8; i < sizeof(arr)/sizeof(int); i++)
    {  
        for(j = 0; j < 5; j++)
        {
            if (sort1 != NULL)
                avgTime += runSort_int(NULL,arr[i], sort1, NULL);
            else if (sort2 != NULL)
                avgTime += runSort_int(NULL,arr[i], NULL, sort2);
            
        }
        
        writeData(algo, arr[i], avgTime/5, "runtime_int.txt");
    }
    
}

char ** fill(int dataSize, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
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
    int max = 3;
    double avgTime;

    if (strcmp(algo, "Merge") == 0)
    {
        max = 2;
    }

    for(i = 0; i < max; i++)
    {
        for(j = 0; j < 5; j++)
        {    
            names = fill(dataSize[i], "new_name.txt");

            if (sort1 != NULL)
                avgTime += runSort_str(names,dataSize[i], sort1, NULL);
            else if (sort2 != NULL)
                avgTime += runSort_str(names,dataSize[i], sort1, NULL);

            releaseArr(names, dataSize[i]);
        }  
        writeData(algo, dataSize[i], avgTime/5, "runtime_str.txt"); 
    }
}

void Run_All()
{
    Run_int("Quick", quickSort_int, NULL);
    Run_int("Merge", mergeSort_int, NULL);
    Run_int("Radix", NULL,radixSort_int);
    Run_int("Heap", NULL, heapSort_int);
    Run_int("Insertion", NULL, insertionSort_int);
    Run_int("Selection", NULL, selectionSort_int);
    

    //sorting algorithms on string smash stack
    
    Run_str("Merge", mergeSort_str, NULL);
    
    Run_str("Radix", NULL,radixSort_str);
   
    Run_str("Heap", NULL, heapSort_str);
    Run_str("Quick", quickSort_str, NULL);
    Run_str("Insertion", NULL, insertionSort_str);
    Run_str("Selection", NULL, selectionSort_str);

}

void writeArray_int(char *algo, int *arr, int dataSize)
{
    char ext[] = ".txt";
    char *filename = malloc((strlen(algo) + strlen(ext) * sizeof(char)) + 1);
    strcpy(filename, algo);
    strcat(filename, ext);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error file %s could not be opened\n", filename);
    }
    int i;
    for(i = 0; i < dataSize; i++)
    {
        fprintf(fp, "%d\n", arr[i]);
    }


}

void writeArray_str(char *algo, char **arr, int dataSize)
{
    char ext[] = ".txt";
    char *filename = malloc((strlen(algo) + strlen(ext) * sizeof(char)) + 1);
    strcpy(filename, algo);
    strcat(filename, ext);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error file %s could not be opened\n", filename);
    }
    int i;
    for(i = 0; i < dataSize; i++)
    {
        fprintf(fp, "%s\n", arr[i]);
    }


}

void printResults_int(double time, int *arr, int dataSize)
{
    printf("Sort executed in %.4lf seconds\n", time);
    printf("First  element Array[%d] = %d\n", 0, arr[0]);
    printf("Middle element Array[%d] = %d\n", dataSize/2, arr[dataSize/2]);
    printf("Last   element Array[%d] = %d\n", dataSize-1, arr[dataSize-1]);
}
void printResults_str(double time, char **arr, int dataSize)
{
    printf("Sort executed in %.4lf seconds\n", time);
    printf("First  element Array[%d] = %s\n", 0, arr[0]);
    printf("Middle element Array[%d] = %s\n", dataSize/2, arr[dataSize/2]);
    printf("Last   element Array[%d] = %s\n", dataSize-1, arr[dataSize-1]);
}

void menu()
{
    char *algorithms[] = {"quick", "merge", "radix", "heap", "insertion", "selection"};

    int algo;
    int type;
    int size;
    double time;

    int i;
    for(i = 0; i < 6; i++)
    {
        printf("%d. %-13s ", i + 1, algorithms[i]);

        if ((i+1)%2 == 0)
            printf("\n");
    }
    printf("Choose sorting algorithm: ");
    scanf("%d", &algo);
    printf("1. %-13s 2. %-13s\n", "Integer", "String");
    printf("Pick data type: ");
    scanf("%d", &type);
    printf("Enter data size: ");
    scanf("%d", &size);

    if (type == 1)
    {
        //integer
        int *arr = malloc(size *sizeof(int));

        fillArray_int(arr, size);

        switch (algo - 1)
        {
        case 1:
            time = runSort_int(&arr, size, quickSort_int, NULL);
            break;
        case 2:
            time = runSort_int(&arr, size, mergeSort_int, NULL);
            break;
        case 3:
            time = runSort_int(&arr, size, NULL, radixSort_int);
            break;
        case 4:
            time = runSort_int(&arr, size, NULL, heapSort_int);
            break;
        case 5:
            time = runSort_int(&arr, size, NULL, insertionSort_int);
            break;
        case 6:
            time = runSort_int(&arr, size, NULL, selectionSort_int);
            break;
        default:
            break;
        }

        printResults_int(time, arr, size);
        writeArray_int(algorithms[algo-1], arr, size);
        free(arr);
    } else{
        //string
        printf("Enter file to read strings: ");
        char filename[MAX_LEN];
        scanf("%s", filename);
        char **items = fill(size, filename);

        if (items == NULL)
        {
            printf("Error: File does not exists\n");
            return;
        }

        switch (algo - 1)
        {
        case 1:
            time = runSort_str(items, size, quickSort_str, NULL);
            break;
        case 2:
            time = runSort_str(items, size, mergeSort_str, NULL);
            break;
        case 3:
            time = runSort_str(items, size, NULL, radixSort_str);
            break;
        case 4:
            time = runSort_str(items, size, NULL, heapSort_str);
            break;
        case 5:
            time = runSort_str(items, size, NULL, insertionSort_str);
            break;
        case 6:
            time = runSort_str(items, size, NULL, selectionSort_str);
            break;
        default:
            break;
        }

        printResults_str(time, items, size);
        writeArray_str(algorithms[algo-1], items, size);
        releaseArr(items, size);
    }
}

int main(){

    printf("1. Run individual sort 2. Run all sorts\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 2)
    {
        Run_All();
    } else
    {
        while(choice)
        {
            menu();

            printf("Sort again? (y/n): ");
            char again;
            scanf("%*c %c", &again);

            if (again != 'y')
                break;
        }    
    }
    

    
   
    return 0;

}



