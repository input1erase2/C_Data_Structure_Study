#include "chaining.h"


HashTable* Hash_createTable(int size) {
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->table = (List*)malloc(sizeof(Node) * size);
    memset(newTable->table, 0, sizeof(List) * size);
    newTable->tableSize = size;
    return newTable;
}

Node* Hash_createNode(KeyType key, ValueType value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->key = (char*)malloc(strlen(key) + 1);
    strcpy(newNode->key, key);
    
    newNode->value = (char*)malloc(strlen(value) + 1);
    strcpy(newNode->value, value);
    
    newNode->next = NULL;
    
    return newNode;
}

/*전체 해시테이블의 각 엔트리를 순회하며 리스트 제거함수 호출하는 함수*/
void Hash_destroyTable(HashTable* ht) {
    // destroyList() 함수는 List 포인터 매개변수를 받으므로
    // 어렵더라도 배열 인덱스를 사용하지 않고 포인터 주소연산 사용했다
    for (int i = 0; i < ht->tableSize; ++i)
        Hash_destroyList((ht->table) + i);
    free(ht);
}

/*특정 엔트리를 제거하는 함수, 엔트리 내 노드들을 재귀호출을 통해 제거*/
void Hash_destroyList(List* l) {
    if (*l == NULL) return;
    if ((*l)->next != NULL) Hash_destroyList(&((*l)->next));
    Hash_destroyNode(*l);
}
/*특정 노드를 제거하는 함수, key, value 모두 문자열이므로 동적할당 해제한다.*/
void Hash_destroyNode(Node* node) {
    free(node->key);
    free(node->value);
    free(node);
}

ValueType Hash_get(HashTable* ht, KeyType key) {
    int addr = Hash_hash(key, strlen(key), ht->tableSize);
    List targetList = ht->table[addr];
    List target = NULL;
    if (targetList == NULL) return NULL;
    
    while (1) {
        // 발견했다면, target에 저장한 후 반복문 탈출한다.
        if (strcmp(targetList->key, key) == 0) {
            target = targetList;
            break;
        }
        // 해당 엔트리 내에 속한 마지막 노드까지 봐도 없다면 탈출한다.
        if (targetList->next == NULL) break;
        else targetList = targetList->next;
    }
    return target->value;
}

void Hash_set(HashTable* ht, KeyType key, ValueType newValue) {
    int addr = Hash_hash(key, strlen(key), ht->tableSize);
    Node* newNode = Hash_createNode(key, newValue);
    if (ht->table[addr] == NULL)
        ht->table[addr] = newNode;
    else {
        newNode->next =  ht->table[addr];
        ht->table[addr] = newNode;
        printf("Collision occured! >> Key(%s), Address(%d)\n", key, addr);
    }
}
/*자릿수 접기를 이용한 해싱 함수 */
int Hash_hash(KeyType key, int keyLen, int tableSize) {
    int hashValue = 0;
    // 전체 테이블 크기(12,289 == 14비트)를 사용하기 위해 3비트 좌측 시프트연산
    for (int i = 0; i < keyLen; ++i)
        hashValue = (hashValue << 3) + key[i];
    hashValue = hashValue % tableSize;
    return hashValue;
}
