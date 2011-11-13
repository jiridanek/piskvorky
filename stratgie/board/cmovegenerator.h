class CBoard;

#ifndef CMOVEGENERATOR_H
#define CMOVEGENERATOR_H

#include <vector>

#include "cboard.h"
#include "smove.h"

using std::vector;

class CMoveGenerator
{
    const CBoard &m_board;
    struct SMove m_previous_move;
    vector<struct SMove> m_try_first;
public:
    CMoveGenerator(const CBoard &board, char c);
    struct SMove GetNextMove();
};

#endif // CMOVEGENERATOR_H
