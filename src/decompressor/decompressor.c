#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "./../compressor/output.h"
void print_binary(uchar c, int length) {
    int i;
    for (i = length - 1; i >= 0; i--) {
        if (c & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

uchar make_mask(int n) {
    return (1 << (8-n)) - 1;
}

uchar* changeExtension(uchar* filename){
    int len = strlen(filename);
    filename[len - 3] = 't';
    filename[len - 2] = 'x';
    filename[len - 1] = 't';
    return filename;
}

int main(int argc, char** argv) {
    int BUF_SIZE = 50;
    uchar* data = malloc (BUF_SIZE * sizeof (uchar));
    FILE *in = fopen(argv[1], "rb");
    FILE *out = fopen(changeExtension(argv[1]), "w");

    fseek(in, 0, SEEK_END);
    long file_length = ftell(in);
    fseek(in, 0, SEEK_SET);
    int free_bits = fgetc(in);
    int code_num = fgetc(in);
    if (code_num == 0)
        code_num = 256;
    int len, len_in_bytes;
    uchar c, * code = calloc (32, sizeof(uchar)); // 32 - max dlugosc kodu zapisanego w bajtach
    treeNode* tree = makeTreeNode ('\0', 0);
    for (int i = 0; i < code_num; ++i)
    {
        c = fgetc(in);
        len = fgetc(in);
        len_in_bytes = 1 + (len - 1) / 8;
        fread (code, sizeof (uchar), len_in_bytes, in);

        addCharCode (tree, c, code, len, len % 8 ? 8 - len % 8 : 0);
        memset (code, 0, len_in_bytes); // czyszczenie zapelnionych bajtow - nie jest konieczne ale na wszelki wypadek
    }
    int i, j;
    treeNode* tree_walker; // wskaznik na obecny wierzcholek
    long int read;
    while (read = fread (data, sizeof (uchar), BUF_SIZE, in))
    {
        tree_walker = tree;
        for (i = 0; i < read; ++i)
        {
            for (j = 0; j < 8; ++j) // dla kazdego bita
            {
                if (tree_walker->c != '\0') // jeżeli znalezlismy znak
                {
                    if (tree_walker->c != 13)
                        fputc (tree_walker->c, out);
                    tree_walker = tree;
                }
                tree_walker = tree_walker->offspring[get_bit(data[i], j)];
            }
        }
    }
    fclose(in);
    fclose(out);
    free(code);
    freeTree (tree);
    return 0;
}
