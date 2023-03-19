#ifndef COMPRESS_H
#define COMPRESS_H

typedef struct
{
    unsigned char* char_code[256]; // kod przechowywany bezpośrednio w bitach
    short code_len[256]; // długość kodu w bitach
} code_struct; // przechowuje info o kodach dla każdego znaku

typedef struct
{
    char* data;
    long len;
    long max_size;
    short byte_pos;
} data_struct; // przechowuje zakodowaną treść pliku wejściowego

#endif