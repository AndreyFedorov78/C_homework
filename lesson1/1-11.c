//
// Created by Andrei Fedorov on 22.08.2022.
//
/*
Необходимо реализовать только одну функцию, которой на входе передаётся вещественное число в типе float, она возвращает порядок который хранится в поле EXP в виде десятичного целого числа.
Функция должна строго соответствовать прототипу int extractExp(float)
 */
#include <stdio.h>
#include <stdint.h>

int extractExp(float value) {
    union {
        float value;
        struct {
            uint32_t man : 23;
            uint32_t exp : 8;
            uint32_t s : 1;
        } components; } fc;
    fc.value = value;
    return fc.components.exp;
}


int main() {
    printf("%d %d %d %d\n", extractExp(1.0), extractExp(2.0),extractExp(3.99999), extractExp(0.001));
    return 0;
};

