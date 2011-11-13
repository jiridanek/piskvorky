#ifndef CALFABETA_H
#define CALFABETA_H

#include "board/cboard.h"

#include "board/smove.h"

class CAlfaBeta
{
    int m_alfa;
    int m_beta;
    int m_depth;
    struct SMove m_best_move;
    long long m_best_score;
public:
    CAlfaBeta(int depth);
    struct SMove GetBestMove();
    long long GetBestScore();
    long long AlfaBeta(CBoard &board, long long alfa, long long beta, long long depth, char hrac);
};

#endif // CALFABETA_H
