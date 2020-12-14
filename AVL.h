#pragma once
#ifndef AVL_H
#define AVL_H
#include "BST.h"


class AVLTree: public BST, public BSTNode
{
    public:
    AVLTree();
    void AVLInsert(int key);
    std::shared_ptr<BSTNode> AVLInsertHelper(std::shared_ptr<BSTNode> currentnode, int key);
    int height(std::shared_ptr<BSTNode> v) const;
    int max(int, int);
    std::shared_ptr<BSTNode> Left(std::shared_ptr<BSTNode> v);
    std::shared_ptr<BSTNode> Right(std::shared_ptr<BSTNode> v);

};



#endif