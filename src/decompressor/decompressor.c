// prosty decompressor służący do testowania 
// w pliku test.bin zakodowana jest wiadomość
// "ala ma [EOF]"

#include <stdio.h>
#include <stdlib.h>
#include "decompressor.h"

void print_binary(unsigned char c, int length) {
    int i;
    for (i = length - 1; i >= 0; i--) {
        if (c & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}
int main(int argc, char** argv){
    FILE *in = fopen(argv[1], "rb");
    int codes_num = fgetc(in);
    printf("Liczba znakow: %d\n", codes_num);

    char* symbols = malloc(codes_num * sizeof *symbols);
    unsigned char* codes = malloc(codes_num * sizeof *codes);

    printf("Slownik:\n");
    for(int i = 0; i < codes_num; i++){
        symbols[i] = fgetc(in);
        int code_length = fgetc(in);
        codes[i] = fgetc(in);
        printf("%c - ", symbols[i]);
        print_binary(codes[i], code_length);
    }


    free(symbols);
    free(codes);
    return 0;
}
