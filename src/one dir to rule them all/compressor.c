// moduł wywołuje funkcje wczytujące, analizujące, kompresujące dane wejściowe
#include "compressor.h"
#include "wczytywanie.h"
#include "queue.h"
#include "encode.h"
#include "output.h"
#include <string.h> // tymczasowo
void compress (FILE* in, FILE* out, unsigned long BUFFER_SIZE)
{
    struct input_data_info input;
    input.BUFFER_SIZE = BUFFER_SIZE;
    input.data = malloc(input.BUFFER_SIZE * sizeof(*input.data));
    input.num = calloc(256, sizeof(*input.num));
    input.length = 0;
    size_t read;
    // pierwszy odczyt, liczenie występowania poszczególnych bajtów
    while (read = fread (input.data, sizeof (*input.data), input.BUFFER_SIZE, in))
    {
        input.length += read;
        printf ("%s\n", input.data);
        for(int i = 0; i < read; i++)
            input.num[input.data[i]]++;    // Zlicz występowanie znaków
    }
    fseek(in, 0, SEEK_SET); // powrót na początek pliku
    fwrite("\0", sizeof(char), 1, out); // zostawienie wolnego miejsca na wpisanie liczby wolnych bajtów
    int code_num = 0; // ile różnych bajtów jest w pliku
    for (int i = 0; i < 256; ++i)
        if (input.num[i])
            ++code_num;
    //
    // tworzenie kolejki, drzewa
    // ja tego nie ogarniam, utworzę przypadkowe kody
    // tmp
    //
    unsigned char** dict[2];
    dict[0] = calloc (code_num,  sizeof (char*));
    dict[1] = calloc (code_num,  sizeof (char*));
    int j = 0;
    for (int i = 0; i < 256; ++i)
    {
        if (input.num[i])
        {
            dict[0][j] = calloc (2, sizeof(char));
            dict[1][j] = calloc (j+3, sizeof (char));
            dict[0][j][0] = i;
            dict[1][j][0] = '1';
            memset (dict[1][j]+1, 48, j+1);
            ++j;
        }
    }
    printf ("tymczasowy slownik:\n");
    for (int i = 0; i < code_num; ++i)
        printf ("%s, %d, %s\n", dict[0][i], i+2, dict[1][i]);
    //
    // koniec tmp
    // chodzi o to, żeby na tutaj na wyjściu była zmienna unsigned char** dict[2] z gotowym słownikiem
    //
    data_struct message = 
    {
        .data = calloc(input.BUFFER_SIZE, sizeof(char)),
        .len = 0,
        .byte_pos = 0,
        .max_size = input.BUFFER_SIZE
    };
    code_struct code_info = {.char_code = {0}, .code_len = {0}};
    fill_char_code(&code_info, dict, code_num); // konwertuje słownik na strukturę
    // for (int i = 0; i < 256; i++) // sprawdzenie poprawności zakodowania binarnego słownika
    // {
    //     if (code_info.code_len[i])
    //     {
    //         printf ("%c len: %d\n", (char)i, code_info.code_len[i]);

    //         print_str_in_bin(code_info.char_code[i], 1+(code_info.code_len[i]-1)/8, 0);
    //     }
    // }
    int compressed_dic_len; // kompresja i zapis do pliku słownika
    unsigned char* compressed_dic = dic_to_bin(dict, code_num, &compressed_dic_len);
    fwrite(compressed_dic, sizeof(char), compressed_dic_len, out); // dodajemy do pliku wyjściowego słownik
    // drugi odczyt, kompresja danych i zapis do pliku
    while (read = fread (input.data, sizeof (*input.data), input.BUFFER_SIZE, in))
    {
        encode(input.data, read, &message, &code_info);
        //print_str_in_bin(message.data, message.len, 0);
        if (message.byte_pos == 0) // jeżeli zakodowana wiadomość zajmuje równą ilość bajtów
        {
            fwrite(message.data, sizeof(char), message.len, out); // można po prostu wpisać do pliku
            memset (message.data, 0, message.max_size);
        }
        else
        {
            fwrite(message.data, sizeof(char), message.len-1, out); // wpisujemy bez ostatniego bajtu, bo nie jest dopełniony
            *message.data = message.data[message.len-1]; // ostatni staje się pierwszym, będzie wysłany z następną partią danych
            memset (message.data+1, 0, message.max_size-1);
        }
        message.len = 0;
    }
    if (message.byte_pos != 0) // trzeba dopisać ostatni, niedopełniony, bajt, bo został pominięty w pętli
        fwrite(message.data, sizeof(char), 1, out);
    fseek(out, 0, SEEK_SET); // na początku pliku wyjściowego wpisujemy liczbę niezapełnionych bitów w ostatnim bajcie
    char tmp = (char)message.byte_pos;
    fwrite(&tmp, sizeof(char), 1, out);
    //printf("Wielkosc pliku w bajtach: %d\n", input.length);   // Komunikat testowy
    for (int i = 0; i < code_num; ++i)
    {
        free (dict[0][i]);
        free (dict[1][i]);
    }
    free (dict[0]);
    free (dict[1]);
    free(input.num);
    free(input.data);
    fclose(in);
    fclose(out);
}