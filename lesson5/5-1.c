#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct value {
    int value;
    struct value *p;
} MyList;

int add_value(MyList *list, int value) {
    if (list->value == value) {
        return 0;
    } else if (NULL == list->p) {
        list->p = malloc(sizeof(MyList));
        list->p->value = value;
        list->p->p = NULL;
        return 1;
    } else {
        return add_value(list->p, value);
    }
}

void clear_list(MyList *list) {
    if (list->p) clear_list((list->p));
    free(list);
    return;
}


int main() {
    char str[101]; // один символ добавим для '0' в конце строки
    char mem;
    MyList list;
    list.value = 0;
    list.p = NULL;
    scanf("%s", str);
    int count = 0;
    int size = strlen(str);
    for (int i = 0; i < size - 2; i++) {
        if (str[i] != '0') {
            for (int j = i + 1; j < size - 1; j++) {
                for (int k = j + 1; k < size; k++) {
                    count += add_value(&list, (str[i] - '0') * 100 + (str[j] - '0') * 10 + (str[k] - '0'));
                }
            }
        }
    }
    printf("%d\n", count);
    if (list.p) clear_list(list.p);
}

