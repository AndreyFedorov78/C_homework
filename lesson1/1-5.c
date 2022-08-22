//
// Created by Andrei Fedorov on 22.08.2022.
//
// На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). Требуется взять K подряд идущих битов числа N так, чтобы полученное число было максимальным. Программа должна вывести полученное число.

#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t n , k, max=0, mask=0xFFFFFFFF;
    scanf("%d %d", &n, &k);
    mask <<=k;
    mask =~mask;
    for (uint8_t i=0; i<33-k; i++) {
        if (max < (n & mask)) max = (n & mask);
        n>>=1;
    }
    printf("%u\n", max);
    return 0;
};