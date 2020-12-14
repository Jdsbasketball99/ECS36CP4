#include "AVL.h"
#include <iostream>



AVLTree::AVLTree()
{
    root_ = nullptr;
    size_ = 0;
}

void AVLTree::AVLInsert(int key)
{
    //calls insert helper function
    root_ = AVLInsertHelper(root_, key);
}

std::shared_ptr<BSTNode> AVLTree::AVLInsertHelper(std::shared_ptr<BSTNode> currentNode, int key)
{
    //recursive function to add new node
    if(currentNode == nullptr) {
        //adds node if spot is empty
		currentNode = std::make_shared<BSTNode>(key);
		size_++;
		return currentNode;
	}
	
    if (key < currentNode->key_)
    {
        //calls function and sets parent
        currentNode->left_ = AVLInsertHelper(currentNode->left_, key);
        currentNode->left_->parent_ = currentNode;
    }else if (key > currentNode->key_)
    {
        //calls function and sets parent
        currentNode->right_ = AVLInsertHelper(currentNode->right_, key);
        currentNode->right_->parent_ = currentNode;
    }else
    {
        return currentNode;
    }

    currentNode->height = 1 + max(height(currentNode->left_), height(currentNode->right_));

    int balanceFactor;
    if (currentNode == nullptr)
    {
        balanceFactor = -1;
    }else
    {
        balanceFactor = height(currentNode->left_) - height(currentNode->right_);
    }
    
     

    if(balanceFactor > 1 && key > currentNode->left_->key_)
    {
        //Left Right Rotation
        currentNode->left_ = Left(currentNode->left_);
        return Right(currentNode);
    }

    if(balanceFactor > 1 && key < currentNode->left_->key_)
    {
        //Left Left Rotation
        return Right(currentNode);
    }

    if(balanceFactor < -1 && key > currentNode->right_->key_)
    {
        //Right Right Rotation
        return Left(currentNode);
    }

    if(balanceFactor < -1 && key < currentNode->right_->key_)
    {
        //Right Left Rotation
        currentNode->right_ = Right(currentNode->right_);
        return Left(currentNode);
    }


    return currentNode;
    
    
}

int AVLTree::max(int a, int b)
{
    //returns the max of the two numbers
    if(a > b)
    return a;
    else
    return b;
    
}


int AVLTree::height(std::shared_ptr<BSTNode> v) const
{
    //returns height or -1 if node is a nullpointer
    if(v == nullptr)
    {
        return -1;
    }
    return v->height;
}
//rotates left
std::shared_ptr<BSTNode> AVLTree::Left(std::shared_ptr<BSTNode> v)
{
    //swpas pointers
    std::shared_ptr<BSTNode> right;
    right = v->right_;
    //creates temp pointer
    std::shared_ptr<BSTNode> temp;
    temp = right->left_;
    right->left_= v;
    v->right_ = temp;
    //updates height for changed nodes
    v->height = 1 + max(height(v->left_), height(v->right_));
    right->height = 1 + max(height(right->left_), height(right->right_));

    return right;
}

//rotates right
std::shared_ptr<BSTNode> AVLTree::Right(std::shared_ptr<BSTNode> v)
{
    //swaps pointers
    std::shared_ptr<BSTNode> left;
    left = v->left_;
    //creates temp pointer
    std::shared_ptr<BSTNode> temp;
    temp = left->right_;
    left->right_= v;
    v->left_ = temp;
//updates height for changed nodes.
    v->height = 1 + max(height(v->left_), height(v->right_));
    left->height = 1 + max(height(left->left_), height(left->right_));

    return left;
}