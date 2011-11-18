#ifndef MINIMAX_H
#define MINIMAX_H

#include "board/cboard.h"
#include <limits>

const int default_points[6][3] = {
    {0,0,0}, {1,1,1}, {100,50,5}, {100000,200,1}, {50000000, 10000000, 300}, {10000000, 10000000, 10000000}
};

int minimax(char hrac, CBoard &board, int depth);
int search(const CBoard &board, int x, int y, int direction, int skip, char hrac);
int search_not_player(const CBoard &board, int x, int y, int direction, int skip, char hrac);
int search(const CBoard &board, int x, int y, int direction, int skip, char hrac);
long long evaluateLL(const CBoard &board, char hrac, const long long points[6][3]);
long long evaluate(const CBoard &board, char hrac, const int points[6][3]);
long long evaluate_both_sides(const CBoard &board, char hrac, char natahu);
int minimax(char hrac, const CBoard &board, int depth);
bool has_n_or_more_in_row(const CBoard &board, int n, char hrac);

#endif // MINIMAX_H
