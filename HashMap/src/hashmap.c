#include "../lib/hashmap.h"

/**
 * This function creates the HashMap
 * Then setting the key and value into the Tree and then Stack
 * Returns the root and exit the program if it has been a problem with allocations
 * Exit status 1 for the root allocation or status 2 for head allocation
 * @param key A string with a name into
 * @param value The value associated with the key
 * @return Returns the root of the Hashmap
 */
HM * create_hm (char *key, int value)
{
    HM *root = NULL;                                    //Initialisation of the HM Root
    root = malloc(sizeof(HM));
    if(root == NULL) {                                  //Verification of the allocation
        printf("Error with the allocation of the HashMap\n");
        exit(1);
    }
    root->count = 1;
    root->head = create_node(static_to_dynamic(key), value);               //Creating the head with a Tree structure
    if(root->head == NULL){                             //Verificating that the creation of the node has been done correctly
        printf("Allocation of head is incorrect\n");
        exit(2);
    }

    return root;
}

/**
 *This function is used for the addition of a new pair into the selected Hashmap. It will call the "insert_tree() to fill the node into the binary research tree" function.
 * @param root Pointer on the HashMap
 * @param key A string with a name into
 * @param value The value associated with the key
 * @return 1 : If everything has been done correctly, 0 on the other case.
 */
int hm_add_node (HM *root, char key[100], int value)
{
    Tree *result;
    result = insert_tree(root->head, key_to_hash(key), static_to_dynamic(key), value);
    if(result == NULL){
        printf("Error with the adding of %s\n", key);
        return 0;
    }
    root->count++;
    return 1;
}

/**
 * This Function modifies  the value associated with the key
 * @param root Pointer on HashMap
 * @param key A string with a name into
 * @param new_value The new value we want to associate with the key
 * @return 1 : If the value has been modified, 0 : If the has not been found
 */
int hm_update_node (HM *root, char* key, int new_value)
{
    int check = 0;

    modify_in_tree(&(root->head), key_to_hash(key), key, new_value, &check);
    return check;
}

/**
 * This function is used at the end of the program to clear the memory and delete the entire Hashmap
 * @param root Pointer on the Hashmap
 */
void del_all(HM *root)
{
    del_tree(root->head);
    root->head = NULL;
    free(root);
    return;
}

/**
 * This function deletes the key-value pair in the hashmap
 * @param root Pointer on the Hashmap
 * @param name The key that we want to delete
 * @return the root of the hashmap
 */
HM * hm_delete_node(HM *root, char *name)
{
    root->head = delete_node(root->head, name, key_to_hash(name));
    root->count--;
    return root;
}

/**
 * @param root Pointer on the Hashmap
 * @return Returns the size of the hashmap
 */
int size_hm(HM *root)
{
    return root->count;
}

/**
 * This function is an example of functions and manipulations on the Hashmap
 * Print a first time the Hashmap after adding all the values.
 * @param root Pointer on Hashmap
 * @return Returns the filled Hashmap
 */
HM * fill_hm (HM *root)
{
    int i=1, size;
    char name[20];

    root = create_hm("papa", 0);
    i += hm_add_node (root, "maman", 10);
    i += hm_add_node (root, "lena", 50);
    i += hm_add_node (root, "mika", 65);
    i += hm_add_node (root, "olaf", 98);
    i += hm_add_node (root, "qlaf", 99);
    i += hm_add_node (root, "Francois", 2);
    i += hm_add_node (root, "Nathan", 1000);
    i += hm_add_node (root, "Efe", -1);
    i += hm_add_node (root, "Tessa", -1);
    i += hm_add_node (root, "Romu", 47);
    hm_update_node (root, "Romu", 911);
    i += hm_add_node (root, "nena", 4785);
    hm_update_node(root, "papa", 41);
    print_hm(root->head, 0);
    printf("\n\nWhich value would you want to delete ? \n");
    scanf("%s", name);
    root = hm_delete_node(root, name);
    return root;
}

void user_hashmap()
{
    HM *root = NULL;
    char key[20];
    int value, choice;
    printf("Whats the name of the first pair\n");
    scanf("%s", key);
    printf("\nAnd what is its associated value ?\n");
    scanf("%d", &value);
    root = create_hm(key, value);
    do{
        do{
            printf("\nWhat do you want to do now ? \n\t 1 : Add a new value\n\t 2 : Modify a value associated with a key\n\t 3 : Delete a pair\n\t 4 : Get the size of the HashMap\n\t 5 : Get the value of a selected key.\n\t 0 : To stop the program\n");
            scanf("%d", &choice);
            switch(choice){
                case 1:
                    printf("Whats the name of the pair\n");
                    scanf("%s", key);
                    printf("\nAnd what is its associated value ?\n");
                    scanf("%d", &value);
                    if(hm_add_node (root, key, value) != 1){
                        printf("Error during the addition\n");
                        exit(74);
                    }
                    break;
                case 2:
                    printf("Which key would you want to modify ?\n");
                    scanf("%s", key);
                    printf("\nAnd with what value ?\n");
                    scanf("%d", &value);
                    if(hm_update_node(root, key, value) == 0) printf("The value cannot be changed, you might try another key\n");
                    break;
                case 3:
                    printf("\n\nWhich pair would you want to delete ? \n");
                    scanf("%s", key);
                    root = hm_delete_node(root, key);
                    break;
                case 4:
                    printf("The HashMap have %d nodes\n", size_hm(root));
                    break;
                case 5:
                    printf("\nWhat key would you want to get the value ? \n");
                    scanf("%s", key);
                    printf("The value of this %s is %d\n", key, get_key(root->head, key_to_hash(key), key, 0));
                    break;
            }
            print_hm(root->head, 0);
        }while(choice >=5 || choice < 0);
    }while(choice != 0);
    del_all(root);
}