//
// Created by Andrei Fedorov on 22.08.2022.
//
//В стартер боксе Geek Brains есть электронные чашечные весы (вместимость каждой чашки 1 тонна) и гири массами 1г, 3г, 9г, 27г, и т.д. по одной штуке каждой массы. Менеджер из рекламного отдела взял такие весы и не знает, можно ли взвесить что-нибудь тяжелое и если можно, сколько гирь придется положить на весы (на любую чашку). Надо помочь ему.
//Формат входных данных: единственное натуральное число – масса взвешиваемого товара в граммах (не больше 1000000000).
//Формат выходных данных: единственное целое число – общее количество гирь или число –1 если данный товар взвесить невозможно.
#include <stdio.h>
#include <stdint.h>
#define LIMIT 1000000
uint8_t error = 0;

unsigned int new_weight(unsigned int value) {
    unsigned int n=1;
    while (n<=LIMIT){
        if (value == n) return 0;
        if ((value >= (n -1)/2) && (value < n)) return n-value;
        if ((value <= (n*3 -1)/2) && (value > n)  ) return  value - n;
        n*=3;
    }
    error = 1;
    return 0;
}


int main() {
    unsigned int n;
        int count = 0;
        scanf("%u", &n);
        while (n != 0) {
            n = new_weight(n);

            if (error) {
                count = -1;
                break;
            } else count++;
        }
        printf("%d\n", count);
    return 0;
};