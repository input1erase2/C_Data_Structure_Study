#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned long long ull;

#define CNT 1000001

// RAND_MAX 이상의 큰 수 범위의 랜덤(random) 값 구하기: https://swjman.tistory.com/26
#define RANDOM(__min__, __max__) \
	((int)(((double)((rand()<<15) | rand())) / ((RAND_MAX<<15 | RAND_MAX) + 1) \
		* (((__max__) + 1) - (__min__))) + (__min__))

void _recursiveHelper(int* a, int* b, int s, int e) {
	if (s >= e) return;
	
	int m = s + ((e - s) >> 1);
	
	_recursiveHelper(a, b, s, m);
	_recursiveHelper(a, b, m + 1, e);
	
	int aPosL = s, aPosR = s;
	int bPosL = 0, bPosR = 0;
	
	while (aPosR <= m) b[bPosR++] = a[aPosR++];
	while (bPosL < bPosR && aPosR <= e)
		a[aPosL++] = (a[aPosR] < b[bPosL]) ? a[aPosR++] : b[bPosL++];
	while (bPosL < bPosR) a[aPosL++] = b[bPosL++];
}

void mergeSort_recursive(int* a, int len) {
	int* b = (int*)malloc(sizeof(int) * len);
	_recursiveHelper(a, b, 0, len - 1);
	free(b);
}


void _nonRecursiveHelper(int* a, int s, int m, int e) {
	int lenL = m - s + 1;		// 왼쪽 부분배열의 길이
	int lenR = e - m;			// 오른쪽 부분배열의 길이
		
	int bufL[lenL], bufR[lenR]; // 부분배열 왼쪽/오른쪽 절반 저장할 버퍼 생성 및 초기화
	
	for (int i = 0; i < lenL; ++i) bufL[i] = a[s + i];
	for (int i = 0; i < lenR; ++i) bufR[i] = a[m + 1 + i];
	
	int aPos = s, bPosL = 0, bPosR = 0;
	// 왼쪽 버퍼와 오른쪽 버퍼를 서로 비교하면서 더 작은쪽을 원본에 저장
	while (bPosL < lenL && bPosR < lenR)
		a[aPos++] = (bufL[bPosL] <= bufR[bPosR]) ? bufL[bPosL++] : bufR[bPosR++];
	while (bPosL < lenL)
		a[aPos++] = bufL[bPosL++];
	while (bPosR < lenR)
		a[aPos++] = bufR[bPosR++];
}

int getMin(int a, int b) { return (a < b) ? a : b; }

void mergeSort_nonRecursive(int* a, int len) {
	// Divide the array into blocks of size = [1, 2, 4, 8, 16…]
	for (int size = 1; size < len; size *= 2) {
		for (int leftStart = 0; leftStart < len - 1; leftStart += size * 2) {
			int leftEnd = getMin(leftStart + size - 1, len - 1);
			int rightEnd = getMin(leftStart + (2 * size) - 1, len - 1);
			_nonRecursiveHelper(a, leftStart, leftEnd, rightEnd);
		}
	}
}


int main() {
	srand(time(NULL));
	
	int a[CNT];
	for (int i = 0; i < CNT; ++i) a[i] = RANDOM(1, 20000000);
	
	printf("[Original] >> ");
	for (int i = 0; i < 15; ++i) printf("%3d ", a[i]);
	printf("\n");
	
	int b[CNT];
	memcpy(b, a, sizeof(a));
	
	ull start = 0ul, end = 0ul;
	
	start = (ull)clock();
	mergeSort_recursive(b, CNT);
	end = (ull)clock();
	
	printf("[Recursive] >> ");
	for (int i = 0; i < 15; ++i) printf("%3d ", b[i]);
	printf("\n");
	printf("Time cost = %lld\n\n", end - start);
	
	
	int c[CNT];
	memcpy(c, a, sizeof(a));
	
	start = (ull)clock();
	mergeSort_nonRecursive(c, CNT);
	end = (ull)clock();
	
	printf("[Non-Recursive] >> ");
	for (int i = 0; i < 15; ++i) printf("%3d ", c[i]);
	printf("\n");
	printf("Time cost = %lld\n\n", end - start);
	
	return 0;
}

/*
[Recursive] >>   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
Time cost = 66
(93.75 ms cpu time, 13584 KB mem used)

[Non-Recursive] >>   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
Time cost = 73
(109.4 ms cpu time, 13580 KB mem used)


[읽어보면 좋은 주제]: Merge sort Implementation - Recursive vs Iterative
Link: https://stackoverflow.com/q/66695718

Most libraries use a variation of insertion sort and bottom up merge sort for a stable sort (i.e. C++ std::stable_sort()).
I've benchmarked naive top down(Recursive) and bottom up(Iterative) merge sort on my system,
and bottom up is slightly faster. Any advantage to cached data is offset by stack operations, versus global optimizations which tend to keep pointers and indexes in registers.

*/