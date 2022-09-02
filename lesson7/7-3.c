//
// Created by Andrei Fedorov on 22.08.2022.
//
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef struct tree {
    int key;
    struct tree *left, *right;
    struct tree *parent; //ссылка на родителя
} tree;


tree * findBrother(tree *root, int key){
    tree *element1 = root->left;
    tree *element2 = root->right;
    for (int i=0; i<2;i++){
        if (NULL != element1){
            if ((element1->key == key) && (NULL != element2)) return element2;
            element1 = findBrother(element1, key);
            if (NULL != element1) return element1;
        }
        element1 = root->right;
        element2 = root->left;
    }
    return NULL;
}


int main() {
    return 0;
};