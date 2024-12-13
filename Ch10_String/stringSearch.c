#include "stringSearch.h"

/* [주의] 코드가 전체적으로 눈에 확 들어오지 않을 것이다.
빠른 처리속도를 위해 각 함수가 논리적으로 동작하는 흐름 또는 들었던 설명과는 다르게 작성됐기 때문이다.
결과적으로 같은 접미사/위치/이동거리 테이블을 만들어서 같은 결과를 만들지만, 한 눈에 따라가기 힘들다.
그러므로, 직접 예시문자열을 만들어 손으로 흐름을 한 번만 따라가보면 이해가 좀 더 쉬워질 것이다.
중요한것은 각 문자열탐색 방식이 어떤 순서로 동작하고, 평균/최악 시간복잡도가 어떻게 되는지다.
*/

/* ========== Brute force ============ */
// 문자열 찾기 알고리즘 - 브루트포스 (고지식한 탐색방식)
int search_bf (char* txt, const int txtLen, char* pat, const int patLen) {
    for (int i = 0; i <= txtLen - patLen; ++i) {
        int j = 0;
        for (; j < patLen; ++j)
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
        hashValue = str[i] + (hashValue << 1);
    return hashValue;
}
// 재해시 함수
int rehash(char* str, int pos, int patLen, int prevHash, int coeff) {
    return (2 * (prevHash - coeff * str[pos - 1])) + str[pos + patLen - 1];
}
// 문자열 찾기 알고리즘 - 라빈카프 (해시를 이용한 탐색방식)
int search_rk (char* txt, const int txtLen, char* pat, const int patLen) {
    int coefficient = 2 << (patLen - 1);    // pow(2, patLen - 1); 오버플로되도 됨
    int hashTxt = hash(txt, patLen);
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
        hashTxt = rehash(txt, i, patLen, hashTxt, coefficient);
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
int search_kmp (char* txt, const int txtLen, char* pat, const int patLen) {
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
// 착한 접미부 테이블 만들기 함수
void buildGoodTable(char* pat, int patLen, int* posOfBorder, int* table) {
    // case 1. 착한 접미부가 패턴 내에 존재할 때
    int i = patLen;
    int j = patLen + 1;
    // 경계를 가질 수 없다면 시작위치에 패턴길이를 넣어준다.
    posOfBorder[i] = j;     // 빈문자열("")은 특별하게, 패턴길이 + 1을 넣는다.

    while (i > 0) {
        // printf("[%s: %d] Pattern: '%s', i: %d, j = %d\n", __FUNCTION__, __LINE__, pat, i, j);
        while (j <= patLen && pat[i - 1] != pat[j - 1]) {
            if (table[j] == 0) table[j] = j - i;
            j = posOfBorder[j];
        }
        posOfBorder[--i] = --j;
    }

    // Case 2. 착한 접미부의 접미부가 패턴 접두부에 존재할 때
    // 1-1. 가장 첫 '접미부의 가장 넓은 경계의 시작넓이'(posOfBorder[0])를 
    j = posOfBorder[0];
    for (i = 0; i <= patLen; ++i) {
        // 1-2. 이동거리가 '0'으로 저장된 곳마다 가져온다.
        if (table[i] == 0) table[i] = j;
        // 2. 위에서 가져온 값(j)이 경계의 너비(i)와 같아질 때, j를 갱신한다.
        if (i == j) j = posOfBorder[j];
    }
}
// 나쁜문자 테이블 만들기 함수
void buildBadTable(char* pat, int patLen, int* table) {
    memset(table, -1, sizeof(table));
    for (int i = 0; i < patLen; ++i) table[pat[i]] = i;
}

void printBadTable(int* badTable, int tableLen) {
    for (int i = 0; i < tableLen; ++i)
        if (badTable[i]) printf("'%C' : %d, ", (char)i, badTable[i]);
    printf("\n");
}

void printGoodTable(int* goodTable, int* posOfBorder, char* pat, int tableLen) {
    for(int i = 0; i < tableLen; i++)
        if (goodTable[i] > 0)
            printf("'%C': %d(%d), ", pat[i], goodTable[i], posOfBorder[i]);
    printf("\n");
}

int getMax(int a, int b) {
    return ( a < b ) ? b : a;
}

// 문자열 찾기 알고리즘 - (나쁜문자 이동, 착한접미부 이동을 이용한 효율적 이동 탐색 방식)
int search_bm (char* txt, const int txtLen, char* pat, const int patLen) {
    int badCharTable[128];
    int* goodSuffixTable = (int*)calloc(patLen + 1, sizeof(int));
    int* posOfBorder = (int*)calloc(patLen + 1, sizeof(int));

    buildBadTable(pat, patLen, badCharTable);
    buildGoodTable(pat, patLen, posOfBorder, goodSuffixTable);

    // printBadTable(badCharTable, 128);
    // printGoodTable(goodSuffixTable, posOfBorder, pat, patLen + 1);

    int i = 0, j = 0;
    int ret = -1;
    while (i <= txtLen - patLen) {
        j = patLen - 1;
        while (j >= 0 && pat[j] == txt[i + j]) j--;

        if (j >= 0)  // 나쁜문자 스킵 vs 착한 접미사 스킵 중 더 이득인것을 결정한다.
            i += getMax(j - badCharTable[txt[i + j]], goodSuffixTable[j + 1]);
        else { ret = i; break; }   // 원하는 패턴 문자열을 찾아냄
    }

    free(posOfBorder);
    free(goodSuffixTable);

    return ret;
}