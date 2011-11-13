#include <cstdio>
#include <algorithm>
#include <iostream>

#include "calfabeta.h"
#include "minimax.h"
#include "func.h"

//#include <cstdint>

#define DEBUG_P

using std::max;
using std::cerr;
using std::endl;

CAlfaBeta::CAlfaBeta(int depth) :
        m_depth(depth) {}

long long CAlfaBeta::AlfaBeta(CBoard &board, long long alfa, long long beta, long long depth, char hrac)
{
    if(depth == 0) {
       /* if (m_depth % 2 == 0) {
            return - evaluate(board, hrac) + evaluate(board, get_other_player(hrac));
        } else {*/
            return evaluate(board, hrac) - evaluate(board, get_other_player(hrac));
        //}
    }

    CMoveGenerator mg = board.CreateMoveGenerator(hrac);

    //int tmp_max = -1000000;
    struct SMove m = mg.GetNextMove();
    while(m.Initialized()) {
        board.ApplyMove(m);
#ifdef DEBUG_P
//                    board.Print(cerr);
//                    cerr << endl;
#endif
        int new_max;
        if(has_n_or_more_in_row(board, 5, hrac)) {
            new_max = -AlfaBeta(board, -beta, -alfa, depth-1, get_other_player(hrac));
        } else {
            return evaluate(board, hrac) - evaluate(board, get_other_player(hrac));
        }
        if (alfa < new_max) {
            alfa = new_max;

#ifdef DEBUG_P
//            fprintf(stderr, "setting new alfa\n");
#endif
            if (depth == m_depth) {
                m_best_move = m;
                m_best_score = new_max;
#ifdef DEBUG_P
                cerr << "Nova nejlepsi:" << endl;
                cerr << "skore: " << m_best_score << endl;
                board.Print(cerr);
#endif
            }
        }
        board.UndoMove(m);
        if (beta <= alfa) {
#ifdef DEBUG_P
//            fprintf(stderr, "ab cutoff\n");
#endif
            return alfa;
        }
        m = mg.GetNextMove();
    }
    return alfa;
}

SMove CAlfaBeta::GetBestMove()
{
    return m_best_move;
}

long long CAlfaBeta::GetBestScore()
{
    return m_best_score;
}

