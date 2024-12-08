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
    
    newNode->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(newNode->key, key);
    
    newNode->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(newNode->value, value);
    
    newNode->next = NULL;
    
    return NULL;
}

void Hash_destroyTable(HashTable* ht) {
    for (int i = 0; i < ht->tableSize; ++i)
        Hash_destroyNode(ht->table[i]);
    free(ht);
}

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
        if (strcmp(targetList->key, key) == 0) {
            target = targetList;
            break;
        }
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
        newNode->next = ht->table[addr];
        ht->table[addr] = newNode;
        printf("Collision occured! >> Key(%s), Address(%d)\n", key, addr);
    }
}

int Hash_hash(KeyType key, int keyLen, int tableSize) {
    int hashValue = 0;
    for (int i = 0; i < keyLen; ++i)
        hashValue = (hashValue << 3) + key[i];
    hashValue = hashValue % tableSize;
    return hashValue;
}
