#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int getMax(int a, int b) { return (a <= b) ? b: a; }

int LCS(char* a, char* b, int lenA, int lenB, int** table) {
	// 첫 행과 첫 열 초기화
	for (int i = 0; i <= lenA; ++i) table[0][i] = 0;
	for (int i = 0; i <= lenB; ++i) table[i][0] = 0;
	// 점화식에 따라서 DP방식으로 LCS 테이블을 채워나간다.
	for (int i = 1; i <= lenB; ++i) {
		for (int j = 1; j <= lenA; ++j) {
			if (b[i - 1] == a[j - 1])	// CASE 1. 문자가 같은 경우
				table[i][j] = table[i - 1][j - 1] + 1;
			else						// CASE 2. 문자가 다른 경우
				table[i][j] = getMax(table[i][j - 1], table[i - 1][j]);
		}
	}
	return table[lenB][lenA];
}

void traceBackLCS(char* a, char* b, int x, int y, int** table, char* lcs) {
	if (y == 0 || x == 0) return;
	
	// CASE 1. 왼쪽, 대각선위, 위보다 크다면 현재 셀 문자 저장 후 대각선 위로 이동
	if (table[y][x]		> table[y - 1][x]
		&& table[y][x]	> table[y][x - 1]
		&& table[y][x]	> table[y - 1][x - 1]) {
		char temp[100];		// char* temp = (char*)malloc(strlen(lcs) + 1);
		strcpy(temp, lcs);
		sprintf(lcs, "%c%s", a[x - 1], temp);	// LCS 문자열 앞에 한글자 붙인다.
		traceBackLCS(a, b, x - 1, y - 1, table, lcs);
	}
	// CASE 2. 왼쪽과는 같고 위보다 크다면 왼쪽으로 이동
	else if (table[y][x] > table[y - 1][x] && table[y][x] == table[y][x - 1])
		traceBackLCS(a, b, x - 1, y, table, lcs);
	else
		traceBackLCS(a, b, x, y - 1, table, lcs);
}

void printLCSTable(char* a, char* b, int lenA, int lenB, int **table) {
	printf("%4s", "");
	for (int i = 0; i < lenA; ++i)
		printf("%c ", a[i]);
	printf("\n");
	
	for (int y = 0; y <= lenB; ++y) {
		if (y == 0) printf("%2s", "");
		else printf("%-2c", b[y - 1]);
		
		for (int x = 0; x <= lenA; ++x)
			printf("%d ", table[y][x]);
		printf("\n");
	}
	printf("\n\n");
}

int main() {
	char* a = "GOOD MORNING.";
	char* b = "GUTEN MORGEN.";
	int lenA = strlen(a);
	int lenB = strlen(b);
	
	int** table = (int**)malloc(sizeof(int*) * (lenA + 1));
	for (int i = 0; i <= lenA; ++i)
		table[i] = (int*)malloc(sizeof(int) * (lenA + 1));
	
	int lcsLength = LCS(a, b, lenA, lenB, table);
	printf("Result = %d\n\n", lcsLength);
	
	printLCSTable(a, b, lenA, lenB, table);
	
	char* lcsString = (char*)calloc(lcsLength + 1, sizeof(char));
	// malloc으로 하니까 간헐적으로 뒤에 쓰레기값 출력돼서 calloc 사용
	traceBackLCS(a, b, lenA, lenB, table, lcsString);
	printf("LCS Traceback string = %s\n", lcsString);
	
	for (int i = 0; i <= lenA; ++i) free(table[i]);
	free(table);
	free(lcsString);
	
	return 0;
}