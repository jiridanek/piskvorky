#include <algorithm>

using std::max;
using std::min;

#include "board/cboard.h"
#include "board/cmovegenerator.h"
#include "func.h"
#include "piskorky.h"
#include "func.h"
#include "minimax.h"

int DIRECTION2[8][2] = { { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }};

/*!
  aplikuje tahy, ohodnotí volná pole a vrátí několik tahů co vedou na pozice s nejlepším ohodnocením

  \param pole tahů
  \param stav desky
 */
//char hrac, const char pole[][])

/*!
 smaže předpředchozí vrstvu, zpracuje aktualní, čímž vytvoří novou
 */

int search(CBoard &board, int x, int y, int direction, int skip, char hrac);

bool has_n_or_more_in_row(CBoard &board, int n, char hrac) {
    for (int x = 0; x < board.GetWidth(); ++x) {
        for (int y=0; y < board.GetHeight(); ++y) {
            for (int dir=0; dir<4; ++dir) {
                const int count = search(board, x, y, dir, 0, hrac);
                if (count >= n) {
                    return true;
                }
            }
        }
    }
    return false;
}

int search_not_player(CBoard &board, int x, int y, int direction, int skip, char hrac) {
    int sum = 0;
    int newsum = 0;
    do {
        newsum = 0;
        newsum += search(board, x, y, direction, skip+sum+newsum,get_other_player(hrac));
        newsum += search(board, x, y, direction, skip+sum+newsum, CBoard::EMPTY_POSITION);
        sum += newsum;
    } while (newsum != 0);
    return sum;
}

int search(CBoard &board, int x, int y, int direction, int skip, char hrac) {
    char cnt = 0;
    int dx = DIRECTION2[direction][0];
    int dy = DIRECTION2[direction][1];

    int px = x+skip*dx;
    int py = y+skip*dy;
    while(board.CanGet(px, py)) {
        if(board.Get(px, py) == hrac) {
            cnt++;
        } else {
            return cnt;
        }
        px += dx; py += dy;
    }
    return cnt;
}

long long evaluate(CBoard &board, char hrac) {
    long long sum = 0;
    // free, one side free, cannot make 5
    const int points[6][3] = {
        {0,0,0}, {1,1,1}, {100,50,5}, {100000,200,1}, {5000000, 1000000, 300}, {10000000, 10000000, 10000000}
    };
    for (int x = 0; x < board.GetWidth(); ++x) {
        for (int y=0; y < board.GetHeight(); ++y) {
            for (int dir=0; dir<4; ++dir) {

                int opposite_dir = (dir + 4) % 8;
                int op_count = search(board, x, y, opposite_dir, 0, hrac);
                if (op_count != 1) {
                    continue;
                }

                int op_free_count = search_not_player(board, x, y, opposite_dir, op_count, get_other_player(hrac));
                int count = search(board, x, y, dir, 0, hrac);
                int free_count = search_not_player(board, x, y, dir, count, get_other_player(hrac));
                int total_count = op_free_count + free_count + count;
                int value;
                if(op_free_count>0 && free_count > 0 && total_count >= 5) {
                    value = 0;
                } else if (total_count >= 5) {
                    value = 1;
                } else {
                    value = 2;
                }

                if (count > 5) {
                    count = 5;
                }
                sum += points[count][value];
            }
        }
    }
    return sum;
}

/*!
 normální rekurzivní verze
 */
int minimax(char hrac, CBoard &board, int depth) {
    char MAX = 'X';
    //char MIN = 'O';

    char other_player = get_other_player(hrac);

    if(depth == 0) {
        return evaluate(board, hrac) - evaluate(board, get_other_player(hrac));
    }

    CMoveGenerator mg = board.CreateMoveGenerator(hrac);
    struct SMove m = mg.GetNextMove();

    //if (hrac == MAX) {
        int tmp_max = -1000000;
        while(m.Initialized()) {
            //CBoard candidate_board(board, m);
            board.ApplyMove(m);
            int nmax = minimax(other_player, board, depth - 1);
            tmp_max = max(tmp_max, nmax);
            board.UndoMove(m);
            m = mg.GetNextMove();
        }
        return tmp_max;
//    } else {
//        int tmp_min = 1;
//        while(m.Initialized()) {
//            CBoard candidate_board(board, m);
//            int nmin = (-1) * minimax(other_player, candidate_board, depth-1);
//            tmp_min = min(tmp_min, nmin);
//            m = mg.GetNextMove();
//        }
//        return tmp_min;
//    }
}

