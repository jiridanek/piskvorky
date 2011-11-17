#ifndef MINIMAX_H
#define MINIMAX_H

#include "board/cboard.h"

int minimax(char hrac, CBoard &board, int depth);
int search(const CBoard &board, int x, int y, int direction, int skip, char hrac);
int search_not_player(const CBoard &board, int x, int y, int direction, int skip, char hrac);
int search(const CBoard &board, int x, int y, int direction, int skip, char hrac);
long long evaluate(const CBoard &board, char hrac);
int minimax(char hrac, const CBoard &board, int depth);
bool has_n_or_more_in_row(const CBoard &board, int n, char hrac);

#endif // MINIMAX_H