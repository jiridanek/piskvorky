#include <cstdio>
#include <algorithm>
#include <iostream>

#include <csignal>

#include "minimax.h"
#include "func.h"

//#include <cstdint>

#include "calphabetaparallel.h"

#define DEBUG_P

using std::max;
using std::cerr;
using std::endl;

CAlphaBetaParallel * CAlphaBetaParallel::singleton = 0;

CAlphaBetaParallel::CAlphaBetaParallel(CBoard & board, int depth, int signal_number) :
    m_signal_number(signal_number), m_board(board), m_depth(depth) {

    sigemptyset(&m_signal_set);
    sigaddset(&m_signal_set, signal_number);
}

void CAlphaBetaParallel::Block() {
    sigprocmask(SIG_BLOCK, &m_signal_set, NULL);
}

void CAlphaBetaParallel::Unblock() {
    sigprocmask(SIG_UNBLOCK, &m_signal_set, NULL);
}

CAlphaBetaParallel* CAlphaBetaParallel::New(CBoard &board, int depth, int signal_number) {
    if(singleton == NULL) {
        CAlphaBetaParallel::singleton = new CAlphaBetaParallel(board, depth, signal_number);
    }
    return CAlphaBetaParallel::singleton;
}

CAlphaBetaParallel* CAlphaBetaParallel::Get() {
    return singleton;
}



//pojišťuje si vítězství... někdy zahraje naprosto blbě, utoci misto braneni
long long CAlphaBetaParallel::AlfaBeta(CBoard &board, long long alfa, long long beta, long long depth, char hrac)
{
//    cerr << alfa << endl;
    if(depth == 0) {
       /* if (m_depth % 2 == 0) {
            return - evaluate(board, hrac) + evaluate(board, get_other_player(hrac));
        } else {*/
            //char natahu = (m_current_call_depth%2==0)?hrac:get_other_player(hrac);
            // na tahu je vždycky ten hrac, za ktereho se chystam hrat, tj jsem tu delal peknou blbost
            return evaluate_both_sides(board, hrac, hrac);
//            long long h_zisk = evaluate(board, hrac, default_points);
//            long long s_zisk = evaluate(board, get_other_player(hrac), default_points);
//            long long attack_bonus = (m_current_call_depth%2==1)?-1*(s_zisk/4) : 0;
//            return h_zisk + attack_bonus - s_zisk;
        //}
    }

    CMoveGenerator mg = board.CreateMoveGenerator(hrac);
    if(depth == m_current_call_depth && m_current_call_depth != m_depth) {
        struct SMove m = m_best_move[m_finished_depths];
        mg.PrependMove(m);
//        cerr << "Adding move " << m.m_x << " " << m.m_y << endl;
    }

    //int tmp_max = -1000000;
    struct SMove m = mg.GetNextMove();
//    cerr << "First move " << m.m_x << " " << m.m_y << endl;
    while(m.Initialized()) {
        board.ApplyMove(m);
#ifdef DEBUG_P
//                    board.Print(cerr);
//                    cerr << endl;
#endif
        long long new_max;
        //cerr << "5_or_" << endl;
        if(has_n_or_more_in_row(board, 5, hrac)){
            //ukonci rekurzi, nema smysl pokracovat za konec hry
            //aby bylo mozno vybrat nejlepsi zpusob jak vyhrat, pokud je jich vic ^_^
            new_max = 1LL*1000*1000*1000 + evaluate_both_sides(board, hrac, hrac);
            //cerr << "5_or_more_ for hrac " << hrac << " in depth " << m_current_call_depth << endl;
            //new_max = -AlfaBeta(board, -beta, -alfa, depth-1, get_other_player(hrac));
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
                if (m_current_call_depth != m_depth) {
                    //accept only if the new solution is better than previous?
                    if (m_best_score[index] > m_best_score[index-1]) {
                        m_finished_depths=m_current_call_depth-m_depth;
                    }
                }
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

SMove CAlphaBetaParallel::GetBestMove()
{
    return m_best_move[m_finished_depths];
}

long long CAlphaBetaParallel::GetBestScore()
{
    return m_best_score[m_finished_depths];
}

CBoard & CAlphaBetaParallel::GetBoard() {
    return m_board;
}

void CAlphaBetaParallel::StartProcessing(char hrac)
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
        AlfaBeta(m_board, -2LL*1000*1000*1000*1000, 2LL*1000*1000*1000*1000, d, hrac);
        m_finished_depths=d-m_depth;
        cerr << "Dokoncena uroven " << d << endl;
//        m_board.Print(cerr);
//         cerr << GetBestScore() << " " << GetBestMove().m_x << " " << GetBestMove().m_y << endl;
    }
}

char CAlphaBetaParallel::GetPlayer()
{
    return m_player;
}
