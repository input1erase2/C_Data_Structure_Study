#include <stdio.h>

#define TRUE    1
#define FALSE   0

int mySearch(int* arr, int s, int e, int target, int option) {
    if (s > e) return -1;
    
    int p;
    
    if (option) {   // Interpolation search (보간탐색)
        if (arr[s] > target || arr[e] < target) return -1;
        p = ((double)(target - arr[s]) / (arr[e] - arr[s]) * (e - s)) + s;
    } else {        // Binary search (이진탐색)
        p = s + ((e - s) >> 1);
    }
    
    if (arr[p] == target) return p;
    else if (arr[p] > target) return mySearch(arr, s, p -  1, target, option);
    else return mySearch(arr, p + 1, e, target, option);
}

int main() {
    int arr[] ={1, 3, 5, 7, 9,
        11, 13, 15, 17, 19, 21};
    
    int idx = mySearch(arr, 0, sizeof(arr) / sizeof(int) - 1, 18, TRUE);
    
    if (idx == -1) printf("Search Failed\n");
    else printf("Search Success >> arr[%d] = %d\n", idx, arr[idx]);

    return 0;
}