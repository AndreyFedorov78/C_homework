//
// Created by Andrei Fedorov on 22.08.2022.
//
#include <stdio.h>
#include <stdint.h>


uint32_t bitCount(uint32_t n, uint32_t k){
    uint32_t count=0;
    for (uint32_t i = 0; i <= n; i++) {
        uint8_t flag = 0;
        uint32_t count_0 = 0;
        for (int8_t j = 31; j>=0; j--) {
            flag = flag || ((1<<j) & i) ;  // если флаг не установлен ищем старшую единицу
            count_0 += (((1<<j) & i) == 0) && flag ;
        }
        if (count_0 == k) count++;
                // if (count_0 == k) printf("%u - ", count);;
    }
    //if ((0 == n) && (k==0)) count=1;
    if ((0 == n) && (k==1)) count=1;
    return count;
}

int main() {
    uint32_t n, k, count=0;
    scanf("%u %u", &n, &k);
   count = bitCount(n,k);
    printf("%u\n", count);

/*
    for (uint32_t i=0; i<16; i++){
        count = bitCount(1<<i,0);
        printf("\n%u %u\n",1<<i, count);
    }*/



    return 0;
};