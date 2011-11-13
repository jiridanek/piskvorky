#include "board/cboard.h"

#include "smove.h"
SMove::SMove() :
    m_x(-1), m_y(-1), m_mark(CBoard::EMPTY_POSITION) {}

SMove::SMove(char mark) :
    m_x(-1), m_y(-1), m_mark(mark) {}

SMove::SMove(int x, int y, char mark) :
    m_x(x), m_y(y), m_mark(mark) {}

bool SMove::Initialized() {
    return m_x != -1 && m_y != -1;
}
