//
// Created by Andrei Fedorov on 22.08.2022.
//
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct tree {
    int key;
    struct tree *left, *right;
    struct tree *parent; //ссылка на родителя
} tree;


void btUpView(tree *root){
    if (NULL == root) return;
    tree *left = root;
    while (left->left != NULL) {
        tree *new = malloc(sizeof(tree));
        new->key = left->left->key;
        new->left = left->left->left;
        new->right = left;
        left = new;
    }
    while (left != NULL) {
        printf("%d ", left->key);
        left = left->right;
    }
    return;
}


int main() {
    return 0;
};