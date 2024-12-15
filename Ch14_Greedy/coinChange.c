#include <stdio.h>
#include <stdlib.h>

int countCoins(int amount, int coinUnit) {
    int coinCount = 0, currentAmount = amount;

    while (currentAmount >= coinUnit) {
        coinCount++;
        currentAmount = currentAmount - coinUnit;
    }
    return coinCount;
}

void getChange(int price, int pay, int coinUnits[], int change[], int size) {
    int changeAmount = pay - price;

    for (int i = 0; i < size; ++i) {
        change[i]    = countCoins(changeAmount, coinUnits[i]);
        changeAmount = changeAmount - (coinUnits[i] * change[i]);
    }
}

void printChange(int CoinUnits[], int Change[], int size) {
    for (int i = 0; i < size; ++i)
        printf("%8d￦ : %d[EA]\n", CoinUnits[i], Change[i]);        
}

int myCompare(const void* a, const void* b) {
    return (*(int*)a) < (*(int*)b);
} 

int main( void ) {
    int  unitCount = 0, price = 0, pay = 0;
    int* coinUnits = (int*)malloc(sizeof(int) * unitCount);
    int* change    = (int*)malloc(sizeof(int) * unitCount);

    printf("Input how many units of coins >> "); 
    scanf("%d", &unitCount);

    printf("Input what is each units of coins\n");
    for (int i = 0; i < unitCount; i++ ) { 
        printf("(%d times left) >> ", unitCount - i);
        scanf("%d", &coinUnits[i]);
    }

    qsort( coinUnits, unitCount, sizeof(int), myCompare);

    printf("Input cost of merchandise you want >> ");
    scanf("%d", &price);

    printf("Input how much money customer give >> ");
    scanf("%d", &pay);

    getChange( price, pay, coinUnits, change, unitCount );
    
    printChange( coinUnits, change, unitCount);

    return 0;
}
