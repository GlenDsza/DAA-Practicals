#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

void quickSort(int arr[], int left, int right, int *qs_swaps, int *qs_compares) {  
  if (left < right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
      (*qs_compares)++;  
      if (arr[j] < pivot) {
        i++;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        (*qs_swaps)++;
      }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    (*qs_swaps)++; //icrement no. of swaps

    int p = i + 1; // p is the pivot element

    quickSort(arr, left, p - 1, qs_swaps, qs_compares);
    quickSort(arr, p + 1, right, qs_swaps, qs_compares);
  }
}

void merge(int arr[], int l, int m, int r, int *ms_swaps, int *ms_compares) {
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
        (*ms_compares)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else  {
            arr[k] = R[j];
            j++;
        }
        (*ms_swaps)++;
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        (*ms_swaps)++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        (*ms_swaps)++;
    }
}

void mergeSort(int arr[], int l, int r, int *ms_swaps, int *ms_compares) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, ms_swaps, ms_compares);
        mergeSort(arr, m + 1, r, ms_swaps, ms_compares);
        merge(arr, l, m, r, ms_swaps, ms_compares);
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
   printf("Block\t%-8s\t%-8s\t%-8s\t%-8s\t%-8s\t%-8s\n\n","QS_time", "QS_swaps", "QS_compares","MS_time","MS_swaps","MS_compares");
   for(int block=0;block<1000;block++) {
    int qs_swaps = 0, qs_compares = 0, ms_swaps = 0, ms_compares = 0;
    clock_t t,t1;
    
    int arr[(block+1)*100];
    int arr1[(block+1)*100];
    for(int i=0;i<(block+1)*100;i++) {
        fscanf(fp, "%d", &arr[i]);
        arr1[i] = arr[i];
    }
    fseek(fp, 0, SEEK_SET); 
    t = clock();   
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1, &qs_swaps, &qs_compares);
    t = clock() - t;
    t1 = clock();
    n = sizeof(arr1) / sizeof(arr1[0]);
    mergeSort(arr1, 0, n - 1, &ms_swaps, &ms_compares);
    t1 = clock() - t1;
    double time_taken_quick_sort = ((double)t)/CLOCKS_PER_SEC; 
    double time_taken_merge_sort = ((double)t1)/CLOCKS_PER_SEC; 
    printf("%d\t%-8f\t%-8d\t%-8d\t%-8f\t%-8d\t%-8d\n",(block+1),time_taken_quick_sort, qs_swaps, qs_compares, time_taken_merge_sort, ms_swaps, ms_compares);
   }
    fclose(fp);
}