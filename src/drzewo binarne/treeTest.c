#include "tree.h"
#include "stdio.h"

int main(){
    treeNode *a = addNode('a', 15);
    treeNode *b = addNode('b', 22);
    treeNode *c = joinNodes(a, b);

    printf("%d %d\n", c->c, c->count);
    printf("%c %d\n", a->c, a->count);
    printf("%c %d\n", b->c, b->count);
}