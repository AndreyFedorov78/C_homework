//
// Created by Andrei Fedorov on 22.08.2022.
//
/*
 * В программе реализована структура данных:
struct pack_array {
    uint32_t array; // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8; // счетчик нулей в array
    uint32_t count1 : 8; // счетчик единиц в array
}
Необходимо реализовать только одну функцию (всю программу писать не надо!!!), которая упаковывает переданный ей массив из 32-ух элементов 0 и 1 в указанную структуру данных.
Функция должна строго соответствовать прототипу: void array2struct(int [], struct pack_array *)
 */
#include <stdio.h>
#include <stdint.h>



struct pack_array {
    uint32_t array; // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8; // счетчик нулей в array
    uint32_t count1 : 8; // счетчик единиц в array
};


void array2struct(int arr[], struct pack_array *arrPacked) {
    arrPacked->array=0;
    arrPacked->count0=0;
    arrPacked->count1=0;
    for (uint8_t i = 0; i<32; i++){
        arrPacked->array <<= 1;
        if (arr[i]) {
            arrPacked->array++;
            arrPacked->count1++;
        } else arrPacked->count0++;
    }
    return;
}


int main() {
    int arr[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    struct pack_array pArr;
    array2struct(arr,&pArr);
    printf("%x\n %d, %d \n", pArr.array, pArr.count1, pArr.count0);
    return 0;
};

