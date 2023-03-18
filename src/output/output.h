#ifndef OUTPUT_H
#define OUTPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_str_in_bin(char* str, int len, int add_char);
int output_to_file(FILE* out, char* content, long length);
void str_to_bin(char* content, int len, char* dest);
char* convert_dic_to_bin(char** dic[2], int num);
int test();


#endif