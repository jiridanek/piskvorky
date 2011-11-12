#include <cstdio>
#include "load.h"

void load_input(char *hrac, char pole[20][20]) {
    char tmp_c;

    fscanf(stdin, " %c", hrac);

    for(int y=0; y < 20; y++) {
        for (int x=0; x < 20; x++) {
            fscanf(stdin, " %c", &tmp_c);
            pole[y][x] = tmp_c;
        }
    }
}

void vypis_pole(char pole[20][20]) {
    for(int y=0; y < 20; y++) {
        for (int x=0; x < 20; x++) {
            printf("%c", pole[y][x]);
        }
        printf("\n");
    }
}



