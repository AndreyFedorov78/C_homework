//
// Created by Andrei Fedorov on 22.08.2022.
//
// На стандартном потоке ввода задаётся натуральное число N (N > 0), после которого следует последовательность из N целых чисел.
// На стандартный поток вывода напечатайте, сколько раз в этой последовательности встречается максимум.

#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t n; // количество числе
    int value, max; // текущее и максимальное значение
    uint16_t count = 0; // количество максимальных чисел
€
    scanf("%hd", &n);
    for (uint16_t i = 0; i < n; i++) {
        scanf("%d", &value);
        if (0 == i) max = value;
        if (max == value) count++;
        if (max < value){
            max = value;
            count = 1;
        }
    }
    printf("%d\n", count);
    return 0;
};