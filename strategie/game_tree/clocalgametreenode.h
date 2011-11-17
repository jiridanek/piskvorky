#ifndef CLOCALGAMETREENODE_H
#define CLOCALGAMETREENODE_H

#include <vector>

#include<game_tree/igametreenode.h>

using std::vector;

class CLocalGameTreeNode : public IGameTreeNode
{
    double m_score;
    vector<IGameTreeNode*> descendants;
public:
    CLocalGameTreeNode();
    //void TurnIntoRemoteNode();

};

#endif // CLOCALGAMETREENODE_H
