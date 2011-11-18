/*!
 Iterativní prohlubování
    Nejlepší výsledek z předchozího běhu se zkusí použít
        Pamatovat si 5 sekvencí tahů (až do konce) s nejlepším skore z předchozího běhu a teď
        jimi v další iteraci začít
 Zkusit odstranit rekurzi - mohlo by se tím zjednodušit to znovupoužívání výsledků
    vlastní správa zásobníku,
    možná menší režie,
    případně lepší nasazení OpenMP?

    v kořeni budu na jednotlivé pohyby spouštět vlákna
        jakým způsobem to prochází ten herní strom? nebude náhodou někdy později lepší napřít síly na jeden nadějný podstrom? Je možné ten podstrom určit iterativním procházením?
            pokud z toho stromu bude pocházet nový práh pro alfabetu, najdu ho dřív a
                možná ani nebudu muset procházet ty další větve
        statistiku (graphviz) dělat nebudu, moc práce)
        asi větve souběžně s tím, že je to obrana před zvolením špatné větve jako té první.
 */

#ifndef CALPHABETAPARALLEL_H
#define CALPHABETAPARALLEL_H

class CAlphaBetaParallel// : public CAlfaBeta
{
public:
    static CAlphaBetaParallel *singleton;
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

    CAlphaBetaParallel(CBoard &board, int depth, int signal_number);
public:
    static CAlphaBetaParallel * New(CBoard &board, int depth, int signal_number);
    static CAlphaBetaParallel * Get();
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

#endif // CALPHABETAPARALLEL_H
