#include <vector>

#include "load.h"
#include "func.h"
#include "piskorky.cpp"
#include "board/smove.h"
#include "strategie_x.h"

using std::vector;

vector<struct SMove> strategie_x_get_good_moves(char hrac, char pole[20][20]) {
    vector<struct SMove> ret;
    vector<struct SMove> ret_utok;
    vector<struct SMove> ret_obrana;
    ret.reserve(5);
    ret_utok.reserve(5);
    ret_obrana.reserve(2);

    struct block souper = find_longest(get_other_player(hrac), pole);
    struct block ja = find_longest(hrac, pole);

    int x;
    int y;

        // utok
    if(ja.x1 != -1) {
       x = ja.x1 - DIRECTION[ja.direct][0];
       y = ja.y1 - DIRECTION[ja.direct][1];
        ret_utok.push_back((struct SMove) SMove(x, y, hrac));
        //put(hrac, ja.x1 - DIRECTION[ja.direct][0],  ja.y1 - DIRECTION[ja.direct][1], pole);
        x = ja.x1 + (DIRECTION[ja.direct][0]) * ja.len;
        y = ja.y1 + (DIRECTION[ja.direct][1]) * ja.len;
        ret_utok.push_back((struct SMove) SMove(x, y, hrac));
        //put(hrac, ja.x1 + (DIRECTION[ja.direct][0]) * ja.len,  ja.y1 + (DIRECTION[ja.direct][1]) * ja.len, pole);
    }
    if(souper.x1 != -1) {
        //obrana
        x = souper.x1 - DIRECTION[souper.direct][0];
        y = souper.y1 - DIRECTION[souper.direct][1];
        ret_obrana.push_back((struct SMove) SMove(x, y, hrac));
        //put(hrac, souper.x1 - DIRECTION[souper.direct][0],  souper.y1 - DIRECTION[souper.direct][1], pole);
        x = souper.x1 + (DIRECTION[souper.direct][0]) * souper.len;
        y = souper.y1 + (DIRECTION[souper.direct][1]) * souper.len;
        ret_obrana.push_back((struct SMove) SMove(x, y, hrac));
        //put(hrac, souper.x1 + (DIRECTION[souper.direct][0]) * souper.len,  souper.y1 + (DIRECTION[souper.direct][1]) * souper.len, pole);
    }

    if (souper.len >= 3) {
        ret.insert(ret.end(), ret_obrana.begin(), ret_obrana.end());
        ret.insert(ret.end(), ret_utok.begin(), ret_utok.end());
    } else {
        ret.insert(ret.end(), ret_utok.begin(), ret_utok.end());
        ret.insert(ret.end(), ret_obrana.begin(), ret_obrana.end());
    }
    return ret;
}
