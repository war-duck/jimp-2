//Ten kod odpowiada za obsługę flag za pomocą getopta

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv) {

    int opcja=0;

    while((opcja = getopt(argc, argv, "i:o:tyh"))) { //trzeba pomyśleć nad flagami bo mogą być tylko pojedyncze znaki
        switch (opcja) {
        case 'i':
            if(optarg != NULL) {
                FILE *in = fopen(optarg, "r");
                if(in!=NULL)
                    printf("Znaleziono plik.\n");
                else
                    printf("Nie mozna odczytywac z danego pliku.\n");
                //tutaj będzie wywoływana funkcja wczytywania z pliku
                break;
            }
        
        case 'o':
            if(optarg != NULL) {
                FILE *out = fopen(optarg, "w"); //jezeli plik nie istnieje to go tworzy
                //tutaj będzie wywoływana funkcja wypisywania do pliku
                break;
            }
        
        case 't':
            printf("wczytywanie z konsoli\n");
            //tutaj będzie wywoływana funkcja wczytywania z konsoli
            break;
        
        case 'y':
            printf("wypisywanie na stdout\n");
            //tutaj będzie wywoływana funkcja wypisywania na stdout
            break;

        case 'h':
            printf("Program kompresuje bezstratnie pliki przy pomocy algorytmu Huffmana\n");
            printf("Uzycie:\n");
            printf("-i <plik> - wczytywanie danych z pliku\n");
            printf("-o <plik> - wypisywanie danych do pliku\n");
            printf("-ti <dane> - wczytywanie danych z konsoli\n");
            printf("-to - wypisywanie danych na stdout\n");
            break;
        }
    }

    return 0;
}