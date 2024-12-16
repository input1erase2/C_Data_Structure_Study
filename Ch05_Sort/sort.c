#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CNT 25000
#define MAX 1000000

#define TRUE    1
#define FALSE   0

typedef unsigned char bool;
typedef unsigned long long ULL;


void printSamples(int* arr, ULL t) {
    printf(" >> ");
    for (int i = 0; i < 10; ++i) printf("%4d ", arr[i]);
    printf("\nTook time: %lld (ms)\n\n", t);
}

void mySwap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int findMidPos(const int* arr, int a, int b, int c) { 
    return arr[a] > arr[b] ?
        ((arr[a] > arr[c]) ? ((arr[b] > arr[c]) ? c : b) : a) :
        ((arr[b] > arr[c]) ? ((arr[a] > arr[c]) ? c : a) : b);
}

// ================= BUBBLE SORT ==================== //

void bubbleSort(int* arr, int len) {
    for (int i = 0; i < len - 1; ++i) {
        bool isChanged = FALSE;
        for (int j = 0; j < len - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                mySwap(&arr[j], &arr[j + 1]);
                isChanged = TRUE;
            }
        }
        if (!isChanged) break;
    }
}

// ================================================== //
// ================= SELECTION SORT ================= //

void selectSort(int* arr, int len) {
    for (int i = 0, target = i; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j)
            if (arr[target] > arr[j]) target = j;
        mySwap(&arr[target], &arr[i]);
    }
}

// ================================================== //
// ================= INSERTION SORT  ================ //

void insertSort(int* arr, int len) {
    for (int i = 1; i < len; ++i) {
        int j = i - 1, target = arr[i];
        for (; j >= 0 && arr[j] > target; --j) arr[j + 1] = arr[j];
        arr[j + 1] = target;
    }
}

// ================================================== //
// =================== SHELL SORT  ================== //

void shellSort(int* arr, int len) {
    int h;
    for (h = 1; h < len / 9; h = 3 * h + 1);

    for (; h > 0; h /= 3) {
        for (int i = h; i < len; ++i) {
            int j = i - h, target = arr[i];
            for (; j >= 0 && arr[j] > target; j -= h) arr[j + h] = arr[j];
            arr[j + h] = target;
        }
    }
}

// ================================================== //
// =================== MERGE SORT  ================== //

void _mergeSort(int* arr, int* buf, int s, int e) {
    if (s >= e) return;

    int m = s + (e - s) / 2;
    
    _mergeSort(arr, buf, s, m);
    _mergeSort(arr, buf, m + 1, e);

    int arrCurL = s, arrCurR = s;   // Cursor for Data array
    int bufCurL = 0, bufCurR = 0;   // Cursor for Buffer

    // 1. Copy left-half of array to buffer (and make 'bufCurR', 'arrCurR' bigger)
    while (arrCurR <= m) buf[bufCurR++] = arr[arrCurR++];
    // 2. Compare copied data in buffer and right-half of array
    while (bufCurL < bufCurR && arrCurR <= e)
        arr[arrCurL++] = (buf[bufCurL] <= arr[arrCurR]) ? buf[bufCurL++] : arr[arrCurR++];
    // 3. If there is leftover data in buffer, move to data array
    while (bufCurL < bufCurR) arr[arrCurL++] = buf[bufCurL++];
}

void mergeSort(int* arr, int len) {
    int* buf = (int *)calloc(len, sizeof(int));
    _mergeSort(arr, buf, 0, len - 1);
    free(buf);
}


// ================================================== //
// =================== QUICK SORT  ================== //

void quickSort(int* arr, int s, int e) {
    if (s >= e) return;

    int p = findMidPos(arr, s, s + (e - s) / 2, e);
    mySwap(&arr[s], &arr[p]);
    p = s;

    int l = s + 1, r = e;
    while (l <= r) {
        while (l <= e && arr[p] >= arr[l]) l++;
        while (r > s && arr[p] <= arr[r]) r--;   // no eqation, because of pivot
        if (l < r) mySwap(&arr[l], &arr[r]);
    }
    mySwap(&arr[p], &arr[r]);
    quickSort(arr, s, r - 1);
    quickSort(arr, r + 1, e);
}

