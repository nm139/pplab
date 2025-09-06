#include <stdio.h>  
#include <stdlib.h> 
#include <omp.h> 
#include <time.h> 

void merge(int* arr, int l, int m, int r) { 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
    int* L = (int*)malloc(n1 * sizeof(int)); 
    int* R = (int*)malloc(n2 * sizeof(int)); 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j]; 
    i = 0; j = 0; k = l; 
    while (i < n1 && j < n2) { 
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++]; 
    } 
    while (i < n1) arr[k++] = L[i++]; 
    while (j < n2) arr[k++] = R[j++]; 
    free(L); 
    free(R); 
} 

void mergeSortSequential(int* arr, int l, int r) { 
    if (l < r) { 
        int m = (l + r) / 2; 
        mergeSortSequential(arr, l, m); 
        mergeSortSequential(arr, m + 1, r); 
        merge(arr, l, m, r); 
    } 
} 

void mergeSortParallel(int* arr, int l, int r, int depth) { 
    if (l < r) { 
        int m = (l + r) / 2; 
        if (depth <= 0) { 
            mergeSortSequential(arr, l, m); 
            mergeSortSequential(arr, m + 1, r); 
        } 
        else { 
            #pragma omp parallel sections 
            { 
                #pragma omp section 
                mergeSortParallel(arr, l, m, depth - 1); 
                #pragma omp section 
                mergeSortParallel(arr, m + 1, r, depth - 1); 
            } 
        } 
        merge(arr, l, m, r); 
    } 
} 
  
int isSorted(int* arr, int n) { 
    for (int i = 1; i < n; i++) { 
        if (arr[i - 1] > arr[i]) return 0; 
    } 
    return 1; 
} 
 
int main() { 
    int n = 1000000; 
    int* arrSeq = (int*)malloc(n * sizeof(int)); 
    int* arrPar = (int*)malloc(n * sizeof(int)); 
  
    srand(42); 
    for (int i = 0; i < n; i++) { 
        arrSeq[i] = rand() % 100000; 
        arrPar[i] = arrSeq[i]; 
    } 
  
    double start = omp_get_wtime(); 
    mergeSortSequential(arrSeq, 0, n - 1); 
    double end = omp_get_wtime(); 
    double timeSeq = end - start; 
 
    start = omp_get_wtime(); 
    mergeSortParallel(arrPar, 0, n - 1, 4); 
    end = omp_get_wtime(); 
    double timePar = end - start; 
  
    printf("Sequential sort time: %.6f seconds\n", timeSeq); 
    printf("Parallel sort time  : %.6f seconds\n", timePar); 
    printf("Speedup             : %.2fx\n", timeSeq / timePar); 
    if (!isSorted(arrSeq, n))
        printf("Sequential sort failed!\n"); 
    if (!isSorted(arrPar, n))
        printf("Parallel sort failed!\n"); 
    free(arrSeq); 
    free(arrPar); 
    return 0; 
} 