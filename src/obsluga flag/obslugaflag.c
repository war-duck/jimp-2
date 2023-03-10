//Ten kod odpowiada za obsługę flag za pomocą getopta

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv) {

    int opcja=0;

    while((opcja = getopt(argc, argv, "i:o:th"))) {
        switch (opcja) {
        case 'i':
            if(optarg != NULL) {
                FILE *in = fopen(optarg, "r");
                if(in == NULL) {
                    printf("Nie mozna odczytywac z danego pliku.\n");
                    return 3;
                }
                else {
                    printf("Znaleziono plik.\n");
                    //tutaj będzie wywoływana funkcja wczytywania z pliku
                }
                break;
            }
        
        case 'o':
            if(optarg != NULL) {
                FILE *out = fopen(optarg, "w"); //jezeli plik nie istnieje to go tworzy
                if( out == NULL) {
                    printf("Brak uprawnień do zapisu w danym pliku.");
                    return 4;
                }
                else {
                    printf("Wypisuje do pliku: %s", optarg);
                    //tutaj będzie wywoływana funkcja wypisywania do pliku
                }
                break;
            }
        
        case 't':
            printf("Wczytywanie z konsoli.\n");
            //tutaj będzie wywoływana funkcja wczytywania z konsoli
            break;

        case 'h':
            printf("Program kompresuje bezstratnie pliki przy pomocy algorytmu Huffmana\n");
            printf("Uzycie:\n");
            printf("-i <plik> - wczytywanie danych z pliku\n");
            printf("-o <plik> - wypisywanie danych do pliku\n");
            printf("-t <dane> - wczytywanie danych z konsoli\n");
        
        default:
            return 0;
        }
    }
}