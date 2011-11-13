#include <cstdio>
#include "load.h"

void load_input(char *hrac, char pole[20][20]) {
    char tmp_c;

    fscanf(stdin, " %c", hrac);

    for(int y=0; y < 20; y++) {
        for (int x=0; x < 20; x++) {
            fscanf(stdin, " %c", &tmp_c);
            pole[x][y] = tmp_c;
        }
    }
}

char** load_board(char *hrac) {
    char pole[20][20];
    load_input(hrac, pole);

    char **ret = new char*[20];
    for (int x=0; x<20; ++x) {
        ret[x] = new char[20];
        for (int y=0; y<20; ++y) {
            ret[x][y] = pole[x][y];
        }
    }
    return ret;
}

void vypis_pole(char pole[20][20]) {
    for(int y=0; y < 20; y++) {
        for (int x=0; x < 20; x++) {
            printf("%c", pole[x][y]);
        }
        printf("\n");
    }
}



