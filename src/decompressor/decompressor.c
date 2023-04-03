// To jest dekompresor, najbrzydszy kod jaki w życiu napisałem ale działa
// Pliki testowe:
// test.bin "ALA MA[EOF]" (najprostszy test)
// test2.bin "ALM M[EOF]" (testowanie odkodowywania bajtów tak, że gdy w jednym bajcie zostanie 2 nieużyte bity, to zostaną uwzględnione dalej)
// test3.bin "ALA MA MAMA [EOF]" (wiele bajtów)

// UWAGA nie działa odokodowanie dla kodów dłóższych niż 8 (jeden bajt)
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

unsigned char make_mask(int n) {
    return (1 << (8-n)) - 1;
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

    fseek(in, 0, SEEK_END);
    long file_length = ftell(in);
    printf("Ilosc bajtow: %d\n", file_length);
    fseek(in, 0, SEEK_SET);

    int freeBits = fgetc(in);
    tracer++;
    printf("Liczba wolnych bitow: %d\n", freeBits);

    int codes_num = fgetc(in);
    tracer++;
    printf("Liczba znakow: %d\n", codes_num);

    char *symbols = malloc(codes_num * sizeof *symbols);
    int *code_lengths = malloc(codes_num * sizeof code_lengths);
    long long int *codes = malloc(codes_num * sizeof *codes);
    for(int i =  0; i < codes_num; i++)
        codes[i] = 0;

    printf("Slownik:\n");
    for (int i = 0; i < codes_num; i++) {
        symbols[i] = fgetc(in);
        code_lengths[i] = fgetc(in);
        tracer += 2;
        for(int j = 0; j < ((code_lengths[i] - 1) / 8) + 1; j++) {
            if(j > 0)
                codes[i] = codes[i] << 8;
            codes[i] = codes[i] | fgetc(in);
//            int nextByte = fgetc(in);
//            int move = code_lengths[i] % 8 == 0 ? code_lengths[i] : (code_lengths[i] / 8)*8 + 8;
//            int move = (code_lengths[i] / 8) + (8 - code_lengths[i]);
//            codes[i] = codes[i] << move;
            tracer++;
        }
        int move = ((code_lengths[i] % 8 == 0) ? 0 : (8 - (code_lengths[i] % 8)));
        codes[i] = codes[i] << move;
        printf("%c - ", symbols[i]);
        print_binary(codes[i], code_lengths[i]);
        printf("\n");
    }

    // Odczytaj treść pliku
    long long int byte = fgetc(in);
    int res = 0;    // liczba mówiąca, ile bitów zostało z poprzedniego bajtu
    while (tracer != file_length) {
        tracer++;
        int left = 8;    // liczba mówiąca, ile bitów zostało w aktualnym bajcie
        while (left > 0) {
                for (int j = 0; j < codes_num; j++) {
                    unsigned char byte_tmp = byte >> (8 - code_lengths[j] + res);   // tymczasowy bajt, który składa się z res poprzednich bitów i 8-code_length[j] nowych bitów
                    byte_tmp = byte_tmp << (8 - code_lengths[j]);
                    if( (byte_tmp == codes[j]) && (code_lengths[j] <= left) ){      // jeżeli bajt pasuje bajtowi kodu i jest wystarczająco krótki
                        fprintf(out, "%c", symbols[j]);
                        if(symbols[j] == 26)    // Jeżeli znak to [EOF]
                            goto end;

                        // Odpowiednio przesuń bity w bajcie
                        byte = (byte << (code_lengths[j] - res));
                        left -= code_lengths[j] - res;
                        res -= code_lengths[j];
                        if(res < 0)
                            res = 0;
                        unsigned char mask = make_mask(res);
                        byte = byte  & mask;
                        break;
                    }
                    if(j == codes_num - 1){
                        res = left;
                        left = 0;
                    }
                }
        }
        byte = (byte<<8) | fgetc(in);
    }



    end:
    fclose(in);
    fclose(out);
    free(symbols);
    free(code_lengths);
    free(codes);
    return 0;
}
