#include <cstdio> //printf
#include <iostream>

#include <cassert>
#include "cboard.h"
#include "cmovegenerator.h"

using std::endl;
using std::ostream;

const char CBoard::EMPTY_POSITION = '.';

CBoard::CBoard(int size_x, int size_y) :
        m_size_x(size_x), m_size_y(size_y) {
    this->InitBoard(size_x, size_y, '-');
    m_size_x = size_x;
    m_size_y = size_y;
}

CBoard::CBoard(int size_x, int size_y, char **board) :
        m_size_x(size_x), m_size_y(size_y) {
    m_board = board;
}

CBoard::CBoard(const CBoard &other) {}

CBoard::CBoard(CBoard &board, struct SMove move) :
         m_size_x(board.GetWidth()), m_size_y(board.GetHeight()){
    this->InitBoard(board.GetWidth(), board.GetHeight(), '-');
    for (int x=0; x<board.GetWidth(); ++x) {
        for (int y=0; y<board.GetHeight(); ++y) {
            this->m_board[x][y] = board.Get(x, y);
        }
    }

    if (move.Initialized()) {
        this->ApplyMove(move);
    }
}

CBoard::~CBoard() {
    for (int x=0; x < m_size_x; ++x) {
        delete[] this->m_board[x];
    }
    delete[] this->m_board;
}

void CBoard::InitBoard(int size_x, int size_y, char c) {
    this->m_board = new char*[size_x];
    for (int x=0; x<m_size_x; ++x) {
        this->m_board[x] = new char[size_y];
        for (int y=0; y<m_size_y; ++y) {
            this->m_board[x][y] = c;
        }
    }
}

//void CBoard::ComputeWeights();

void CBoard::Put(int x, int y, char c) {
    assert(x > -1 && x < m_size_x);
    assert(y > -1 && y < m_size_y);
    m_board[x][y] = c;
}

int CBoard::GetHeight() const {
    return m_size_y;
}

int CBoard::GetWidth() const {
    return m_size_x;
}

CMoveGenerator CBoard::CreateMoveGenerator(char c) const {
    return CMoveGenerator(*this, c);
}

bool CBoard::ApplyMove(SMove move) {
    if ( ! move.Initialized()) {
        return false;
    }
    this->Put(move.m_x, move.m_y, move.m_mark);
    return true;
}

void CBoard::Print(ostream &stream) const {
    for(int y=0; y < m_size_y; y++) {
        for (int x=0; x < m_size_x; x++) {
            stream << m_board[x][y];
        }
        stream << endl;
    }
}

void CBoard::UndoMove(SMove move) {
    this->Put(move.m_x, move.m_y, CBoard::EMPTY_POSITION);
}

char** CBoard::LeakM_Board() const {
    return m_board;
}
