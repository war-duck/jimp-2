//Ten kod odpowiada za obsługę flag za pomocą getopta

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "wczytywanie.h"

int main(int argc, char **argv) {
    FILE *in = NULL;
    FILE *out = NULL;
    int opcja=0;

    while((opcja = getopt(argc, argv, "i:th"))) {
        switch (opcja) {
        case 'i':
            if(optarg != NULL) {
                in = fopen(optarg, "rb");
                out = fopen(strcat(strtok(optarg, "."), ".cps"), "wb"); //stworzenie pliku wyjsciowego
                break;
            }
        
        case 't':
            in = stdin;
            out = fopen("out.cps", "wb");
            break;
        
        case 'h':
            printf("Program kompresuje bezstratnie pliki przy pomocy algorytmu Huffmana\n");
            printf("Uzycie:\n");
            printf("-i <plik> - wczytywanie danych z pliku\n");
            printf("-o <plik> - wypisywanie danych do pliku\n");
            printf("-t <dane> - wczytywanie danych z konsoli\n");
            return 0;

        default:
            //sprawdzenie wejscia
            if(in == NULL) {
                printf("Nie mozna odczytywac z danego pliku.\n");
                return 3;
            }
            else if (in == stdin) {
                printf("Wczytywanie z konsoli.\n");
            }
            else {
                printf("Przyjeto plik wejsciowy\n");
            }

            //sprawdzenie wyjscia
            if( out == NULL) {
                printf("Nie mozna utworzyc pliku wyjsciowego.\n");
                return 4;
            }
            else {
                printf("Utworzono plik wyjsciowy.\n");
            }

            //main
            struct input_data_info input;
            input.BUFFER_SIZE = 50;
            input.max_data_size = input.BUFFER_SIZE;
            input.data = malloc(input.max_data_size * sizeof(*input.data));
            input.num = calloc(256, sizeof *input.num);
            input.length = 0;
            
            while (wczytaj(in, &input)) {
#ifdef DEBUG
                printf ("len dotychczas: %ld\n", input.length);
#endif
            }
#ifdef DEBUG
            printf("Wielkosc pliku w bajtach: %ld\n", input.length);   // Komunikat testowy
#endif

            free(input.data);
            free(input.num);
            fclose(in);
            fclose(out);
            
            return 0;
        }
    }
}