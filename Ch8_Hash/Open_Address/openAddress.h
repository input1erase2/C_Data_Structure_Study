#ifndef __OPEN_ADDRESSING_H_
#define __OPEN_ADDRESSING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* KeyType;
typedef char* ValueType;

typedef struct _Node {
    KeyType key;
    ValueType value;
    enum NodeStatus {
        EMPTY = 0,
        OCCUPIED = 1
    } status;
} Node;

typedef struct _HashTable {
    int occupiedCount;
    int tableSize;
    Node* table;
} HashTable;


HashTable*  Hash_createTable(int size);
void        Hash_destroyTable(HashTable* ht);
void        Hash_clearNode(Node* node);
void        Hash_set(HashTable** ht, KeyType key, ValueType value);
ValueType   Hash_get(HashTable* ht, KeyType key);
int         Hash_hash1(KeyType key, int keyLen, int size);
int         Hash_hash2(KeyType key, int keyLen, int size);
void        Hash_rehash(HashTable** ht);


#endif