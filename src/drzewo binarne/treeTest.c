#include "tree.h"
#include "stdio.h"

int main(){
    treeNode *root = addNode('a', 33);
    printf("%c\n", root->c);
    return 0;
}