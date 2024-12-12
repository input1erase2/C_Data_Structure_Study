#include "stringSearch.h"

/* ========== Brute force ============ */
// 문자열 찾기 알고리즘 - 브루트포스 (고지식한 탐색방식)
int search_bf (char* txt, const int txtLen, char* pat, const int patLen) {
    for (int i = 0; i <= txtLen - patLen; ++i) {
        for (int j = 0; j < patLen; ++j)
            if (txt[i + j] != pat[j]) break;
        if (j >= patLen) return i;
    }
    return -1;
}

/* ========== Rabin Karp ============= */
// 해시 함수 
int hash(char* str, int len) {
    int hashValue = 0;
    for (int i = 0; i < len; ++i)
        hashValue = str[i] + (hashValue * 2);
    return hashValue;
}
// 재해시 함수
inline int rehash(char* str, int pos, int patLen, int prevHash, int coeff) {
    return (2 * (prevHash - coeff * str[pos - 1])) + str[pos + patLen - 1];
}
// 문자열 찾기 알고리즘 - 라빈카프 (해시를 이용한 탐색방식)
int search_rk (char* txt, const int txtLen, char* pat, const int patLen) {
    int coefficient = 1 << (patLen - 1);    // pow(2, patLen - 1); 오버플로되도 됨
    int hashTxt = hash(txt, txtLen);
    int hashPat = hash(pat, patLen);

    for (int i = 0; i <= txtLen - patLen; ++i) {
        // 해시값이 일치해도 문자열이 일치하는지 재확인해야함.
        if (hashTxt == hashPat) {
            int j = 0;
            for (; j < patLen; ++j)
                if (txt[i + j] != pat[j]) break;
            // 해시값도 일치, 문자열도 일치하므로 반환
            if (j >= patLen) return i;
        }
        // 해시값이 일치하지 않는다면 이전 해시값 활용해서 재해싱
        hashTxt = reHash(txt, i, patLen, hashTxt, coefficient);
    }
    return -1;
}

/* =========== KMP ==================== */
void preprocessKmp(char* pat, int patLen, int* table) {
    int i = 0;
    int j = -1;
    
    table[0] = -1;      // 첫번째 문자의 경계너비는 항상 -1
                        // 0은 이전 접두부가 존재하나, 경계가 없을 때를 의미한다.
    while (i < patLen) {
        while (j > -1 && pat[i] != pat[j]) j = table[j];
        table[++i] = ++j;
    }
}
// 문자열 찾기 알고리즘 - KMP (접두부/접미부 테이블을 이용한 효율적 이동 탐색 방식)
int search_kmp (char* txt, int txtLen, char* pat, int patLen) {
    // 이동거리 테이블 생성 및 계산
    int* table = (int*)calloc(patLen + 1, sizeof(int));
    preprocessKmp(pat, patLen, table);

    int txtPos  = 0;    // 원본 문자열 위를 움직이며 문자를 가리킬 커서
    int i       = 0;    // 이동거리 테이블 위를 움직이며 패턴 문주열 속 문자를 가리킬 커서
    int ret     = -1;

    while (txtPos < txtLen) {
        // 불일치 발생했다면, 이동거리 테이블에 따라 i를 조정
        while (i >= 0 && txt[txtPos] != pat[i]) i = table[i];
        txtPos++;
        i++;
        // 패턴 문자열을 발견했다면, 원본 문자열 내 해당 위치를 반환
        if (i == patLen) {
            ret = txtPos - i;
            break;
        }
    }
    free(table);
    return ret;
}

/* ============ Boyer-Moore ============ */
void buildGoodTable(char* pat, int patLen, int* posOfBorder, int* table) {
    // case 1. 착한 접미부가 패턴 내에 존재할 때
    int i = patLen;
    int j = patLen + 1;
    // 경계를 가질 수 없다면 시작위치에 패턴길이를 넣어준다.
    posOfBorder[i] = j;     // 빈문자열("")은 특별하게, 패턴길이 + 1을 넣는다.

    while (i > 0) {
        printf("[%s: %d] %s, i: %d, j = %d\n", __FUNCTION__, __LINE__, pat, i, j);
        while (j <= patLen && pat[i - 1] != pat[j - 1]) {
            if (table[i] == 0) table[j] = j - i;
            j = posOfBorder[j];
        }
        posOfBorder[--i] = --j;
    }
    j = posOfBorder[0]
}
// 
void buildBadTable(char* pat, int patLen, int* table) {

}
// 문자열 찾기 알고리즘 - (나쁜문자 이동, 착한접미부 이동을 이용한 효율적 이동 탐색 방식)
int search_bm (char* txt, int txtLen, int start, char* pat, int patLen) {

}