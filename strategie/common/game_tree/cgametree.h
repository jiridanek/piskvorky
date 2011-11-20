#ifndef CGAMETREE_H
#define CGAMETREE_H

#include "game_tree/clocalgametreenode.h"
//#include "board/cboard.h"

#include <vector>

using std::vector;

class CLocalGameTreeNode;

class CGameTree
{
public:
    CLocalGameTreeNode *root;
private:
    //double (*m_evaluating_function)(const IGameTreeNode&);

    static const int m_max_no_branches = 10;
    int m_curr_no_branches;
    vector<CLocalGameTreeNode*> m_good_branches;
    CBoard &m_board;
    int m_maximal_depth;
    int m_starting_depth;
public:
    CGameTree(CBoard &board, char player, int starting_depth, int maximal_depth);
    void GetBestMove(int time_limit, int depth_limit);
    void CreateNode();
    void RunAlphaBeta(CLocalGameTreeNode *from_node);
    void AddBranch(CLocalGameTreeNode *end_node);
    CLocalGameTreeNode * PopBranch();
};

#endif // CGAMETREE_H
