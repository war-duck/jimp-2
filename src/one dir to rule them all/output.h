#ifndef OUTPUT_H
#define OUTPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_str_in_bin(unsigned char* str, int len, int add_char);
void str_to_bin(unsigned char* content, int len, unsigned char* dest);
unsigned char* dic_to_bin(unsigned char** dic[2], int num, int* len);
// void test();


#endif