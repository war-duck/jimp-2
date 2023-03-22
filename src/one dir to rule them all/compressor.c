// moduł wywołuje funkcje wczytujące, analizujące, kompresujące dane wejściowe
#include "compressor.h"
#include "wczytywanie.h"

//int compress (FILE* in, FILE* out)
int main()
{
    FILE* in = fopen("test.txt", "rb");

    struct input_data_info input;
    input.BUFFER_SIZE = 50;
    input.max_data_size = input.BUFFER_SIZE;
    input.data = malloc(input.max_data_size * sizeof(*input.data));
    input.num = calloc(256, sizeof *input.num);
    // fseek(in, 0, SEEK_END);     // Ustaw wskaźnik na koniec pliku
    // input.length = ftell(in);
    // printf("Wielkosc pliku w bajtach: %d\n", input.length);   // Komunikat testowy
    // fseek(in, 0, SEEK_SET);     // Ustaw wskaźnik z powrotem na początek pliku
    while (wczytaj(in, &input))
    {
        printf ("len dotychczas: %d\n", input.length);
    }
printf("Wielkosc pliku w bajtach: %d\n", input.length);   // Komunikat testowy
    free(input.data);
    free(input.num);
    fclose(in);
    return 0;
}