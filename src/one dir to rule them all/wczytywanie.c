// Ten kod poprawnie wczytuje bajty z pliku wejściowego i zapisuje je w wektorze unsigned char* c
// Kod można potem przekopiować (z dorbnymi edycjami) do większego programu

#include "wczytywanie.h"

unsigned long wczytaj(FILE* in, struct input_data_info* input){ // zwraca ilość wczytanych bajtów

    unsigned long i;
    unsigned long read = 0;      // Aktualna ilość wczytanych bajtów (w tej iteracji)
    input->num = calloc(256, sizeof *input->num);

    // Otwieranie pliku wejściowego
    // FILE *in = fopen(argv[1], "rb");
    // if (in == NULL)
    //     return 1;
    // fseek(in, 0, SEEK_END);     // Ustaw wskaźnik na koniec pliku
    // input->length += ftell(in);
    // printf("Wielkosc pliku w bajtach: %d\n", input->length);   // Komunikat testowy
    // fseek(in, 0, SEEK_SET);     // Ustaw wskaźnik z powrotem na początek pliku
    //input->data = malloc(BUFFOR_SIZE * sizeof(*input->data)); // nie warto osobno alokować z każdym wywołaniem funkcji, wywaliłem do nadfunkcji compress()
    //size_t liczba_odczyt = fread(input->data, sizeof(*input->data), input->length, in);   // Wczytaj treść pliku
    // printf("Liczba odczytanych bajtów: %d\n", liczba_odczyt);
    // printf("Wczytana tresc (tekstowa): %s\n", input->data);
    // input->num = calloc(256, sizeof *input->num);

    read = fread(input->data, sizeof(*input->data), input->BUFFER_SIZE, in);
    printf ("read: %d\n", read);
    // if((input->length - read) > input->BUFFER_SIZE){
    //     printf("Wczytana tresc (tekstowa): %s\n", input->data);
    //     for(i = 0; i < input->BUFFER_SIZE; i++)
    //         input->num[input->data[i]]++;    // Zlicz występowanie znaków
    // }
    // else{
    //     printf("Wczytana tresc (tekstowa): %s\n", input->data);
    //     for(i = 0; i < read; i++)
    //         input->num[input->data[i]]++;    // Zlicz występowanie znaków
    // }
    printf("Wczytana tresc (tekstowa): %s\n", input->data);
    for(i = 0; i < read; i++)
        input->num[input->data[i]]++;    // Zlicz występowanie znaków

    printf("Czestotliwosc wystepowania konkretnych bajtow:\n");
    for(i = 0; i < 256; i++)
        if (input->num[i])
            printf("%c - %d\n", i, input->num[i]);

    input->length += read;
    return read;
}