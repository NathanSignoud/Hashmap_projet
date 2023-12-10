#ifndef _TREE_H
#define _TREE_H

#include "stack.h"

typedef struct Tree{
    int hash;
    struct Stack *value;
    struct Tree *left, *right;
}Tree;

Tree * create_node (char *key, int value);

Tree * insert_tree (Tree *head, int hash, char *key, int value);

void modify_in_tree (Tree **head, int hash, char *key, int new_value, int *modifications);

int get_key (Tree *head, int hash, char *key, int *modifications);

Tree * supp_max(Tree  *head, Stack **pnode, int *hash);

Tree * delete_node (Tree *head, char* key, int hash);

void del_tree(Tree *head);

void print_hm(Tree *head, int start);

#endif