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
    printf("%s\n", argv[1]);
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
    unsigned char byte = fgetc(in);
    while(tracer != file_length){
        tracer++;
        int rep = 0;
        while(rep < 8){
//            for(int j = 0; j < codes_num; j++){
//
//                if( (byte>>i) == (codes[j] >> (code_lengths[j] - 1)) ) {
//                    printf("%c", symbols[i]);
//                    unsigned char mask = (1 << i) - 1;
//                    byte = (byte >> (8-i)) & mask;
//                    break;
//                }
            for(int i = 7; i > rep; i--){
                for(int j = 0; j < codes_num; j++){
                    if( (byte>>i) == (codes[j] >> (code_lengths[j] - 1)) ) {
                        printf("%c", symbols[j]);
//                      unsigned char mask = (1 << i) - 1;
                      byte = (byte << (8-i)) & 0b11111111;
//                        byte = (byte >> (8-i)) & 0x11111111;
                        break;
                    }
                }
                rep++;
            }

            byte = (byte<<8) + fgetc(in);
        }
    }


    free(symbols);
    free(code_lengths);
    free(codes);
    return 0;
}
