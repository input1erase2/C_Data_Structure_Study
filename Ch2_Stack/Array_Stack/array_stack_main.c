#include <stdio.h>
#include "array_stack.h"

int main() {
    Stack stk;
    initialize(&stk);

    // 크기 10짜리 스택, 일부러 11개 삽입해서 push 오류문 1번 출력
    for (int i = 1; i <= 11; ++i) push(&stk, 100 * i);

    // 스택 내 요소 전부 출력
    while (!isEmpty(&stk))
        printf("Popped --- %d\n", pop(&stk));
    
    return 0;
}