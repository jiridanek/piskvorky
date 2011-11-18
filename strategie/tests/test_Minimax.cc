#include <iostream>

#include <unittest++/UnitTest++.h>
#include "board/cboard.h"
#include "board/cmovegenerator.h"
#include "board/smove.h"
#include "minimax.h"
#include "func.cpp"

using std::cout;
using std::endl;

SUITE(test_minimax) {
    TEST(simple) {
        CBoard board(5,1);
        board.Put(0,0,'X');
        board.Put(1,0,'X');
        board.Put(2,0,'X');
        //board.Put(3,0,'X');

        int depth = 1;
        char hrac = 'O';

        cout << evaluate(board, 'X', default_points) << endl;
        cout << evaluate(board, hrac, default_points) << endl;


        CMoveGenerator mg = board.CreateMoveGenerator('X');
        struct SMove m = mg.GetNextMove();
        int highest = minimax(hrac, board, depth);
        struct SMove highest_m = m;
        while (m.Initialized()) {
            CBoard candidate_board(board, m);
            int new_value = minimax(hrac, candidate_board, depth);
            if (new_value > highest) {
                highest = new_value;
                highest_m = m;
            }
            m = mg.GetNextMove();
        }
        cout << highest << " " << highest_m.m_x << " " << highest_m.m_y << endl;
    }
}
