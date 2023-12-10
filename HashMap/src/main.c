#include "../lib/hashmap.h"

int main ()
{
    int choice; 
    HM *root = NULL;
    printf("Welcome into my Program, you have two possibilities, \n\t1 : You can fill he hashmap by yourself and manipulate your hashmap. \n\t2 : You can load an already filled hashmap and just explore the code.\nWhat is your choice : \n");
    scanf("%d",&choice);
    while(choice < 1 || choice > 2){
        printf("Error, you must enter a value between 1 and 2\n");
        scanf("%d",&choice);
    }
    if(choice == 1) user_hashmap();
    else{
        root = fill_hm(root);
        print_hm(root->head, 0);
        del_all(root);
    }
    return 0;
}
