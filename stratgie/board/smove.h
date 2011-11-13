#ifndef CMOVE_H
#define CMOVE_H

struct SMove
{
    int m_x;
    int m_y;
    char m_mark;
public:
    SMove();
    SMove(char mark);
    SMove(int x, int y, char mark);
    bool Initialized();
};

#endif // CMOVE_H
