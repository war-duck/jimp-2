#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "output.h"
void print_str_in_bin(unsigned char* str, int len, int add_char) // len w bajtach, add_char - 1 - podpisuj poszczególne bajty odp. znakami, 0 - nie
{
    unsigned char c;
    for (int i = 0; i < len; ++i)
    {
        c = str[i];
        for (int j = 0; j < 8; ++j)
        {
            printf ("%c", ((c >> 7)+'0'));
            c <<= 1;
        }
        if (add_char) printf ("(%c) ", str[i]); else printf (" ");
    }
    printf ("\n");
}

void str_to_bin(unsigned char* content, int len, unsigned char* dest)
{
    for (int i = 0; i < (1 + (len-1) / 8); ++i) // zerujemy wszystkie potrzebne bajty
        dest[i] = '\0';
    *(dest + 1 + (len-1) / 8) = '\0'; // koniec kodu
    for (int i = 0; i < len; ++i)
    {
        if ((len - i) % 8 == 0 && i != 0)
            ++dest;
        *dest <<= 1; // przesuń poprzedni znak
        *dest |= ((content[i] == '1') ? 0b1 : 0b0); // wstaw znak
    }
}

unsigned char* dic_to_bin(unsigned char** dic[2], int num, int* len) // tablica[0-znak,1-kod][nr_znaku], ilość znaków
{
    int max_size, cur_size = 0;
    max_size = 4 * num;
    unsigned char* output = calloc(max_size, sizeof(char));
    unsigned char* pos = output, * code_pos, code[33];
    int code_len;
    for (int i = 0; i < num; ++i)
    {

        code_len = strlen(dic[1][i]);
        cur_size += 2 + (1 + (code_len-1) / 8); // 2B na znak i długość kodu + (długość kodu)
        if (cur_size > max_size)
        {
            output = realloc(output, max_size+=16);
            memset(output+max_size-16, 0, 16); // czyści doalokowaną pamięć
        }
        *pos++ = *dic[0][i];// znak
        *pos++ = code_len;  // długość kodu
        str_to_bin(dic[1][i], code_len, code);
        *pos = '\0'; // żeby strcat znalazło koniec outputa
        strcat(pos, code);
        pos += (1 + (code_len-1) / 8);
        //printf ("%s, len: %d\n", output, code_len);
    }
    // print_str_in_bin(output, cur_size, 1);
    *len = pos - output;
    return output;
}

// void test()
// {
//     int num = 6;
//     char **my_test[2];
//     my_test[0] = malloc(num * sizeof(char*));
//     my_test[1] = malloc(num * sizeof(char*));
//     my_test[0][0] = "a";
//     my_test[0][1] = "b";
//     my_test[0][2] = "c";
//     my_test[0][3] = "d";
//     my_test[0][4] = "e";
//     my_test[0][5] = "f";
//     my_test[1][0] = "101";
//     my_test[1][1] = "101101000";
//     my_test[1][2] = "1";
//     my_test[1][3] = "100111001000110001";
//     my_test[1][4] = "1011010010";
//     my_test[1][5] = "1010101010101010101010101010101";
//     char* result = dic_to_bin(my_test, num);
//     printf ("\n\n%s", result);
//     FILE *out = fopen("test", "wb");
//     if (out == NULL)
//         return;
//     output_to_file(out, result, strlen(result));
//     fclose(out);
//     free(result);
//     free(my_test[0]);
//     free(my_test[1]);
// }