//
// Created by Andrei Fedorov on 26.08.2022.
//
/*
 Описана структура данных
typedef struct list {
    void *address;
    size_t size;
    char comment[64];
    struct list *next;
} list;
Требуется реализовать только одну функцию, которая в данном списке находит адрес блока памяти занимающий больше всего места. Адрес хранится в поле address, поле size - соответствующий размер данного блока. Если список пустой, то функция должна возвращать NULL. Если есть несколько таких блоков, то вернуть адрес любого из них. Прототип функции:
void * findMaxBlock(list *head)
 */

#include <stddef.h>

typedef struct list {
    void *address;
    size_t size;
    char comment[64];
    struct list *next;
} list;


void * findMaxBlock(list *head) {
    list *result;
       result = head;

    while (head){
        if ((head->size) > (result->size)) {
            result = head;
        }
        head = head -> next;
    }
    return (result) ? result->address : NULL;
}

int main (){
    list *p1, *p2;


    return 0;
}