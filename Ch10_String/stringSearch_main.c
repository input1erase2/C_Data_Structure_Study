#include <stdio.h>
#include <string.h>
#include "stringSearch.h"

#define MAX_BUFFER 512

int main(int argc, char** argv) {
    // File
    char* filePath;
    FILE* fp;
    // Strings
    char txt[MAX_BUFFER];
    char* pattern;
    int patternLen = 0;
    int line = 0;

    if (argc < 3) {
        printf("Usage: %s <FilePath> <Pattern String>\n", argv[0]);
        return 1;
    }
    filePath = argv[1];
    pattern = argv[2];
    patternLen = strlen(pattern);

    if ((fp = fopen(filePath, "r")) == NULL) {
        printf("Cannot open file : %s\n", filePath);
        return 1;
    }

    int option = 0;
    do {
        printf("Select option\n");
        printf("1. Bruteforce, 2. Rabin-Karp, 3. KMP, 4. Boyer-Moore\n");
        printf(">> ");
        scanf("%d", &option);
    } while (option >= 5 || option < 1);
    while (fgets(txt, MAX_BUFFER, fp) != NULL) {
        int pos = -1;
        switch (pos) {
        case 1: pos = search_bf(txt, strlen(txt), 0, pattern, patternLen); break;
        case 2: pos = search_rk(txt, strlen(txt), 0, pattern, patternLen); break;
        case 3: pos = search_kmp(txt,strlen(txt), 0, pattern, patternLen); break;
        case 4: pos = search_bm(txt, strlen(txt), 0, pattern, patternLen); break;
        }
        if (pos >= 0)
            printf("[Line: %d, Column: %d] >> %s\n", line, pos + 1, txt);
    }
    fclose(fp);
    return 0;
}