#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

void selection_sort(int arr[],int size) {
    for(int i=0;i<size-1;i++) {
        int min=i;
        for(int j=i+1;j<size;j++) 
            if(arr[j]<arr[min])
                min = j;
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }

}

void insertion_sort(int arr[],int n) {
    int i,key,j;
    for(int i=1;i<n;i++) {
        key = arr[i];
        j=i-1;
        while(j>=0 && arr[j]>key) {
            arr[j+1] = arr[j];
            j=j-1;
        }
        arr[j+1] = key;
    }
}


void main() {

    FILE *fp;
    fp  = fopen ("exp1b.txt", "w");
    srand((unsigned int) time(NULL));
    for(int block=0;block<1000;block++) {
        for(int i=0;i<100;i++) {
            int number = (int)(((float) rand() / (float)(RAND_MAX))*100000);
            fprintf(fp,"%d ",number);
        }
        fputs("\n",fp);
    }
    fclose (fp);

   fp = fopen("exp1b.txt", "r");
   printf("Block\tSelection_sort\tInsertion_sort\n");
   for(int block=0;block<500;block++) {
    clock_t t,t1;
    
    int arr[(block+1)*100];
    int arr1[(block+1)*100];
    for(int i=0;i<(block+1)*100;i++){
        fscanf(fp, "%d", &arr[i]);
        arr1[i] = arr[i];
    }
    fseek(fp, 0, SEEK_SET); 
    t = clock();   
    selection_sort(arr,(block+1)*100);
    t = clock() - t;
    t1 = clock();
    insertion_sort(arr1,(block+1)*100);
    t1 = clock() - t1;
    double time_taken_selection_sort = ((double)t)/CLOCKS_PER_SEC; 
    double time_taken_insertion_sort = ((double)t1)/CLOCKS_PER_SEC; 
    printf("%d\t%f\t%f\n",(block+1),time_taken_selection_sort,time_taken_insertion_sort);
   }
    fclose(fp);
}