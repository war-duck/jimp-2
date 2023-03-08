#include "tree.h"
#include "stdio.h"

int main(){
    treeNode *root = addNode('a');
    printf("%c\n", root->c);
    return 0;
}