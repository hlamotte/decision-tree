#include "../DecisionTree.hpp"

#include <gtest/gtest.h>

TEST(DecisionTreeTests, TreeNode) {
    // Instantiate a TreeNode
    TreeNode Head;
    Head.SplitFeature = 1;
    Head.SplitCategory = 0;
    Head.GiniGain = 0.3;

    TreeNode LeftChild;
    LeftChild.SplitFeature = 1;
    LeftChild.SplitCategory = 0;
    LeftChild.GiniGain = 0.2;
    Head.ChildLeft = &LeftChild;

    TreeNode RightChild;
    RightChild.SplitFeature = 1;
    RightChild.SplitCategory = 0;
    RightChild.GiniGain = 0.1;
    Head.ChildRight = &RightChild;

    //std::cout << Head.SplitFeature;
    ChildrenNumber(&Head);
    EXPECT_EQ(1, 2);
    
    
}