#include <unittest++/UnitTest++.h>

#include "board/cboard.cc"
#include "board/cmovegenerator.cc"
#include "board/smove.cc"

SUITE (test_CBoard) {
    TEST(create) {
        CBoard board(2, 2);
    }
    TEST(put_get) {
        CBoard board(2, 2);
        board.Put(1,1, 'X');
        board.Put(1,1, 'O');
        CHECK_EQUAL('O', board.Get(1,1));
    }
    TEST(create_move_generator) {
        CBoard board(2, 2);
        board.Put(1,1, 'X');
        board.Put(0,0, 'O');
        CMoveGenerator mg = board.CreateMoveGenerator('X');
        struct SMove m = mg.GetNextMove();
        CHECK_EQUAL(1,m.m_x);
        CHECK_EQUAL(0,m.m_y);
        m = mg.GetNextMove();
        CHECK_EQUAL(0,m.m_x);
        CHECK_EQUAL(1,m.m_y);
        m = mg.GetNextMove();
        CHECK(! m.Initialized());
    }
}
