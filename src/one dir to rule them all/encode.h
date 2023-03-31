#ifndef ENCODE_H
#define ENCODE_H

typedef struct
{
    unsigned char* char_code[256]; // kod przechowywany bezpośrednio w bitach
    short code_len[256]; // długość kodu w bitach
} code_struct; // przechowuje info o kodach dla każdego znaku

typedef struct
{
    unsigned char* data; // surowe dane
    long len;            // długość w bajtach zakodowanych danych (len(data))
    long max_size;       // rozmiar zaalokowany
    short byte_pos; // jeżeli == 0, to cały ostatni bajt (data[len-1]) jest zajęty.
                    // jeżeli != 0, to część bajtu data[len-1] jest zajęta, należy przejść do kolejnego bitu
} data_struct; // przechowuje zakodowaną treść pliku wejściowego

void fill_char_code(code_struct* code_info, unsigned char **my_test[2], int dic_len); // przekształca słownik na strukturę, która pozwala szybko wyszukać kod poszczególnych znaków

void compress (unsigned char* uncomp , int len, data_struct* message, code_struct* code_info);

#endif