#ifndef PISKORKY_H
#define PISKORKY_H

enum sides {NONE = 0, ONE = 1, BOTH = 2};

struct block {
        int x1;
        int y1;
        int len;
        int direct;
        enum sides side;
};

//int DIRECTION[8][2];

void end_position(struct block *block, const char pole[20][20], int direct, int *len);

void find_direction(struct block *block, const char pole[20][20]);
void find_sides(struct block *block, const char pole[20][20]);
struct block find_longest(char c, const char pole[20][20]);

#endif // PISKORKY_H
