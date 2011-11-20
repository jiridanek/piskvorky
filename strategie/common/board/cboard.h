#ifndef CBOARD_H
#define CBOARD_H

#include <cassert>

#include "cmovegenerator.h"
#include <iostream>
#include <ostream>

using std::ostream;
using std::cout;

class CMoveGenerator;

class CBoard
{
public:
    static const char EMPTY_POSITION;
private:
    char **m_board;
    int m_size_x;
    int m_size_y;
public:
    CBoard(int size_x, int size_y);
    CBoard(int size_x, int size_y, char **board);
    CBoard(CBoard &board, struct SMove move);
    CBoard(const CBoard &other);
    ~CBoard();
    void InitBoard(int size_x, int size_y, char c);
    void ComputeWeights();
    CMoveGenerator CreateMoveGenerator(char c) const;
    int GetWidth() const;
    int GetHeight() const;
    void Put(int x, int y, char c);
    inline char Get(int x, int y) const;
    bool ApplyMove(struct SMove move);
    void UndoMove(struct SMove move);
    inline bool CanGet(int x, int y) const;
    void Print(ostream &stream = cout) const;
    char** LeakM_Board() const;
};

inline bool CBoard::CanGet(int x, int y) const{
    return x > -1 && x < m_size_x && y > -1 && y < m_size_y;
}

inline char CBoard::Get(int x, int y) const{
    assert(this->CanGet(x, y));
    return m_board[x][y];
}


#endif // CBOARD_H
