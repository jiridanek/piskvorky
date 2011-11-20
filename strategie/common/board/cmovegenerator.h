class CBoard;

#ifndef CMOVEGENERATOR_H
#define CMOVEGENERATOR_H

#include <vector>
#include <map>

#include "cboard.h"
#include "smove.h"

using std::vector;
using std::map;

class CBoard;

class CMoveGenerator
{
    const CBoard &m_board;
    struct SMove m_previous_move;
    vector<struct SMove> m_try_first;
    map<struct SMove, bool> m_tried_moves;
public:
    CMoveGenerator(const CBoard &board, char c);
    struct SMove GetNextMove();
    bool TryMove(const SMove &m);
    void PrependMove(const SMove &m);
};

#endif // CMOVEGENERATOR_H
