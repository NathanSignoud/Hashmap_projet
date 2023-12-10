#ifndef _STACK_H
#define _STACK_H


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>



typedef struct Stack{
    char *key;
    int value;
    struct Stack *next;
}Stack;



Stack * create_stack (char *key, int value);

void push (char* key, int value, Stack** head);

int del_into_stack(Stack **head, char* key, int *is_empty);

void clear_stack(Stack *head);

void print_stack(Stack *head);

char * static_to_dynamic(char s_str[100]);

int key_to_hash(char *key);

int  find_in_list (Stack *head, char *key, int new_value);

int is_in_tree (Stack *head, char *key);

int get_in_stack(Stack *head, char *key);


#endif
