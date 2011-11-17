#include <cstdio>

#include "load.h"
#include "func.h"
#include "strategie_x.h"


int main() {
    char pole[20][20];
    char hrac;

    load_input(&hrac, pole);

    strategie_x(hrac, pole);

    printf("%c\n", get_other_player(hrac));
    vypis_pole(pole);
    return 0;
}
