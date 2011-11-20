#include "clocalgametreenode.h"

CLocalGameTreeNode::CLocalGameTreeNode(CLocalGameTreeNode *previous_node, CBoard &board, char natahu, long long alpha, long long beta, int depth_remaining) :
    m_board(board)
  , m_best_yet_alpha(alpha)
  , m_best_yet_beta(beta)
  , m_depth_remaining(depth_remaining)
  , m_player(natahu) {}

CLocalGameTreeNode::CLocalGameTreeNode(const CLocalGameTreeNode &inst) :
    m_board(inst.m_board)
  , m_best_yet_alpha(inst.m_best_yet_alpha)
  , m_best_yet_beta(inst.m_best_yet_beta)
  , m_depth_remaining(inst.m_depth_remaining)
  , m_player(inst.m_player)
  , m_move(inst.m_move){}

void CLocalGameTreeNode::SetMove(SMove m) {
    m_move = m;
}

SMove CLocalGameTreeNode::GetMove() {
    return m_move;
}

CLocalGameTreeNode * CLocalGameTreeNode::GetPrevious() {
    return m_previous_node;
}

bool CLocalGameTreeNode::soperator_lt(const CLocalGameTreeNode &inst1, const CLocalGameTreeNode &inst2) {
    return inst1.GetAlpha() < inst2.GetAlpha();
}

bool operator < (const CLocalGameTreeNode &inst1, const CLocalGameTreeNode &inst2) {
    const bool comparsion = CLocalGameTreeNode::soperator_lt(inst1, inst2);
    return comparsion;
}
