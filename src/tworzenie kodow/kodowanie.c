#include "kodowanie.h"
#include <stdlib.h>

char** make_codes(treeNode *root, int code_num){
    char** dict[2];
    dict[0] = malloc(code_num * sizeof(dict[0]));
    dict[1] = malloc(code_num * sizeof(dict[1]));
    // TO-DO reszta
}