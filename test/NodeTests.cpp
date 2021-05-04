#include <gtest/gtest.h>
#include "../Node.hpp"


TEST(DecisionTreeTests, Node) {
    DataFrame testData{
        {0, 1, 1, 1, 0}, //feature0
        {1, 0, 0, 1, 0}, //feature1
        {1, 1, 1, 1, 1}, //feature2
        {1, 1, 2, 0, 1}, //feature3
        {0, 1, 2, 3, 4}, //target
        {0, 0, 0, 0, 0}, //target
    };
    //gini impurity calculation tests
    //Node testNode(&testData);
    //std::cout << (testData[0]).size();

    // test Gini Impurity calculation
    EXPECT_NEAR(Node::calcGiniImpurity(&testData, 0), 0.48, 0.001);
    EXPECT_NEAR(Node::calcGiniImpurity(&testData, 1), 0.48, 0.001);
    EXPECT_NEAR(Node::calcGiniImpurity(&testData, 2), 0, 0.001);
    EXPECT_NEAR(Node::calcGiniImpurity(&testData, 3), 0.56, 0.001);
    EXPECT_NEAR(Node::calcGiniImpurity(&testData, 4), 0.8, 0.001);
    EXPECT_NEAR(Node::calcGiniImpurity(&testData, 5), 0, 0.001);
    
    //std::cout << testData[2][2];
    
    
    
    /*
    // Instantiate a Node
    Node head;
    head.splitFeature = 1;
    head.splitCategory = 0;
    head.giniGain = 0.3;

    Node leftChild;
    leftChild.splitFeature = 1;
    leftChild.splitCategory = 0;
    leftChild.giniGain = 0.2;
    head.childLeftP = &leftChild;

    Node rightChild;
    rightChild.splitFeature = 1;
    rightChild.splitCategory = 0;
    rightChild.giniGain = 0.1;
    head.childRightP = &rightChild;

    Node rightChildRightChild;
    rightChildRightChild.splitFeature = 1;
    rightChildRightChild.splitCategory = 0;
    rightChildRightChild.giniGain = 0.1;
    rightChild.childRightP = &rightChildRightChild;

    ////std::cout << Head.SplitFeature;
    head.traverseTree();
    */
    //EXPECT_EQ(1, 2);
    
    
}