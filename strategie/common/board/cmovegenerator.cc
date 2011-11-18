#include "cboard.h"
#include "smove.h"
#include "strategie_x.h"
//#include "strategie_x.cpp"

#include "board/cboard.h"
#include "cmovegenerator.h"

#include <vector>

#include <cstdlib>
#include <map>

using std::vector;
using std::map;
using std::pair;

//char **to_char_star_star(char pole[20][20]) {

//}

CMoveGenerator::CMoveGenerator(const CBoard &board, char c) :
    m_board(board), m_previous_move(c) {
//  to_char_star_star(m_board.LeakM_Board());
    char **pp = board.LeakM_Board();
    char p[20][20];
    for (int x=0; x < 20; ++x) {
        for (int y=0; y<20; ++y) {
            p[x][y] = pp[x][y];
        }
    }
    m_try_first = strategie_x_get_good_moves(c, p);
}

bool CMoveGenerator::TryMove(const struct SMove &m) {
    //FIXME: Pomaha nebo skodi?
    // zda se, ze kdyz skodi, tak malo, a kdyz pomuze, tak hodne; nechat
    //return true;
    if (m_tried_moves.find(m) == m_tried_moves.end()) {
        m_tried_moves.insert(pair<struct SMove, bool>(m, true));
        return true;
    }
    return false;
}

SMove CMoveGenerator::GetNextMove() {
    if (m_try_first.size() > 0) {
        struct SMove m;
        do {
            m = m_try_first.back();
            m_try_first.pop_back();
            if (m_board.CanGet(m.m_x, m.m_y)
                    && m_board.Get(m.m_x, m.m_y) == CBoard::EMPTY_POSITION
                    && this->TryMove(m)) {
                return m;
            } else if (m_try_first.size() > 0) {
                continue;
            } else {
                break;
            }
        } while(true);
    }

    if ( ! m_previous_move.Initialized()) {
        m_previous_move.m_x = 0;
        m_previous_move.m_y = 0;
    }

    // trivial version
    int x = m_previous_move.m_x+1;
    int y=m_previous_move.m_y;
    for (; y < m_board.GetHeight(); ++y) {
        for (; x < m_board.GetWidth(); ++x) {
            if (m_board.Get(x, y) == CBoard::EMPTY_POSITION) {
                if(! this->TryMove(SMove(x, y, m_previous_move.m_mark))) {
                    continue;
                }
                // small improvement - only adjectant positions
                for (int a=-1; a <= 1; ++a) {
                    for (int b=-1; b<=1; ++b) {
                        if(m_board.CanGet(x+a, y+b)
                                && m_board.Get(x+a, y+b) != CBoard::EMPTY_POSITION) {
                            goto found;
                        }
                    }
                }

            }
        }
        x = 0;
    }

    // not found
    x = -1;
    y = -1;

    found:
        struct SMove new_move = SMove(x, y, m_previous_move.m_mark);
        m_previous_move = new_move;
        return new_move;
}

void CMoveGenerator::PrependMove(const SMove &m) {
    m_try_first.push_back(m);
}


