#include "chaining.h"


int main() {
    HashTable* ht = Hash_createTable(12289);
    
    Hash_set( ht, "MSFT",   "Microsoft Corporation");
    Hash_set( ht, "JAVA",   "Sun Microsystems");
    Hash_set( ht, "REDH",   "Red Hat Linux");
    Hash_set( ht, "APAC",   "Apache Org");
    Hash_set( ht, "ZYMZZ",  "Unisys Ops Check"); //  APAC와 충돌 
    Hash_set( ht, "IBM",    "IBM Ltd.");
    Hash_set( ht, "ORCL",   "Oracle Corporation");
    Hash_set( ht, "CSCO",   "Cisco Systems, Inc.");
    Hash_set( ht, "GOOG",   "Google Inc.");
    Hash_set( ht, "YHOO",   "Yahoo! Inc.");
    Hash_set( ht, "NOVL",   "Novell, Inc.");

    printf("\n");
    printf("[Key] %s --- [Value] %s\n", "MSFT",   Hash_get( ht, "MSFT" ) );
    printf("[Key] %s --- [Value] %s\n", "REDH",   Hash_get( ht, "REDH" ) );
    printf("[Key] %s --- [Value] %s\n", "APAC",   Hash_get( ht, "APAC" ) );
    printf("[Key] %s --- [Value] %s\n", "ZYMZZ",  Hash_get( ht, "ZYMZZ" ) );
    printf("[Key] %s --- [Value] %s\n", "JAVA",   Hash_get( ht, "JAVA" ) );
    printf("[Key] %s --- [Value] %s\n", "IBM",    Hash_get( ht, "IBM" ) );
    printf("[Key] %s --- [Value] %s\n", "ORCL",   Hash_get( ht, "ORCL" ) );
    printf("[Key] %s --- [Value] %s\n", "CSCO",   Hash_get( ht, "CSCO" ) );
    printf("[Key] %s --- [Value] %s\n", "GOOG",   Hash_get( ht, "GOOG" ) );
    printf("[Key] %s --- [Value] %s\n", "YHOO",   Hash_get( ht, "YHOO" ) );
    printf("[Key] %s --- [Value] %s\n", "NOVL",   Hash_get( ht, "NOVL" ) );

    Hash_destroyTable( ht );
    return 0;
}