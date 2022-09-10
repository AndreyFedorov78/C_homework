//
// Created by Andrei Fedorov on 22.08.2022.
//
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char word[20];
    struct list *next;
} myList;


myList *createItem(myList *p) {
    myList *new;
    new = malloc(sizeof(myList));
    new->next = p;
    return new;
}

void clearList(myList *p) {
    if (p->next) {
        clearList(p->next);
    }
    free(p);
    return;
}

void printList(myList *p) {
    while (p) {
        printf("%s ", p->word);
        p = p->next;
    }
}

myList * sortList(myList *p) {
    myList *curPos, *tmp;
    int change = 1;
    p = createItem(p);
    p->word[0]=0;
    while (change) {
        change = 0;
        curPos = p->next;
        tmp = p;
        while (curPos->next) {
            if (strcmp(curPos->word, curPos->next->word) > 0) {
                change = 1;
                tmp->next = curPos->next;
                tmp  = curPos->next;
                myList *tmp2 = curPos->next->next;
                curPos->next->next = curPos;
                curPos->next = tmp2;
            } else {
                tmp = curPos;
                curPos = curPos->next;
            }
        }
    }
    tmp = p;
    p= p->next;
    free(tmp);
    return (p);
}

int main() {
    myList *list = createItem(NULL);
    char ch = getchar();
    int p = 0;
    while (ch != '.') {
        if (' ' == ch) {
            list->word[p] = 0;
            list = createItem(list);
            p = 0;
        } else {
            list->word[p++] = ch;
        }
        ch = getchar();
    }

   // printList(list);
   // printf("\n");
    list = sortList(list);
    printList(list);
    printf("\n");
    clearList(list);
    return 0;
};