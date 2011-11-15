#include <cstdio>
#include <algorithm>
#include <iostream>

#include <csignal>

#include "calfabeta.h"
#include "minimax.h"
#include "func.h"

//#include <cstdint>

#define DEBUG_P

using std::max;
using std::cerr;
using std::endl;

CAlfaBeta * CAlfaBeta::singleton = 0;

CAlfaBeta::CAlfaBeta(CBoard & board, int depth, int signal_number) :
    m_signal_number(signal_number), m_board(board), m_depth(depth) {

    sigemptyset(&m_signal_set);
    sigaddset(&m_signal_set, signal_number);
}

void CAlfaBeta::Block() {
    sigprocmask(SIG_BLOCK, &m_signal_set, NULL);
}

void CAlfaBeta::Unblock() {
    sigprocmask(SIG_UNBLOCK, &m_signal_set, NULL);
}

CAlfaBeta* CAlfaBeta::New(CBoard &board, int depth, int signal_number) {
    if(singleton == NULL) {
        CAlfaBeta::singleton = new CAlfaBeta(board, depth, signal_number);
    }
    return CAlfaBeta::singleton;
}

CAlfaBeta* CAlfaBeta::Get() {
    return singleton;
}

long long CAlfaBeta::AlfaBeta(CBoard &board, long long alfa, long long beta, long long depth, char hrac)
{
    if(depth == 0) {
       /* if (m_depth % 2 == 0) {
            return - evaluate(board, hrac) + evaluate(board, get_other_player(hrac));
        } else {*/
            long long h_zisk = evaluate(board, hrac);
            long long s_zisk = evaluate(board, get_other_player(hrac));
            return h_zisk + /*(h_zisk/2)*/ - s_zisk;
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
        if(has_n_or_more_in_row(board, 5, hrac)){
            new_max = evaluate(board, hrac) * 1000;
        } else {
            new_max = -AlfaBeta(board, -beta, -alfa, depth-1, get_other_player(hrac));
        }

        if (alfa < new_max) {
            alfa = new_max;

#ifdef DEBUG_P
//            fprintf(stderr, "setting new alfa\n");
#endif
            if (depth == m_current_call_depth) {
                this->Block();
                int index = m_current_call_depth - m_depth;
                m_best_move[index] = m;
                m_best_score[index] = new_max;
#ifdef DEBUG_P
                cerr << "Nova nejlepsi:" << endl;
                cerr << "skore: " << m_best_score[index] << endl;
                board.Print(cerr);
#endif
                this->Unblock();
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
    return m_best_move[m_finished_depths];
}

long long CAlfaBeta::GetBestScore()
{
    return m_best_score[m_finished_depths];
}

CBoard & CAlfaBeta::GetBoard() {
    return m_board;
}

void CAlfaBeta::StartProcessing(char hrac)
{
    m_player = hrac;
    m_finished_depths = 0;

    m_best_move.resize(10);
    m_best_score.resize(10);

    for (int d = m_depth; d < m_depth+10;++d) {

    //int d = 4;
        //ab.AlfaBeta(board, -2L*1000, 2L*1000, m_depth, hrac);
        //ab.AlfaBeta(board, -2L*1000*1000, 2L*1000*1000, depth, hrac);
        m_current_call_depth = d;
        //CBoard temp(m_board);
        AlfaBeta(m_board, -2L*1000*1000*1000*1000, 2L*1000*1000*1000*1000, d, hrac);
        m_finished_depths=d-m_depth;
        cerr << "Dokoncena uroven " << d << endl;
//        m_board.Print(cerr);
//         cerr << GetBestScore() << " " << GetBestMove().m_x << " " << GetBestMove().m_y << endl;
    }
}

char CAlfaBeta::GetPlayer()
{
    return m_player;
}

