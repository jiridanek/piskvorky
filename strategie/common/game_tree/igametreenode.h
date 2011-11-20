#ifndef IGAMETREENODE_H
#define IGAMETREENODE_H

class IGameTreeNode
{

public:
    IGameTreeNode();
    virtual double GetScore() = 0;
    virtual void AddDescendant() = 0;
};

#endif // IGAMETREENODE_H
