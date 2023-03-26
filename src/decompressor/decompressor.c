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
    long tracer = 0;    // znacznik, który bajt jest aktualnie czytany

    fseek(in, 0, SEEK_END);     
    long file_length = ftell(in);         
    printf("Ilosc bajtow: %d\n", file_length);   
    fseek(in, 0, SEEK_SET);

    int codes_num = fgetc(in);
    tracer++;
    printf("Liczba znakow: %d\n", codes_num);

    char* symbols = malloc(codes_num * sizeof *symbols);
    int* code_lengths = malloc(codes_num * sizeof code_lengths);
    unsigned char* codes = malloc(codes_num * sizeof *codes);

    printf("Slownik:\n");
    for(int i = 0; i < codes_num; i++){
        symbols[i] = fgetc(in);
        code_lengths[i] = fgetc(in);
        codes[i] = fgetc(in);
        tracer += 3;
        printf("%c - ", symbols[i]);
        print_binary(codes[i], code_lengths[i]);
    }

    // Odczytaj treść pliku
    while(tracer != file_length){
        char byte = fgetc(in);
        tracer++;
        // Tutaj będzie kod odpowiedzialny za odkodowanie treści pliku
    }


    free(symbols);
    free(code_lengths);
    free(codes);
    return 0;
}
