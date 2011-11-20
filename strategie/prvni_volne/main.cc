#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "strategie_prvnivolne.cpp"

int main(){
        srand ( time(NULL) );

    char hrac;
    char pole[20][20];
    load_input(&hrac, pole);

    strategie_prvnivolne(hrac, pole);

    printf("%c\n", get_other_player(hrac));
    vypis_pole(pole);
}
