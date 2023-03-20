#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "output.h"
void fill_char_code(code_struct* code_info, unsigned char **my_test[2], int dic_len)
{
    unsigned char* ch, * code;
    for (int i = 0; i < dic_len; ++i)
    {
        ch   = my_test[0][i];
        code = my_test[1][i];
        code_info->code_len[*ch] = strlen(code); // długość kodu
        code_info->char_code[*ch] = malloc((1+(code_info->code_len[*ch]-1)/8) * sizeof(char));
        str_to_bin(code, code_info->code_len[*ch], code_info->char_code[*ch]); // z modułu output - przetwarza string "(0|1)*" na kod binarny i wsadza kod do char_code
    }
}

int compress(unsigned char* uncomp , int len, data_struct* message, code_struct* code_info)
{
    short cur_byte_pos = 0; //"wskaźnik" na pierwszy wolny bit.  0 - początek bajta >0<0111001 - 
    unsigned char* upos = uncomp, *cpos = message->data, cur_uncomp, *cur_code;
    short left; // ile bitow znaku zostalo
    int j;
    cpos = message->data+message->len;
    message->len += len; // pesymistyczna wersja - skompresowane dane zajmują tyle co nieskompresowane
    if (message->len > message->max_size)
        message->data = realloc(message->data, (message->max_size=message->max_size+64));
    for (int i = 0; i < len; ++i) // dla każdego znaku z niezakodowanej treści
    {
        cur_uncomp = *upos++;
        cur_code = code_info->char_code[cur_uncomp];
        left = code_info->code_len[cur_uncomp];
        //cur_byte_pos = (cur_byte_pos + left) % 8;
        for (j = 0; left > 0; ++j)
        {
            if (left % 8 != 0) // została część bajtu kodu do wpisania
            {
                if (left % 8 > 8 - cur_byte_pos) // więcej bitów kodu niż miejsca w bajcie
                {
                    *cpos++ |= (*cur_code >> (left % 8 - 8 + cur_byte_pos));
                    *cpos = '\0';
                    left -= (8 - cur_byte_pos); // wsadziliśmy tyle ile było miejsca w bajcie
                    cur_byte_pos = 0; // nowy bajt
                }
                else if (left % 8 < 8 - cur_byte_pos) // całość kodu zmieści się w bajcie z nadwyżką
                {
                    *cpos |= ((*cur_code++ << (8 - left % 8)) >> cur_byte_pos);
                    cur_byte_pos += left % 8;
                    left -= left % 8;
                }
                else // left % 8 == cur_byte_pos
                {
                    *cpos++ |= (*cur_code++ << cur_byte_pos) >> cur_byte_pos;
                    *cpos = '\0';
                    cur_byte_pos = 0;
                    left -= left % 8;
                }
            }
            else // zostały tylko pełne bajty kodu -> left = 8 * n
            {
                if (cur_byte_pos != 0) // nie zmieści się cały bajt kodu
                {
                    *cpos++ |= (*cur_code >> cur_byte_pos);
                    *cpos = '\0'; // zerujemy wartość nowego bajtu
                    left -= 8 - cur_byte_pos;
                    cur_byte_pos = 0; // nowy bajt, więc wolny pierwszy bit
                }
                else // zmieści się cały bajt kodu w bajcie message
                {
                    *cpos++ |= *cur_code++;
                    *cpos = '\0';
                    left -= 8;
                }
            }
        }
    }
    message->len = cpos - message->data + (cur_byte_pos ? 1 : 0);
    message->byte_pos = cur_byte_pos;
    print_str_in_bin(message->data, message->len, 1);
    printf ("nr wolengeo bitu: %d, dlugosc zakodowana: %d\n", message->byte_pos, message->len);
}
int main()
{
    int BUF_SIZE = 4096;
    data_struct message = {.data = malloc(BUF_SIZE * sizeof(char)), .len = 0, .byte_pos = 0, .max_size = BUF_SIZE};
    *(message.data) = '\0';
    code_struct code_info = {.char_code = {0}, .code_len = {0}};
    int num = 6;
    unsigned char **my_test[2];
    my_test[0] = malloc(num * sizeof(char*));
    my_test[1] = malloc(num * sizeof(char*));
    my_test[0][0] = "a";
    my_test[0][1] = "b";
    my_test[0][2] = "c";
    my_test[0][3] = "d";
    my_test[0][4] = "e";
    my_test[0][5] = "f";
    my_test[1][0] = "1";
    my_test[1][1] = "0";
    my_test[1][2] = "0000000";
    my_test[1][3] = "11111111";
    my_test[1][4] = "11";
    my_test[1][5] = "00001111";
    fill_char_code(&code_info, my_test, num);
    compress("fdeadeebfc", 10, &message, &code_info);
    return 0;
}