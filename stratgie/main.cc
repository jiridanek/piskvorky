#include <iostream>

#include "board/cboard.h"
#include "load.h"
#include "minimax.h"
#include "func.h"
#include "minimax.cpp"
#include "CAlfaBeta/calfabeta.h"

using std::cout;
using std::endl;

int main() {
    char hrac;
    CBoard board(20, 20, load_board(&hrac));

    int depth = 4;
    char other = get_other_player(hrac);

   // cout << evaluate(board, hrac) << endl;
   // cout << evaluate(board, other) << endl;

//    CMoveGenerator mg = board.CreateMoveGenerator(hrac);
//    struct SMove m = mg.GetNextMove();
//    int highest = minimax(other, board, depth);
//    struct SMove highest_m = m;
//    while (m.Initialized()) {
//        //CBoard candidate_board(board, m);
//        board.ApplyMove(m);
//        int new_value = minimax(other, board, depth);
//        if (new_value > highest) {
//            highest = new_value;
//            highest_m = m;
//        }
//        board.UndoMove(m);
//        m = mg.GetNextMove();
//    }
    CAlfaBeta ab(depth);
    ab.AlfaBeta(board, -2000000, 2000000, depth, hrac);
    struct SMove highest_m = ab.GetBestMove();
    int highest = ab.GetBestScore();
//    cout << highest << " " << highest_m.m_x << " " << highest_m.m_y << endl;

    cout << other << endl;
    CBoard(board, highest_m).Print();

    return 0;
}
