#ifndef __STRING_SEARCH_H_
#define __STRING_SEARCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 문자열 찾기 알고리즘 - 브루트포스 (고지식한 탐색방식)
int search_bf (char* txt, const int txtLen, char* pat, const int patLen); 
// 문자열 찾기 알고리즘 - 라빈카프 (해시를 이용한 탐색방식)
int search_rk (char* txt, const int txtLen, char* pat, const int patLen);
// 문자열 찾기 알고리즘 - KMP (접두부/접미부 테이블을 이용한 효율적 이동 탐색 방식)
int search_kmp (char* txt, const int txtLen, int start, char* pat, const int patLen); 
// 문자열 찾기 알고리즘 - (나쁜문자 이동, 착한접미부 이동을 이용한 효율적 이동 탐색 방식)
int search_bm (char* txt, const int txtLen, int start, char* pat, const int patLen); 

#endif