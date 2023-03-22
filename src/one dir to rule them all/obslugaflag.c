//Ten kod odpowiada za obsługę flag za pomocą getopta

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv) {
    FILE *in = NULL;
    FILE *out = NULL;
    int opcja=0;

    while((opcja = getopt(argc, argv, "i:o:th"))) {
        switch (opcja) {
        case 'i':
            if(optarg != NULL) {
                in = fopen(optarg, "r");
                break;
            }
        
        case 'o':
            if(optarg != NULL) {
                out = fopen(optarg, "w"); //jezeli plik nie istnieje to go tworzy
                break;
            }
        
        case 't':
            in = stdin;
            break;

        case 'h':
            printf("Program kompresuje bezstratnie pliki przy pomocy algorytmu Huffmana\n");
            printf("Uzycie:\n");
            printf("-i <plik> - wczytywanie danych z pliku\n");
            printf("-o <plik> - wypisywanie danych do pliku\n");
            printf("-t <dane> - wczytywanie danych z konsoli\n");
            break;

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
                printf("Przyjalem plik wejsciowy\n");
            }

            //sprawdzenie wyjscia
            if( out == NULL) {
                printf("Niewlasciwy format pliku wyjsciowego.\n");
                return 4;
            }
            else {
                printf("Przyjalem plik wyjsciowy.\n");
            }

            //tutaj bedzie wywolywana funkcja glowna programu w formacie np. funkcja(plik we/stdin, plik wy)
            
            return 0;
        }
    }
}