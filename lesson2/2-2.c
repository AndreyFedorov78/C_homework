//
// Created by Andrei Fedorov on 26.08.2022.
//


#include <stddef.h>

typedef struct list {
    void *address;
    size_t size;
    char comment[64];
    struct list *next;
} list;


size_t totalMemoryUsage(list *head) {
    size_t result = 0;
    while (head){
        result +=head -> size;
        head = head -> next;
    }
    return result;
}

int main (){
    list *p1, *p2;


    return 0;
}