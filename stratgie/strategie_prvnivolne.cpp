#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <func.h>
#include <load.h>

int placni_to_tam_nekam(char hrac, int initx, int inity, char pole[20][20]) {
    for(int y=inity; y < 20; y++) {
        for (int x=initx; x < 20; x++) {
            if (pole[x][y] == '.') {
                pole[x][y] = hrac;
                return 1;
            }
        }
    }
    return 0;
}

void randmove(int *x, int *y) {
    int oldx = *x;
    int oldy = *y;

    if (rand() % 3 == 0) {
        (*y)++;
    } else if (rand() % 3 == 0) {
        (*y)--;
    }
    if (rand() % 3 == 0) {
        (*x)--;
    } else if (rand() % 3 == 0) {
        (*x)++;
    }

    if (*y < 0 || *y > 19) {
        *y = oldy;
    }

    if (*x < 0 || *x > 19) {
        *x = oldx;
    }
}

void strategie_prvnivolne(char hrac, char pole[20][20]) {
    int initx = 5;
    int inity = 10;

    if(rand() % 3 > 0) {
        /* lepsi zacatek - scanY*/
        for(int x=0; x < 20; x++) {
            for (int y=initx; y < 20; y++) {
                if (pole[x][y] == hrac) {
                    initx = x;
                    inity = y;
                    goto hraj;
                }
            }
        }
    } else {
        /* lepsi zacatek - scanX*/
        for(int y=0; y < 20; y++) {
            for (int x=initx; x < 20; x++) {
                if (pole[x][y] == hrac) {
                    initx = x;
                    inity = y;
                    goto hraj;
                }
            }
        }
    }

    hraj: /* LABEL */

    //printf("%d, %d", initx, inity);
    randmove(&initx, &inity);
    //printf("%d, %d", initx, inity);

    if(! placni_to_tam_nekam(hrac, initx, inity, pole)) {
        placni_to_tam_nekam(hrac, 0,0, pole);
    }
}


int main(){
        srand ( time(NULL) );

    char hrac;
    char pole[20][20];
    load_input(&hrac, pole);

    strategie_prvnivolne(hrac, pole);

    printf("%c\n", get_other_player(hrac));
    vypis_pole(pole);
}
