#include "../lib/tree.h"

/**
 * This function creates the Tree
 * Then setting the key and value into the Stack
 * It's called by the function create_hm and call the create_stack function
 * @param key String attached with the value
 * @param value An integer value attached with the key
 * @return Returns the new node
 * Exit the program if it has been a problem with allocations
 * Exit status 3 for the head allocation or status 4 for the stack allocation
 */
Tree * create_node (char *key, int value)
{
    Tree *new = NULL;                                   //Initialisation of the tree head
    new = malloc(sizeof(Tree));

    if(new == NULL){                                    //Verification of the allocation
        printf("Error with the allocation of the %s Node\n", key);
        exit(3);
    }
    new->hash = key_to_hash(key);
    new->right = NULL;
    new->left = NULL;
    new->value = create_stack(key, value);              //Creating the value with a Stack structure
    if(new->value == NULL){                             //Verificating that the creation of the stack has been done correctly
        printf("Error with the allocation of the %s stack\n", key);
        exit(4);
    }

    return new;
}

/**
 * Insert tree is the function that creates and puts the nodes in the tree
 * It sorts the nodes by their hash code and makes the tree a BRT
 * @param head Pointer on the head of the tree
 * @param hash int value created with the hash_to_key(key) function
 * @param key String with a name inside
 * @param value An integer value associated with the key
 * @return the head of the tree or the new node if the tree was empty
 */
Tree * insert_tree (Tree *head, int hash, char *key, int value)
{
    if(head == NULL){                   //if the hash code is not in the tree, it adds it at its right place in order to keep the tree a BRT
        Tree *new = create_node(key, value);
        //printf("\t%s has been inserted with the key %d\n", key, hash);
        return new;
    }
    if(hash == head->hash){             //if the hash code is already in the tree, it appeals the push function to add the node to the stack
        push(key, value, &(head->value));
        return head;
    }
    if(hash < head->hash){              // It is used for navigating into the tree
        head->left = insert_tree(head->left, hash, key, value);
        return head;
    }
    else {
        head->right = insert_tree(head->right, hash, key, value);
        return head;
    }
}

/**
 * The function used for the modification of the value in the tree
 * @param head Pointer on the head of the Tree
 * @param hash Integer that is used for searching the stack with the key/value pair
 * @param key String with a name inside
 * @param new_value the new integer value we want to associate with the key
 * @param modifications an integer that is either 0 for : No modifications had been done. Or 1 for : The modification had been done successfully
 */
void modify_in_tree (Tree **head, int hash, char *key, int new_value, int *modifications)
{
    if(*head == NULL){                                                            //if the hash code is not in the tree, it adds it at its right place in order to keep the tree a BRT
        return;
    }
    if((*head)->hash == key_to_hash(key)){                                        //if the hash code is already in the tree, it appeals the push function to modify the node into the stack
        *modifications = find_in_list((*head)->value, key, new_value); //if the modification had been done correctly, the pointer modification will be 1
        return;
    }
    if(hash < (*head)->hash){                                                    // It is used for navigating into the tree
        modify_in_tree(&((*head)->left), hash, key, new_value, modifications);
        return;
    }
    else {
        modify_in_tree(&((*head)->right), hash, key, new_value, modifications);
        return;
    }
}

/**
 *
 * @param head
 * @param hash
 * @param key
 * @param modifications
 */
int get_key (Tree *head, int hash, char *key, int *modifications)
{
    if(head == NULL){                                  //if the hash code is not in the tree, it adds it at its right place in order to keep the tree a BRT
        return 0;
    }
    if(head->hash == hash ){              //if the hash code is already in the tree, it appeals the get_in_stack function to get the value associated with the key into the stack
         return get_in_stack(head->value, key);
    }
    else if(hash < head->hash){                           // It is used for navigating into the tree
        return get_key(head->left, hash, key, modifications);
    }
    else {
        return get_key(head->right, hash, key, modifications);;
    }
    return *modifications;
}

/**
 *
 * @param head Pointer on the head of the Tree
 * @param pnode double pointer on the value of the stack of the initial head in order to modify this value
 * @param hash Pointer on the hash_key of the initial head in order to modify this value
 * @return Returns the head that had been modified wit the value of the node with the maximal hash_key of its left side
 */
Tree * supp_max(Tree  *head, Stack **pnode, int *hash)
{
    Tree* tmp;
    if(head->right != NULL){
        head->right = supp_max(head->right, pnode, hash);   //Advance into the maximal hash key
    }
    else{
        *pnode = head->value;                                    //Modifying the value of the pointer on the stack, so it modifies the original head
        *hash = head ->hash;                                     //Modifying the value of the pointer on the hash key,  so it modifies the original head
        tmp = head;
        head = head->left;
        tmp->right = tmp->left = NULL;
        free(tmp);                                           //Freeing the value of the tmp
    }
    return head;                                                 //Returning the new head recursively
}

/**
 * This function deletes the key/value selected.
 * When the good hash key has been found, it will erase the key into the stack and then if the stack is empty, erase the node in the tree also.
 * @param head Pointer on the head of the tree
 * @param key String that contain a name
 * @param hash integer hash key associated with the key
 * @return the head of the tree ( recursively )
 */
Tree * delete_node (Tree *head, char* key, int hash)
{
    int is_empty = 0;
    Tree *temp;
    if (head == NULL) return head;
    if (hash < head->hash) {
        head->left = delete_node(head->left, key, hash);
    }
    else if (hash > head->hash) {
        head->right = delete_node(head->right,key,  hash);              //Dichotomic reserach of the value
    }
    else if (del_into_stack(&head->value, key, &is_empty) == 1){        //case 1: stack found but not empty
        if(is_empty == 1) {
            if (head->left == NULL) {                                        //case 2: one child (right) or zero children
                //printf("there is one child");
                temp = head;                                                 // save current node as a backup
                head = head->right;
                temp->left = temp->right = NULL;
                free(temp);

            }
            else if (head->right == NULL) {                                  // case 3: one child (left)
                //printf("there is one child");
                Tree *temp = head;                                           // save current node as a backup
                head = head->left;
                temp->left = temp->right = NULL;
                free(temp);
            }                                                                // case 4: two children
            else {
                //printf("there is two children");
                head->left = supp_max(head->left, &(head->value), &(head->hash));   //Replacing the value of head
            }
        }
    }
    return head;                                                             // parent node can update reference
}

/**
 * This function delete the entire tree in order to clear the hashmap
 * @param head Pointer on the tree
 */
void del_tree(Tree *head)
{
    if(head == NULL) return;
    del_tree((head->left));
    del_tree((head->right));
    clear_stack(head->value);   //First delete the entire stack before the free of the node
    head->left = head->right = NULL;
    free(head);                   //Then freeing the node
}

/**
 * Used For printing the Tree with recursive technique
 * Use the print_stack function for printing the all stack.
 * Print a "\n" before the first node and then appealing the print_hm() with start = 1
 * @param head pointer on the head of the tree
 * @param start integer which is initialized at 0
 */
void print_hm(Tree *head, int start)
{
    if(head == NULL) {
        printf("\n");
        return;
    }
    if(start == 0) printf("\n");

    print_hm(head->left, 1);
    printf("| %d : ", head->hash);
    print_stack(head->value);
    print_hm(head->right, 1);
}