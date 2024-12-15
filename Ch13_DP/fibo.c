#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

ull getFibo(int n) {
	if (n == 0 || n == 1) return n;
	
	ull* table = (ull*)malloc(sizeof(ull) * n);
	table[0] = table[1] = 1;
	for (int i = 2; i < n; ++i) table[i] = table[i - 1] + table[i - 2];
	
	return table[n - 1];
}

int main() {
	int n = 48;
	printf("Fibonacci(%d) = %lld\n\n", n, getFibo(n));
	return 0;
}