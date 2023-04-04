// Kod dekompresujący plik

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_binary(long long int c, int length) {
    int i;
    int start = (length % 8 == 0) ? length : ((length / 8) * 8 + 8);
//    int end = (length % 8 == 0) ?
    for (i = start - 1; i >= (start - length) ; i--) {
        if (c & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

long long int make_mask(int n, int byteNum) {
    return (1 << (8-n*byteNum)) - 1;
}

char* changeExtension(char* filename){
    int len = strlen(filename);
    filename[len - 3] = 't';
    filename[len - 2] = 'x';
    filename[len - 1] = 't';
    return filename;
}

int main(int argc, char** argv) {
    printf("%s\n", argv[1]);
    FILE *in = fopen(argv[1], "rb");
    FILE *out = fopen(changeExtension(argv[1]), "w");
    long tracer = 0;    // znacznik, który bajt jest aktualnie czytany

    // Znajdź długość pliku
    fseek(in, 0, SEEK_END);
    long file_length = ftell(in);
    printf("Ilosc bajtow: %d\n", file_length);
    fseek(in, 0, SEEK_SET);

    // Ilość wolnych bitów w ostatnim bajcie
    int freeBits = fgetc(in);
    tracer++;
    printf("Liczba wolnych bitow: %d\n", freeBits);

    // Liczba znaków w słowniku
    int codes_num = fgetc(in);
    tracer++;
    printf("Liczba znakow: %d\n", codes_num);

    char *symbols = malloc(codes_num * sizeof *symbols);
    int *code_lengths = malloc(codes_num * sizeof code_lengths);
    long long int *codes = malloc(codes_num * sizeof *codes);
    for(int i =  0; i < codes_num; i++)
        codes[i] = 0;

    // Odczytaj słownik
    printf("Slownik:\n");
    for (int i = 0; i < codes_num; i++) {
        symbols[i] = fgetc(in);
        code_lengths[i] = fgetc(in);
        tracer += 2;

        for(int j = 0; j < ((code_lengths[i] - 1) / 8) + 1; j++) {
            if(j > 0)
                codes[i] = codes[i] << 8;
            codes[i] = codes[i] | fgetc(in);
            tracer++;
        }

        // Przesuń kody do lewej strony
        // np. kod "010" -> "01000000"
        int move = ((code_lengths[i] % 8 == 0) ? 0 : (8 - (code_lengths[i] % 8)));
        codes[i] = codes[i] << move;
        printf("%c - ", symbols[i]);
        print_binary(codes[i], code_lengths[i]);
        printf("\n");
    }

    // Odczytaj treść pliku
    long long int byte = fgetc(in);
    int byteNum = 1;
    int res = 0;    // ile bitów zostało z poprzedniego bajtu
    while (tracer != file_length) {
        tracer++;
        int left = 8;    // ile bitów zostało w aktualnym (nowym) bajcie
        while (left > 0) {
                for (int j = 0; j < codes_num; j++) {

                    // Usuń niepotrzebne bity
                    // np. długość kodu to 5: "11111111" -> "11111000"
                    int move = byteNum*8 - code_lengths[j] + res;
                    long long byte_tmp = byte >> move;
                    int codeByte = code_lengths[j] % 8 == 0 ? code_lengths[j]/8 : (code_lengths[j]/8 + 1);
                    move = codeByte * 8 - code_lengths[j];
                    byte_tmp = byte_tmp << move;

                    if( (byte_tmp == codes[j]) && (code_lengths[j] <= left + res) ){      // jeżeli bajt pasuje bajtowi kodu i jest wystarczająco krótki
                        if(symbols[j] != 13)    // pomiń znak "carriage return"
                            fprintf(out, "%c", symbols[j]);

                        // Odpowiednio przesuń bity w bajcie
                        byte = (byte << (code_lengths[j] - res));
                        left -= code_lengths[j] - res;
                        res -= code_lengths[j];
                        if(res < 0)
                            res = 0;
                        byteNum = res / 8 + 1;
                        long long int mask = make_mask(res, byteNum);
                        byte = byte  & mask;
                        if(tracer == file_length && left == freeBits)
                            goto end;
                        break;
                    }
                    if(j == codes_num - 1){
                        if(tracer == file_length && left == freeBits)
                            goto end;
                        res = left;
                        left = 0;
                    }
                }
        }

        byte = (byte<<res) | fgetc(in);

    }



    end:
    fclose(in);
    fclose(out);
    free(symbols);
    free(code_lengths);
    free(codes);
    return 0;
}
