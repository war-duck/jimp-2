#include <stdlib.h>
#include <string.h>
#include "encode.h"
#include "output.h"
void fill_char_code(code_struct* code_info, unsigned char **my_test[2], int dic_len) // przekształca słownik na strukturę, która pozwala szybko wyszukać kod poszczególnych znaków
{
    unsigned char* ch, * code;
    for (int i = 0; i < dic_len; ++i)
    {
        ch   = my_test[0][i]; // znak
        code = my_test[1][i]; // kod zapisany w stringu
        code_info->code_len[*ch] = strlen(code); // długość kodu w bajtach
        code_info->char_code[*ch] = malloc((1+(code_info->code_len[*ch]-1)/8) * sizeof(char)); // alokuje miejsce na kod zapisany w bitach
        str_to_bin(code, code_info->code_len[*ch], code_info->char_code[*ch]); // funkcja z modułu output.c - przetwarza string "(0|1)*" na kod binarny i wsadza kod do char_code
    }
}

void encode (unsigned char* uncomp , int len, data_struct* message, code_struct* code_info)
{
    short cur_byte_pos = message->byte_pos; // nr pierwszego wolnego bita.  0 - początek bajta: >0<0111001 - 
    unsigned char* upos = uncomp; // obecnie czytany bajt z pliku wejściowego
    unsigned char* cpos = message->data; // obecnie edytowany bajt danych skompresowanych
    unsigned char* cur_code; // obecnie czytany bajt kodu danego znaku
    short left; // ile bitów kodu zostało do wczytania
    if (message->len + len > message->max_size) // jeżeli jakimś cudem nie starczy zaalokowanej pamięci
    {
        message->len = cpos - message->data;
        message->data = realloc(message->data, (message->max_size+=64));
        memset(message->data + message->max_size - 64, 0, 64);
        cpos = message->data+message->len;
    }
    cpos = message->data+message->len; // znajdujemy pierwszy wolny bajt
    for (int i = 0; i < len; ++i) // dla każdego znaku z niezakodowanej treści
    {
        if (message->data+message->max_size - cpos < 32)
        {
            message->len = cpos - message->data;
            message->data = realloc(message->data, (message->max_size+=64));
            memset(message->data + message->max_size - 64, 0, 64);
            cpos = message->data+message->len;
        }
        cur_code = code_info->char_code[*upos]; // bierzemy wskaźnik na pierwszy bajt kodu danego znaku
        left = code_info->code_len[*upos]; // wczytujemy długość kodu do wczytania
        while (left > 0) // aż cały kod będzie wczytany
        {
            if (left % 8 != 0) // została część bajtu kodu do wpisania
            {
                if (left % 8 > 8 - cur_byte_pos) // więcej bitów kodu niż miejsca w bajcie docelowym
                {
                    *cpos++ |= (*cur_code >> (left % 8 - 8 + cur_byte_pos));
                    left -= (8 - cur_byte_pos); // wsadziliśmy tyle ile było miejsca w bajcie
                    cur_byte_pos = 0; // nowy bajt --> zerowy bit
                }
                else if (left % 8 < 8 - cur_byte_pos) // całość kodu zmieści się w bajcie docelowym, z nadwyżką
                {
                    *cpos |= ((*cur_code++ << (8 - left % 8)) >> cur_byte_pos);
                    cur_byte_pos += left % 8;
                    left -= left % 8;
                }
                else // left % 8 == cur_byte_pos
                {
                    *cpos++ |= (*cur_code++ << cur_byte_pos) >> cur_byte_pos;
                    cur_byte_pos = 0;
                    left -= left % 8;
                }
            }
            else // zostały tylko pełne bajty kodu -> left = 8 * n
            {
                if (cur_byte_pos != 0) // nie zmieści się cały bajt kodu
                {
                    *cpos++ |= (*cur_code >> cur_byte_pos);
                    left -= 8 - cur_byte_pos;
                    cur_byte_pos = 0; // nowy bajt, więc wolny pierwszy bit
                }
                else // zmieści się cały bajt kodu w bajcie message
                {
                    *cpos++ |= *cur_code++;
                    left -= 8;
                }
            }
        }
        ++upos;
    }
    message->len = cpos - message->data + (cur_byte_pos ? 1 : 0); // ustawiamy poprawną długość danych wyjściowych
    message->byte_pos = cur_byte_pos;
}