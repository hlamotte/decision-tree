#ifndef DECISIONTREE_HPP
#define DECISIONTREE_HPP

#include <iostream>
#include "NodeUtility.hpp"

class TreeNode
{
    // Access specifier
    public:
  
    // Data Members
    TreeNode* ChildLeft = NULL;
    TreeNode* ChildRight = NULL;
    int SplitFeature;
    int SplitCategory;
    float GiniGain;
  
    // Number of children nodes
    
};

void ChildrenNumber(TreeNode* node)
{
    // return if both null
    if (node == NULL)
        return;

    ChildrenNumber(node->ChildLeft);
    ChildrenNumber(node->ChildRight);
    
    std::cout << node->GiniGain << '\n';
}

#endif /* DECISIONTREE_HPP */
