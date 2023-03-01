#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

void selection_sort(int arr[],int size, int *ss_swaps, int *ss_compares) {
    for(int i=0;i<size-1;i++) {
        int min=i;
        for(int j=i+1;j<size;j++){
            (*ss_compares)++;
            if(arr[j]<arr[min]) 
                min = j;
        }    
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
        (*ss_swaps)++;
    }

}

void insertion_sort(int arr[],int n, int *is_swaps, int *is_compares) {
    int i,key,j;
    for(int i=1;i<n;i++) {
        key = arr[i];
        j=i-1;
        while(j>=0 && arr[j]>key) {
            (*is_compares)++;
            arr[j+1] = arr[j];
            j=j-1;
            (*is_swaps)++;
        }
        arr[j+1] = key;
    }
}


void main() {

    FILE *fp;
    fp  = fopen ("random.txt", "w");
    srand((unsigned int) time(NULL));
    for(int block=0;block<1000;block++) {
        for(int i=0;i<100;i++) {
            int number = (int)(((float) rand() / (float)(RAND_MAX))*100000);
            fprintf(fp,"%d ",number);
        }
        fputs("\n",fp);
    }
    fclose (fp);

   fp = fopen("random.txt", "r");
   printf("Block\t%-8s\t%-8s\t%-8s\t%-8s\t%-8s\t%-8s\n\n","SS_time", "SS_swaps", "SS_compares","IS_time","IS_swaps","IS_compares");
   for(int block=0;block<500;block++) {
    int ss_swaps = 0, ss_compares = 0, is_swaps = 0, is_compares = 0;
    clock_t t,t1;
    
    int arr[(block+1)*100];
    int arr1[(block+1)*100];
    for(int i=0;i<(block+1)*100;i++){
        fscanf(fp, "%d", &arr[i]);
        arr1[i] = arr[i];
    }
    fseek(fp, 0, SEEK_SET); 
    t = clock();   
    selection_sort(arr,(block+1)*100, &ss_swaps, &ss_compares);
    t = clock() - t;
    t1 = clock();
    insertion_sort(arr1,(block+1)*100, &is_swaps, &is_compares);
    t1 = clock() - t1;
    double time_taken_selection_sort = ((double)t)/CLOCKS_PER_SEC; 
    double time_taken_insertion_sort = ((double)t1)/CLOCKS_PER_SEC; 
    printf("%d\t%-8f\t%-8d\t%-8d\t%-8f\t%-8d\t%-8d\n",(block+1),time_taken_selection_sort, ss_swaps, ss_compares, time_taken_insertion_sort, is_swaps, is_compares);
   }
    fclose(fp);
}