#include "piskorky.h"

int DIRECTION[8][2] = { { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }};

//                       -->                                      <--

void end_position(struct block *block, const char pole[20][20], int direct, int *len)
{
	int y1 = block->y1;
	int x1 = block->x1;

        //FIXME Proč *len?
        if((y1+DIRECTION[direct][1]*(*len) >= 20) || (x1+DIRECTION[direct][0]*(*len) >= 20))
		return;
	
        if(pole[x1][y1] == pole[x1+DIRECTION[direct][0]*(*len)][y1+DIRECTION[direct][1]*(*len)])
	{
		end_position(block, pole, direct, &(++(*len)));
	} 
}

void find_direction(struct block *block, const char pole[20][20])
{
        char c = pole[block->x1][block->y1];
        for(int direct = 0; direct < 4; direct++)
	{
		int len = 1;
		end_position(block, pole, direct, &len);
		if(block->len < len)
		{
			block->len = len;
			block->direct = direct;
		}
	}
}

void find_sides(struct block *block, const char pole[20][20]){
	int result = 0;
	int x = block->x1;
	int y = block->y1;
	int d = block->direct;

        if(x-DIRECTION[d][0] >= 0 && y-DIRECTION[d][1] >= 0){
                if(pole[x-DIRECTION[d][0]][y-DIRECTION[d][1]] == '.'){
			result++;
		}	
	}
        if(x+DIRECTION[d][0] < 20 && y+DIRECTION[d][1] < 20){
                if(pole[x+DIRECTION[d][0]*block->len][y+DIRECTION[d][1]*block->len] == '.'){
			result++;
		}	
	}
	if(result == 0){
		block->side = NONE;
	} else if(result == 1){
		block->side = ONE;
	} else {
		block->side = BOTH;	
	}	 
}


struct block find_longest(char c, const char pole[20][20]){
	struct block current;
	current.x1 = -1;
	current.y1 = -1;
	current.len = 0;
	current.side = NONE;
	
	for(int y = 0; y < 20; y++){
		for(int x = 0; x < 20; x++){
                        struct block tmp;
                        if(pole[x][y] == c){
				tmp.x1 = x;
				tmp.y1 = y;
                                tmp.len = 0;
				find_direction(&tmp,pole);
				find_sides(&tmp,pole);
				if(current.len < tmp.len && tmp.side != NONE){
					current = tmp;
				}
                                //FIXME nechápu
				if(current.len == tmp.len && tmp.side > current.side){
					current= tmp;
				}
			}
		}	
	}
        return current;
}
