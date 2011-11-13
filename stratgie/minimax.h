#ifndef MINIMAX_H
#define MINIMAX_H

#include "board/cboard.h"

int search(CBoard &board, int x, int y, int direction, int skip, char hrac);
int search_not_player(CBoard &board, int x, int y, int direction, int skip, char hrac);
int search(CBoard &board, int x, int y, int direction, int skip, char hrac);
long long evaluate(CBoard &board, char hrac);
int minimax(char hrac, CBoard &board, int depth);

#endif // MINIMAX_H
