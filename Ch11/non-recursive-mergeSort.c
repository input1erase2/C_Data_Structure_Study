#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CNT 100000
#define MAX 1000000


// merge function, merge between a[s : m] and s[m+1 : e] 
void _mergeSort_nonRecursive(int* a, int s, int m, int e) {
    int lenL = m - s + 1;
    int lenR = e - m;
    
    // Make Left side buffer and initialize
    int bufL[lenL];
    for (int i = 0; i < lenL; ++i) bufL[i] = a[s + i];
    // Make Right side buffer and initialize
    int bufR[lenR];
    for (int i = 0; i < lenR; ++i) bufR[i] = a[m + 1 + i];
    
    int aPos = s, bPosL = 0, bPosR = 0;
    
    while (bPosL < lenL && bPosR < lenR)
        a[aPos++] = (bufL[bPosL] < bufR[bPosR]) ? bufL[bPosL++] : bufR[bPosR++];
    while (bPosL < lenL)
        a[aPos++] = bufL[bPosL++];
    while (bPosR < lenR)
        a[aPos++] = bufR[bPosR++];
}

int getMin(int x, int y) { return (x < y) ? x : y; }

void mergeSort_nonRecursive(int* a, int len) {
    for (int i = 1; i < len; i <<= 1) {
        int offset = i << 1;
        for (int j = 0; j < len - 1; j += offset) {
            int leftEnd = getMin(j + i - 1, len - 1);
            int rightEnd = getMin(j + offset - 1, len - 1);
            _mergeSort_nonRecursive(a, j, leftEnd, rightEnd);
        }
    }
}

void _mergeSort_recursive(int* a, int* b, int s, int e) {
    if (s >= e) return;
    
    int m = s + ((e - s) >> 1);     // s + (e - s) / 2
    
    _mergeSort_recursive(a, b, s, m);
    _mergeSort_recursive(a, b, m + 1, e);
    
    int aPosL = s, aPosR = s;
    int bPosL = 0, bPosR = 0;
    
    while (aPosR <= m) b[bPosR++] = a[aPosR++];
    while (bPosL < bPosR && aPosR <= e)
        a[aPosL++] = (a[aPosR] < b[bPosL]) ? b[bPosL++] : a[aPosR++];
    while (bPosL < bPosR) a[aPosL++] = b[bPosL++];
}

int mergeSort_recursive (int* a, int len) {
    int* b = (int*)calloc(len, sizeof(int));
    _mergeSort_recursive(a, b, 0, len - 1);
    free(b);
}

/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7, 3, 29, 23, 9, 18, 15};
    int n = sizeof(arr)/sizeof(arr[0]);
 
    printf("Given array is \n");
    printArray(arr, n);
 
    mergeSort_nonRecursive(arr, n);
 
    printf("\nSorted array is \n");
    printArray(arr, n);
    
    return 0;
}