#ifndef __CHAINING_H_
#define __CHAINING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* KeyType;
typedef char* ValueType;

typedef struct _Node {
    KeyType key;
    ValueType value;
    struct _Node* next;
} Node;

typedef Node* List;

typedef struct _Table {
    int tableSize;
    List* table;    // Node** table;
} HashTable;

HashTable*  Hash_createTable(int size);
void        Hash_destroyTable(HashTable* ht);
void        Hash_destroyList(List* l);
void        Hash_destroyNode(Node* node);
Node*       Hash_createNode(KeyType key, ValueType value);
ValueType   Hash_get(HashTable* ht, KeyType key);
void        Hash_set(HashTable* ht, KeyType key, ValueType newValue);
int         Hash_hash(KeyType key, int keyLen, int tableSize);

#endif