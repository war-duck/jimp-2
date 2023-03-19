#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "output.h"
void fill_char_code(code_struct* code_info, char **my_test[2], int dic_len)
{
    char* ch, * code;
    printf("wywołano\n");
    for (int i = 0; i < dic_len; ++i)
    {
        ch   = my_test[0][i];
        code = my_test[1][i];
        code_info->code_len[*ch] = strlen(code); // długość kodu
        code_info->char_code[*ch] = malloc((1+(code_info->code_len[*ch]-1)/8) * sizeof(char));
        str_to_bin(code, code_info->code_len[*ch], code_info->char_code[*ch]); // z modułu output - przetwarza string "(0|1)*" na kod binarny i wsadza kod do char_code
    }
    for (int i = 0; i < 256; ++i)
    {
        printf ("%c: len: %d, %s\n", i, code_info->code_len[i], code_info->char_code[i]);
        if (code_info->code_len[i]) print_str_in_bin(code_info->char_code[i], 1+code_info->code_len[i]/8, 1);
    }
}
int compress(char* uncomp , int len, data_struct* message, code_struct* code_info)
{
    short current_byte_pos = 0; // 0 - początek bajta >0<0111001
    char* pos = message->data;
    for (int i = 0; i < len; ++i)
    {
        
        if ((len - i) % 8 == 0 && i != 0)
        {
            ++pos;
            ++message->len;
        }
        *dest <<= 1; // przesuń poprzedni znak
        *dest |= ((content[i] == '1') ? 0b1 : 0b0); // wstaw znak
    }
}
int main()
{
    int len = 30;
    data_struct message = {.data = malloc(len * sizeof(char)), .len = 0, .byte_pos = 0};
    code_struct code_info = {.char_code = {0}, .code_len = {0}};
    int num = 6;
    char **my_test[2];
    my_test[0] = malloc(num * sizeof(char*));
    my_test[1] = malloc(num * sizeof(char*));
    my_test[0][0] = "a";
    my_test[0][1] = "b";
    my_test[0][2] = "c";
    my_test[0][3] = "d";
    my_test[0][4] = "e";
    my_test[0][5] = "f";
    my_test[1][0] = "101";
    my_test[1][1] = "101101000";
    my_test[1][2] = "1";
    my_test[1][3] = "100111001000110001";
    my_test[1][4] = "1011010010";
    my_test[1][5] = "1010101010101010101010101010101";
    fill_char_code(&code_info, my_test, num);
    return 0;
}