void stackQuickSort(int* arr, int len) {
    int stk[25] = {0, };    // avg~worst space complexity for stack is log_2(n)
    int top = -1;
    int s = 0, e = len - 1;
    
    stk[++top] = s;
    stk[++top] = e;

    while (top >= 0) {
        int r = e = stk[top--];
        int l = s = stk[top--];
        int p = arr[l + (r - l) / 2];   // [Caution] pivot should be a value not position or index.
        while (l <= r) {
			while (arr[p] > arr[l]) l++;    
            while (arr[p] < arr[r]) r--;
            if (l <= r) mySwap(&arr[l++], &arr[r--]);
        }
        // Push large partition first so that process smaller one first
        int leftLen = r - s, rightLen = e - l;
        if (leftLen > rightLen) {
            if (leftLen > 0)    { stk[++top] = s; stk[++top] = r; } // if s < r
            if (rightLen > 0)   { stk[++top] = l; stk[++top] = e; } // if l < e
        } else {
            if (rightLen > 0)   { stk[++top] = l; stk[++top] = e; } // if l < e
            if (leftLen > 0)    { stk[++top] = s; stk[++top] = r; } // if s < r
        }
    }
}

// ================================================== //
// =================== HEAP SORT  =================== //

// Heapsort - recursive version
void __heapSort(int* arr, int len, int target) {
    int lc = 2 * target + 1, rc = lc + 1;
    if (lc >= len) return;
    int c = (rc < len && arr[rc] > arr[lc]) ? rc : lc;
    if (arr[target] >= arr[c]) return;
    mySwap(&arr[target], &arr[c]);  
    __heapSort(arr, len, c);    // target = c;
}

// Heapsort - non-recursive version
void _heapSort(int* arr, int len, int target) {
    int lc, rc, c;     // left child, right child, chosen child
    while (target < (len / 2)) {
        lc = 2 * target + 1, rc = lc + 1; 
        c = (rc < len && arr[rc] > arr[lc]) ? rc : lc; // choose bigger child
        if (arr[target] >= arr[c]) break;
        mySwap(&arr[target], &arr[c]);
        target = c;
    }
}

void heapSort(int* arr, int len) {
    for (int i = (len - 1) / 2; i >= 0; --i) {
		_heapSort(arr, len, i);
		// __heapSort(arr, len, i);
	}
    for (int i = len - 1; i > 0; --i) {
        mySwap(&arr[i], &arr[0]);	// swap last node <-> root node
        _heapSort(arr, i, 0);		// arrange heap for moved node
		// __heapSort(arr, len, i);
    }
}

// ================================================== //


int main() {
    srand(time(0));
    
    long long s = 0UL, e = 0UL;

    int arr[CNT];
    for (int i = 0; i < CNT; ++i) arr[i] = rand() % MAX;

    int copyArr[7][CNT];
    for (int i = 0; i < 7; ++i) memcpy(&copyArr[i], arr, sizeof(arr));

    printf("[Before]"); printSamples(arr, 0);

    s = (ULL)clock();
    bubbleSort(copyArr[0], CNT);
    e = (ULL)clock();
    printf("[Bubble Sort]"); printSamples(copyArr[0], e - s);

    s = (ULL)clock();
    selectSort(copyArr[1], CNT);
    e = (ULL)clock();
    printf("[Select Sort]"); printSamples(copyArr[1], e - s);

    s = (ULL)clock();
    insertSort(copyArr[2], CNT);
    e = (ULL)clock();
    printf("[Insert Sort]"); printSamples(copyArr[2], e - s);

    s = (ULL)clock();
    shellSort(copyArr[3], CNT);
    e = (ULL)clock();
    printf("[Shell Sort]"); printSamples(copyArr[3], e - s);

    s = (ULL)clock();
    mergeSort(copyArr[4], CNT);
    e = (ULL)clock();
    printf("[Merge Sort]"); printSamples(copyArr[4], e - s);

    s = (ULL)clock();
    quickSort(copyArr[5], 0, CNT - 1);
    e = (ULL)clock();
    printf("[Quick Sort]"); printSamples(copyArr[5], e - s);

    s = (ULL)clock();
    heapSort(copyArr[6], CNT);
    e = (ULL)clock();
    printf("[Heap Sort]"); printSamples(copyArr[6], e - s);
    
    
    return 0;
}

/*

[Before] >> 17640 25758 30002 26240 4836 4223 17479 17499 20040 15538
Took time: 0 (ms)

[Bubble Sort] >>    0    0    3    3    4    4    5    6    7    7
Took time: 1728 (ms)

[Select Sort] >>    0    0    3    3    4    4    5    6    7    7
Took time: 425 (ms)

[Insert Sort] >>    0    0    3    3    4    4    5    6    7    7
Took time: 166 (ms)

[Shell Sort] >>    0    0    3    3    4    4    5    6    7    7
Took time: 4 (ms)

[Merge Sort] >>    0    0    3    3    4    4    5    6    7    7
Took time: 3 (ms)

[Quick Sort] >>    0    0    3    3    4    4    5    6    7    7
Took time: 3 (ms)

[Heap Sort] >>    0    0    3    3    4    4    5    6    7    7
Took time: 4 (ms)

*/