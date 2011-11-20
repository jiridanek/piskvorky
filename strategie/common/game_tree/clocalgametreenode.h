#ifndef CLOCALGAMETREENODE_H
#define CLOCALGAMETREENODE_H

#include <vector>

#include "board/cmovegenerator.h"
#include "game_tree/cgametree.h"
#include<game_tree/igametreenode.h>

using std::vector;

//class CLocalGameTreeNode;

class CLocalGameTreeNode //: public IGameTreeNode
{
    friend class CGameTree;

    CBoard &m_board;
    long long m_best_yet_alpha;
    long long m_best_yet_beta;
    struct SMove m_best_yet_move;
    int m_depth_remaining;
    char m_player;
    struct SMove m_move;
public:
    static bool soperator_lt(const CLocalGameTreeNode &inst1, const CLocalGameTreeNode &inst2);
    CMoveGenerator *m_move_generator;
    CLocalGameTreeNode *m_previous_node;
    // shared between nodes, nodes below have to undo their changes to make it
    // valid for this node

public:
    CLocalGameTreeNode(CLocalGameTreeNode *previous_node, CBoard &board, char natahu, long long alpha, long long beta, int depth_remaining);
    CLocalGameTreeNode(const CLocalGameTreeNode &inst);
    void SetMove(struct SMove m);
    struct SMove GetMove();
    CLocalGameTreeNode* GetPrevious();
    void SetPrevious(CLocalGameTreeNode*p) {
        m_previous_node = p;
    }

    long long GetBeta() const {
        return m_best_yet_beta;
    }
    void SetBeta(long long beta) {
        m_best_yet_beta = beta;
    }
    long long GetAlpha() const {
        return m_best_yet_alpha;
    }
    void SetAlpha(long long alpha) {
        m_best_yet_alpha = alpha;
    }
    struct SMove GetBestMove() {
        return m_best_yet_move;
    }

    long long GetBound(int depth) {
        if(depth%2 == 0) {
            return GetAlpha();
        } else {
            return GetBeta();
        }
    }

    void SetBound(long long value, int depth) {
        if(depth%2 == 0) {
            SetAlpha(value);
        } else {
            SetBeta(value);
        }
    }

    //void TurnIntoRemoteNode();

};

#endif // CLOCALGAMETREENODE_H
