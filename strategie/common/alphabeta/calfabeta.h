#ifndef CALFABETA_H
#define CALFABETA_H

#include "board/cboard.h"

#include "board/smove.h"

class CAlfaBeta
{
    static CAlfaBeta *singleton;
    int m_signal_number;
    sigset_t m_signal_set;

    CBoard &m_board;
    char m_player;

    int m_best_alfa;
    int m_best_beta;
    int m_depth;
    int m_current_call_depth;
    int m_finished_depths;

    vector<struct SMove> m_best_move;
    vector<long long> m_best_score;

    CAlfaBeta(CBoard &board, int depth, int signal_number);
public:
    static CAlfaBeta * New(CBoard &board, int depth, int signal_number);
    static CAlfaBeta * Get();
    struct SMove GetBestMove();
    long long GetBestScore();
    long long AlfaBeta(CBoard &board, long long alfa, long long beta, long long depth, char hrac);
    void Block();
    void Unblock();
    void StartProcessing(char hrac);
    CBoard& GetBoard();
    char GetPlayer();
    void StartProcessing();
};

#endif // CALFABETA_H
