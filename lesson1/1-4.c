//
// Created by Andrei Fedorov on 22.08.2022.
//
// На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). Требуется взять K младших битов числа N и вывести полученное таким образом число.

#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t n , k, mask=0xFFFFFFFF;
    scanf("%d %d", &n, &k);
    mask <<=k;
    mask =~mask;
    n = (n & mask);
    printf("%u\n", n);
    return 0;
};