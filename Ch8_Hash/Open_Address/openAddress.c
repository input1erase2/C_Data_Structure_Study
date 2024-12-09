#include "openAddress.h"

HashTable* Hash_createTable(int size) {
    HashTable* newHashTable = (HashTable*)malloc(sizeof(HashTable));
    newHashTable->table = (Node*)malloc(sizeof(Node) * size);
    memset(newHashTable->table, 0, sizeof(Node) * size);
    newHashTable->tableSize = size;
    newHashTable->occupiedCount = 0;
    return newHashTable;
}

void Hash_destroyTable(HashTable* ht) {
    for (int i = 0; i < ht->tableSize; ++i)
        Hash_clearNode((ht->table) + i);
    free(ht->table);
    free(ht);
}

void Hash_clearNode(Node* node) {
    if (node->status == EMPTY) return;
    free(node->key);
    free(node->value);
}

void Hash_set(HashTable** ht, KeyType key, ValueType value) {
    double usage = (double)(*ht)->occupiedCount / (*ht)->tableSize;
    if (usage > 0.5) Hash_rehash(ht);

    int keyLen = strlen(key);
    int addr = Hash_hash1(key, keyLen, (*ht)->tableSize);
    int subAddr = Hash_hash2(key, keyLen, (*ht)->tableSize);
    // Collision 발생했다면, 이중해싱 사용
    while ((*ht)->table[addr].status != EMPTY &&
            strcmp((*ht)->table[addr].key, key) != 0) {
        printf("Collision Occured! --- Key: %s, Address: %d, "
            "sub-address: %d\n", key, addr, subAddr);
        addr = (addr + subAddr) % (*ht)->tableSize;
    }
    (*ht)->table[addr].key = (KeyType)malloc(keyLen + 1);
    strcpy((*ht)->table[addr].key, key);

    (*ht)->table[addr].value = (ValueType)malloc(strlen(value) + 1);
    strcpy((*ht)->table[addr].value, value);

    (*ht)->table[addr].status = OCCUPIED;
    ((*ht)->occupiedCount)++;
    
    printf("Key [%s] entered at address [%d]\n", key, addr);
}

ValueType Hash_get(HashTable* ht, KeyType key) {
    int keyLen = strlen(key);
    int addr = Hash_hash1(key, keyLen, ht->tableSize);
    int subAddr = Hash_hash2(key, keyLen, ht->tableSize);
    while (ht->table[addr].status != EMPTY &&
            strcmp(ht->table[addr].key, key) != 0)
        addr = (addr + subAddr) % (ht->tableSize);
    return ht->table[addr].value;
}
// 해시함수 1
int Hash_hash1(KeyType key, int keyLen, int size) {
    int ret = 0;
    for (int i = 0; i < keyLen; ++i)
        ret = (ret << 3) + key[i];
    ret %= size;
    return ret;
}
// 해시함수 2 
int Hash_hash2(KeyType key, int keyLen, int size) {
    int ret = 0;
    for (int i = 0; i < keyLen; ++i)
        ret = (ret << 2) + key[i];
    ret = ret % (size - 3);
    return ret + 1;
}

void Hash_rehash(HashTable** ht) {
    Node* oldTable = (*ht)->table;
    HashTable* newTable = Hash_createTable(((*ht)->tableSize) * 2);

    printf("\n[RE-HASH] Starts ---------- \n");
    // 기존 해시테이블 내 데이터를 다시 해싱해서 새로운 해시테이블에 저장
    for (int i = 0; i < (*ht)->tableSize; ++i)
        if (oldTable[i].status == OCCUPIED)
            Hash_set(&newTable, oldTable[i].key, oldTable[i].value);
    Hash_destroyTable(*ht); // 이전 해시테이블 삭제
    (*ht) = newTable;       // 새로운 해시테이블 주소 삽입
    printf("[Re-Hash] Ends ------ New Size: %d\n\n", newTable->tableSize);
}
