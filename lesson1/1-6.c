//
// Created by Andrei Fedorov on 22.08.2022.
//
// На вход программе подается беззнаковое 32-битное целое число N. Требуется найти количество единичных битов в двоичном представлении данного числа.


#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t n , count=0;
    scanf("%d", &n);
    for (uint8_t i=0; i<32; i++)
        count += (n & (1 << i)) ? 1 : 0;
    printf("%u\n", count);
    return 0;
};