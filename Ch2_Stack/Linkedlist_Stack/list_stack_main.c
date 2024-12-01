#include <stdio.h>
#include "list_stack.h"

int main() {
    Stack stk;
    initialize(&stk);

    for (int i = 1; i <= 11; ++i) push(&stk, 100 * i);

    // 스택 내 요소 전부 출력
    while (!isEmpty(&stk)) {
        printf("Peek --- %d\t", peek(&stk));
        printf("Popped --- %d\n", pop(&stk));
    }
    
    // 오류문 정상 출력 여부 확인을 위해 한 번 더 pop
    pop(&stk);
    
    return 0;
}