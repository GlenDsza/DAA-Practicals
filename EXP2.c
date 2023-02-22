#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

void quickSort(int arr[], int left, int right) {
  if (left < right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
      if (arr[j] < pivot) {
        i++;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;

    int p = i + 1; // p is the pivot element

    quickSort(arr, left, p - 1);
    quickSort(arr, p + 1, right);
  }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else  {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


void main() {
    FILE *fp;
    fp  = fopen ("exp2.txt", "w");
    srand((unsigned int) time(NULL));
    for(int block=0;block<1000;block++) {
        for(int i=0;i<100;i++) {
            int number = (int)(((float) rand() / (float)(RAND_MAX))*100000);
            fprintf(fp,"%d ",number);
        }
        fputs("\n",fp);
    }
    fclose (fp);

   fp = fopen("exp2.txt", "r");
   printf("Block\tQuick_sort\tMerge_sort\n");
   for(int block=0;block<1000;block++) {
    clock_t t,t1;
    
    int arr[(block+1)*100];
    int arr1[(block+1)*100];
    for(int i=0;i<(block+1)*100;i++){
        fscanf(fp, "%d", &arr[i]);
        arr1[i] = arr[i];
    }
    fseek(fp, 0, SEEK_SET); 
    t = clock();   
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    t = clock() - t;
    t1 = clock();
    n = sizeof(arr1) / sizeof(arr1[0]);
    mergeSort(arr1, 0, n - 1);
    t1 = clock() - t1;
    double time_taken_quick_sort = ((double)t)/CLOCKS_PER_SEC; 
    double time_taken_merge_sort = ((double)t1)/CLOCKS_PER_SEC; 
    printf("%d\t%f\t%f\n",(block+1),time_taken_quick_sort, time_taken_merge_sort);
   }
    fclose(fp);
}