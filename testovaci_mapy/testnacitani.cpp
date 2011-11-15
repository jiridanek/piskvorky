#include <cstdio>
#include "load.h"

int main() {
    char pole[20][20];
    char hrac;

    load_input(&hrac, pole);

    printf("na tahu %c\n", hrac);
    vypis_pole(pole);

    return 0;
}
