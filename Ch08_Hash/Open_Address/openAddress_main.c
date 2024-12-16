#include "openAddress.h"

int main( void )
{
    HashTable* hashTable = Hash_createTable(11);

    Hash_set(&hashTable, "MSFT",   "Microsoft Corporation");
    Hash_set(&hashTable, "JAVA",   "Sun Microsystems");
    Hash_set(&hashTable, "REDH",   "Red Hat Linux");
    Hash_set(&hashTable, "APAC",   "Apache Org");
    Hash_set(&hashTable, "ZYMZZ",  "Unisys Ops Check"); //  APAC와 충돌 
    Hash_set(&hashTable, "IBM",    "IBM Ltd.");
    Hash_set(&hashTable, "ORCL",   "Oracle Corporation");
    Hash_set(&hashTable, "CSCO",   "Cisco Systems, Inc.");
    Hash_set(&hashTable, "GOOG",   "Google Inc.");
    Hash_set(&hashTable, "YHOO",   "Yahoo! Inc.");
    Hash_set(&hashTable, "NOVL",   "Novell, Inc.");

    printf("\n");
    printf("Key: %s, Value: %s\n", "MSFT",  Hash_get(hashTable, "MSFT" ) );
    printf("Key: %s, Value: %s\n", "REDH",  Hash_get(hashTable, "REDH" ) );
    printf("Key: %s, Value: %s\n", "APAC",  Hash_get(hashTable, "APAC" ) );
    printf("Key: %s, Value: %s\n", "ZYMZZ", Hash_get(hashTable, "ZYMZZ" ) );
    printf("Key: %s, Value: %s\n", "JAVA",  Hash_get(hashTable, "JAVA" ) );
    printf("Key: %s, Value: %s\n", "IBM",   Hash_get(hashTable, "IBM" ) );
    printf("Key: %s, Value: %s\n", "ORCL",  Hash_get(hashTable, "ORCL" ) );
    printf("Key: %s, Value: %s\n", "CSCO",  Hash_get(hashTable, "CSCO" ) );
    printf("Key: %s, Value: %s\n", "GOOG",  Hash_get(hashTable, "GOOG" ) );
    printf("Key: %s, Value: %s\n", "YHOO",  Hash_get(hashTable, "YHOO" ) );
    printf("Key: %s, Value: %s\n", "NOVL",  Hash_get(hashTable, "NOVL" ) );

    Hash_destroyTable(hashTable);

    return 0;
}
