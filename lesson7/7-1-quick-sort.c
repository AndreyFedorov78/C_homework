#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char word[20];
    struct list *next;
} myList;

int compare(const void *x1, const void *x2) {
    /* От строки ниже реально пахнет потом! :))) */
    return (strcmp(((myList *) *(myList **) x1)->word, ((myList *) *(myList **) x2)->word));
}

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

void sortList(myList *arr[], int size) {
    qsort(arr, size, sizeof(myList *), compare);
    return;
}

int main() {
    myList *list = createItem(NULL);
    char ch = getchar();
    int p = 0, number = 1;
    while (ch != '.') {
        if (' ' == ch) {
            list->word[p] = 0;
            list = createItem(list);
            p = 0;
            number++;
        } else {
            list->word[p++] = ch;
        }
        ch = getchar();
    }
    myList *arr[number];
    int i;
    myList *tmp = list;
    for (i = number - 1; i >= 0; i--) {
        arr[i] = tmp;
        if (tmp->next) tmp = tmp->next;
    }
    sortList(arr, number);
    for (i = 0; i < number; i++) {
        printf("%s ", arr[i]->word);
    }
    printf("\n");
    clearList(list);
    return 0;
};