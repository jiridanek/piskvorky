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
    bool operator< (const struct SMove &other) const {
        if (m_x < other.m_x) {
            return true;
        } else if(m_x == other.m_x && m_y < other.m_y){
            return true;
        } else {
            return false;
        }
    }
};

#endif // CMOVE_H
