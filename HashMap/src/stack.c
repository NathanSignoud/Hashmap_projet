#include "../lib/stack.h"

/**
 * This function creates the Stack
 * Then setting the key and value into the Stack
 * It's called by the create_tree function
 * Returns the stack and exit the program if it has been a problem with allocations
 * Exit status 5 for the stack allocation
 * @param key String that contains a name
 * @param value Integer associated with the key
 * @return returns the new node
 */
Stack * create_stack (char *key, int value)
{
    Stack *new = NULL;                                  //Initialisation of the tree head
    new = malloc(sizeof(Stack));

    if(new == NULL){                                    //Verification of the allocation
        printf("Error with the allocation of the Stack\n");
        free(new);
        exit(5);
    }
    new->key = key;
    new->value = value;
    new->next = NULL;

    return new;
}

/**
 * It is used when two keys have the same hash code and storing them at the same place in the tree
 * @param key String that contains a name
 * @param value Integer value associated with the key
 * @param head Double pointer on the head of the stack to be able to modify its value without return
 * Push is the function for adding new things in the selected stack
 */
void push (char* key, int value, Stack** head)
{
    Stack *new = create_stack(key, value);
    if(is_in_tree(*head, key) == 1) printf("%s has not been added because the key is already in this stack\n", key);
    new->next = *head;
    *head = new;
}

/**
 * This function deletes the potential node of key if it is in the stack and also indicates if the has to be deleted too
 * @param head Pointer on the head of the stack
 * @param key String
 * @param is_empty Pointer on an integer that is initialised at 0 and updated at 1 if the stack is going to be empty after the suppression of the node
 * @return return 1 if a value has been deleted and 0 if not
 */
int del_into_stack(Stack **head, char* key, int *is_empty)
{
    Stack *tmp;
    if(*head == NULL) return 0;
    if((*head)->next == NULL && is_in_tree(*head, key) == 1) *is_empty = 1;
    if (strcmp((*head)->key, key) == 0) {
        tmp = *head;
        *head = tmp->next;
        tmp->next == NULL;
        free(tmp->key);
        free(tmp);
        return 1;
    }
    while((*head)->next != NULL) {
        if (strcmp((*head)->next->key, key) == 0) {
            tmp = (*head)->next;
            (*head)->next = tmp->next;
            free(tmp->key);
            free(tmp);
            return 1;
        }
        *head = (*head)->next;
    }
    return 0;
}

/**
 * Used for deleting the entire stack
 * @param head Pointer on the head of the stack
 */
void clear_stack(Stack *head)
{
    Stack *tmp;
    while(head != NULL){
        tmp = head;
        head = head->next;
        tmp->next = NULL;
        if(tmp->key != NULL) free(tmp->key);
        tmp->key = NULL;
        free(tmp);
    }
}

/**
 * Used For printing a stack
 * @param head Pointer on the head of the stack
 */
void print_stack(Stack *head)
{
    if(head == NULL){
        printf("ERROR");
    }
    while(head != NULL){
        printf("%s -> %d  ", head->key, head->value);
        head = head->next;
    }
}

/**
 * This function is used for converting a static string into a dynamic string
 * it then returns the dynamic str or exit with the status 6 if the allocation is NULL
 * @param s_str A "static" string
 * @return Returns a string that has been allocated correctly
 */
char * static_to_dynamic(char s_str[100])
{
    char *d_str = NULL;
    unsigned long len = strlen(s_str) + 1;
    d_str = malloc(sizeof(char)*len);

    if(d_str == NULL){
        printf("Error with the static to dynamic conversion of %s", s_str);
        exit(6);
    }
    strcpy(d_str, s_str);

    return d_str;
}

/**
 * Key_to_hash is the function that creates the hash code
 * It uses a technique which is multiplying each character value with its place in the str
 * @param key A string
 * @return Returns an integer that has been created with the key
 */
int key_to_hash(char *key)
{
    unsigned long n = strlen(key);
    int hash = 0;
    for(int i = 0; i < n; i++)
    {
        hash += key[i] * (i+1);             //Doing the transformation by multiplying each character by its place in the string
    }
    //printf("The hash key associated with %s is %d\n", key, hash);

    return hash;
}


/**
 * Checks if key is already in the stack by comparing the keys
 * @param head A pointer on the head of the stack
 * @param keys A string
 * @param new_value An integer with the value we want to replace with
 * @return If yes, modifies the value associated with the key by a new_value and returns 1, if no, returns 0
 *
 */
int  find_in_list (Stack *head, char *key, int new_value)
{
    while(head != NULL){
        if(strcmp(head->key,key) == 0){
            head->value = new_value;
            return 1;
        }
        head = head->next;
    }
    return 0;
}

/**
 * Checks if a key is into a stack
 * @param head A pointer on the head of the stack
 * @param key The key we want to check
 * @return 1 if the key is in the stack, 0 if not
 */
int is_in_tree (Stack *head, char *key)
{
    while(head != NULL){
        if(strcmp(head->key,key) == 0) return 1;
        head = head->next;
    }
    return 0;
}

/**
 * The same function as before, excepts that this time, its return the value of the key
 * @param head A pointer on the head of the stack
 * @param key The key associated with the value with want to get
 * @return the integer associated with the key or 0 if there is no node in this hashmap with this key
 */
int get_in_stack(Stack *head, char *key)
{
    while(head != NULL){
        if(strcmp(head->key,key) == 0) return head->value;
        head = head->next;
    }
    printf("%s is not in the tree\n", key);
    return 0;
}