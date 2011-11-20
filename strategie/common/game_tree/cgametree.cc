#include <algorithm>
#include <stack>
#include <vector>

#include "func.h"
#include "minimax.h"
#include "cgametree.h"

using std::min;
using std::push_heap;
using std::pop_heap;
using std::stack;

CGameTree::CGameTree(CBoard &board, char player, int starting_depth, int maximal_depth) :
    m_board(board){
    m_starting_depth = starting_depth;
    m_maximal_depth = maximal_depth;
    root = new CLocalGameTreeNode(NULL, m_board, player,-2LL*1000*1000*1000*1000, 2LL*1000*1000*1000*1000, starting_depth);
    root->m_move_generator = new CMoveGenerator(board, player);

    m_curr_no_branches = 0;
    m_good_branches.resize(m_max_no_branches);
}

void CGameTree::AddBranch(CLocalGameTreeNode *end_node) {
    int index = (int) min(m_max_no_branches-1, m_curr_no_branches);
    if (index == m_max_no_branches-1 && m_good_branches[index]!= NULL) {

        // we are deleting a previously added branch
        // it should not have any descendents, so we are free to proceed like this
        CLocalGameTreeNode *this_node = m_good_branches[index];
        CLocalGameTreeNode *next_node = this_node->GetPrevious();
        while(next_node != NULL) {
            delete this_node;
            this_node = next_node;
            next_node = this_node->GetPrevious();
        }
        delete this_node;
    }
    m_good_branches[index] = end_node;
    //deep copy up
    CLocalGameTreeNode *current =  end_node;
    CLocalGameTreeNode *previous = end_node->GetPrevious();
    while(previous != NULL) {
        current->SetPrevious(new CLocalGameTreeNode(*previous));
        current = previous;
        previous = previous->GetPrevious();
    }
    m_curr_no_branches = index+1;
    push_heap(m_good_branches.begin(), m_good_branches.begin()+index);
}

CLocalGameTreeNode * CGameTree::PopBranch() {
    CLocalGameTreeNode *b = m_good_branches.front();
    pop_heap(m_good_branches.begin(), m_good_branches.begin()+m_curr_no_branches-1);
    m_curr_no_branches -= 1;
    return b;
}

/*!
 assumes that the previous node on the stack is the parent of the current node
 */
void CGameTree::RunAlphaBeta(CLocalGameTreeNode *from_node) {
    int current_iteration_depth = m_starting_depth;
    stack<CLocalGameTreeNode*> S;
    S.push(from_node);
    while( ! S.empty()) {
        CLocalGameTreeNode *node = S.top();
        const char player = node->m_player;
        const int depth_remaining = node->m_depth_remaining;
        CBoard &board = node->m_board;
        // We are in a leaf
        if(depth_remaining == 0) {
            S.pop();
            // S cannot be empty now
            assert( ! S.empty());
            if (! S.empty()) {
                int predek_depth = current_iteration_depth-depth_remaining-1;
                long long nvalue = 0;
                CLocalGameTreeNode *predek = S.top();
                if(predek_depth%2 == 0) {
                    nvalue = evaluate_both_sides(board, player, get_other_player(player));

                    //we are updating alpha
                    if(predek->GetAlpha() < nvalue) {
                        predek->SetAlpha(nvalue);
                        predek->m_best_yet_move = node->GetMove();
                    }
                } else {
                    nvalue = evaluate_both_sides(board, player, player);
                    //updating beta
                    if(predek->GetBeta() > nvalue) {
                        predek->SetBeta(nvalue);
                        predek->m_best_yet_move = node->GetMove();
                    }
                }
//                AddBranch(node);
            }

            // unduju tah
            if(node->GetMove().Initialized()) {
                board.UndoMove(node->GetMove());
            }
            continue;
        }
        //! Here goes AlphaBeta prunning
        struct SMove m = node->m_move_generator->GetNextMove();
        const long long alpha = node->m_best_yet_alpha;
        const long long beta = node->m_best_yet_beta;
        if (m.Initialized() && alpha < beta) {
            board.ApplyMove(m);
            CLocalGameTreeNode *new_node = new CLocalGameTreeNode(node, board, player, alpha, beta, depth_remaining - 1);
            new_node->m_move_generator = new CMoveGenerator(board, player);
            new_node->SetMove(m);
            S.push(new_node);
        } else {
            // prosel jsem vsecky potomky
            // unduju tah
            if(node->GetMove().Initialized()) {
                board.UndoMove(node->GetMove());
            }
            S.pop();
            if (! S.empty()) {
                int predek_depth = current_iteration_depth-depth_remaining-1;
                CLocalGameTreeNode *predek = S.top();
                //minimax
                if(predek_depth%2 == 0) {
                    //we are updating alpha
                    if(predek->GetAlpha() < node->GetBeta()) {
                        predek->SetAlpha(node->GetBeta());
                        predek->m_best_yet_move = node->GetMove();
                    }
                } else {
                    //updating beta
                    if(predek->GetBeta() > node->GetAlpha()) {
                        predek->SetBeta(node->GetAlpha());
                        predek->m_best_yet_move = node->GetMove();
                    }
                }
                //v kazdem pripade si uloz cestu, pokud je v S uz jen vrchol
/*                if (S.size() == 1) {
                    AddBranch();
                }
 */           }
            continue;
        }
    }
}
