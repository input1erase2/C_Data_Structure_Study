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
        printf("[Select option]\n");
        printf("[1. Bruteforce, 2. Rabin-Karp, 3. KMP, 4. Boyer-Moore]\n");
        printf(" >> ");
        scanf("%d", &option);
    } while (option >= 5 || option < 1);
    while (fgets(txt, MAX_BUFFER, fp) != NULL) {
        int pos = -1;
        switch (option) {
        case 1: pos = search_bf(txt, strlen(txt), pattern, patternLen); break;
        case 2: pos = search_rk(txt, strlen(txt), pattern, patternLen); break;
        case 3: pos = search_kmp(txt,strlen(txt), pattern, patternLen); break;
        case 4: pos = search_bm(txt, strlen(txt), pattern, patternLen); break;
        }
        if (pos >= 0) printf("[Line: %d, Column: %d] >> %s\n", line, pos + 1, txt);
        line++;
    }
    fclose(fp);
    return 0;
}

/*
// 브루트포스 테스트  (Faithful)
Select option                                                                                              
1. Bruteforce, 2. Rabin-Karp, 3. KMP, 4. Boyer-Moore                                                       
>> 1
[Line: 17177, Column: 9] >> Prv27:6 Faithful are the wounds of a friend; but the kisses of an enemy are deceitful.
[Line: 29647, Column: 9] >> 1Th5:24 Faithful is he that calleth you, who also will do it.
[Line: 31030, Column: 97] >> Rev19:11 And I saw heaven opened, and behold a white horse; and he that sat upon him was called Faithful and True, and in righteousness he doth judge and make war.


// Rabin-Karp 테스트 (Righteousness)
[Select option]
[1. Bruteforce, 2. Rabin-Karp, 3. KMP, 4. Boyer-Moore]
 >> 2
[Line: 15286, Column: 10] >> Psa85:13 Righteousness shall go before him; and shall set us in the way of his steps.
[Line: 16755, Column: 9] >> Prv13:6 Righteousness keepeth him that is upright in the way: but wickedness overthroweth the sinner.
[Line: 16808, Column: 10] >> Prv14:34 Righteousness exalteth a nation: but sin is a reproach to any people.


// KMP 테스트 ("The Prince of Peace")
[Select option]
[1. Bruteforce, 2. Rabin-Karp, 3. KMP, 4. Boyer-Moore]
 >> 3
[Line: 17837, Column: 200] >> Isa9:6 For unto us a child is born, unto us a son is given: and the government shall be upon his shoulder: and his name shall be called Wonderful, Counsellor, The mighty God, The everlasting Father, The Prince of Peace.


// Boyer-Moore 테스트 ("Get wisdom")
[Select option]
[1. Bruteforce, 2. Rabin-Karp, 3. KMP, 4. Boyer-Moore]
 >> 4
[Line: 16497, Column: 8] >> Prv4:5 Get wisdom, get understanding: forget it not; neither decline from the words of my mouth.
*/