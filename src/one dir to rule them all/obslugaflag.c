//Ten kod odpowiada za obsługę flag za pomocą getopta

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "compressor.h"

int main(int argc, char **argv) {
    FILE *in = NULL;
    FILE *out = NULL;
    int opcja=0;

    unsigned long BUFFER_SIZE = 50;

    while((opcja = getopt(argc, argv, "i:tb:h"))) {
        switch (opcja) {
        case 'i':
            if(optarg != NULL) {
                in = fopen(optarg, "rb");
                out = fopen(strcat(strtok(optarg, "."), ".cps"), "wb"); //stworzenie pliku wyjsciowego
                break;
            }
            else
                break;
        
        case 't':
            in = stdin;
            out = fopen("out.cps", "wb");
            break;

        case 'b':
            if(optarg != NULL) {
                BUFFER_SIZE = atoi(optarg);
                break;
            }
            else
                break;
        
        case 'h':
            printf("Program kompresuje bezstratnie pliki przy pomocy algorytmu Huffmana\n");
            printf("Uzycie:\n");
            printf("-i <plik> - wczytywanie danych z pliku\n");
            printf("-t <dane> - wczytywanie danych z konsoli\n");
            printf("-b <rozmiar_buffora> - zdefiniowanie rozmairu buffora (domyslnie=50)\n");
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

            compress (in, out, BUFFER_SIZE);
            return 0;
        }
    }
}