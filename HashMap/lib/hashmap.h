#include "tree.h"

typedef struct HM{
    struct Tree *head;
    int count;
}HM;

HM * create_hm (char *key, int value);

int hm_add_node (HM *root, char key[100], int value);

int hm_update_node (HM *root, char* key, int new_value);

void del_all(HM *root);

HM * hm_delete_node(HM *root, char *name);

int size_hm(HM *root);

HM * fill_hm (HM *root);

void user_hashmap();


