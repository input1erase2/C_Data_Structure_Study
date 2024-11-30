#include <stdio.h>
#include "single_linked_list.h"


void printList(List* list) {
    Node* cur = list->head->next;
    int size = getCount(list);
    printf("Current total node count = %d\n", size);
    for (int i = 0; i < size; ++i) {
        printf("List[%d] >> %4d --- (", i, cur->data);

        if (cur->next) printf("%4d)\n", cur->next->data);
        else printf("NULL)\n");

        cur = cur->next;
    }
    printf("\n\n");
}

int main() {
    // 단방향 연결리스트 생성
    printf("[Test] Add nodes ========\n");
    List list;
    makeList(&list);
    // 연결리스트에 10, 20, ... , 70 입력 
    for (int i = 0; i < 7; ++i) addNode(&list, 10*(i+1));
    printList(&list);

    // list->cur를 움직이며 '20'을 찾고 삭제
    printf("[Test] Remove data '20' ========\n");
    int data;
    if (moveCurFirst(&list, &data)) {
        if (data == 20) removeCur(&list);
        while (moveCurNext(&list, &data))
            if (data == 20) removeCur(&list);
    }
    printList(&list);

    // 한 번에 '30'을 찾고 삭제
    printf("[Test] Remove data '30' ========\n");
    removeNode(&list, 30);
    printList(&list);

    // Tail node 삭제
    printf("[Test] Remove tail node ========\n");
    removeNode(&list, 10);
    printList(&list);

    // 연결리스트 삭제
    removeList(&list);
    printf("[List removal Complete]\n");
    
    return 0;
}