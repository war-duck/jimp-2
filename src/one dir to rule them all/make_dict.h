#ifndef MAKE_DICT_H
#define MAKE_DICT_H

#include "tree.h"

unsigned char*** make_dict(treeNode*, int);
void free_dict(unsigned char***, int);

#endif