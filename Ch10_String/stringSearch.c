#include "stringSearch.h"

/* ========== Brute force ============ */
// 문자열 찾기 알고리즘 - 브루트포스 (고지식한 탐색방식)
int search_bf (char* txt, int txtLen, int start, char* pat, int patLen) {
    int i = 0, j = 0;
    for (i = start; i <= txtLen - )
}

/* ========== Rabin Karp ============= */
// 해시 함수 
int hash(char* str, int len) {

}
// 재해시 함수
int rehash(char* str, int pos, int len, int prevHash, int coefficient) {

}
// 문자열 찾기 알고리즘 - 라빈카프 (해시를 이용한 탐색방식)
int search_rk (char* txt, int txtLen, int start, char* pat, int patLen) {

}

/* =========== KMP ==================== */
void preprocessKmp(char* pat,  int patLen, int* border) {

}
// 문자열 찾기 알고리즘 - KMP (접두부/접미부 테이블을 이용한 효율적 이동 탐색 방식)
int search_kmp (char* txt, int txtLen, int start, char* pat, int patLen) {

}

/* ============ Boyer-Moore ============ */
void buildGoodTable(char* pat, int patLen, int* suffix, int* table) {

}
// 
void buildBadTable(char* pat, int patLen, int* table) {

}
// 문자열 찾기 알고리즘 - (나쁜문자 이동, 착한접미부 이동을 이용한 효율적 이동 탐색 방식)
int search_bm (char* txt, int txtLen, int start, char* pat, int patLen) {

}