#include <gtest/gtest.h>
#include "../Node.hpp"


TEST(DecisionTreeTests, Node) {
    DataFrame testData{
        {0, 1, 1, 1, 0}, //feature0
        {1, 0, 0, 1, 0}, //feature1
        {0, 0, 0, 0, 0}, //feature2
        {1, 1, 2, 0, 1}, //feature3
        {0, 1, 2, 3, 4}, //feature4
        {0, 0, 0, 0, 0}, //feature5
        {0, 1, 1, 1, 0} //target
    };
    //gini impurity calculation tests
    //Node testNode(&testData);
    //std::cout << (testData[0]).size();

    // test Gini Impurity calculation
    EXPECT_NEAR(Node::getGiniImpurity(testData[1]), 0.48, 0.001);
    EXPECT_NEAR(Node::getGiniImpurity(testData[0]), 0.48, 0.001);
    EXPECT_NEAR(Node::getGiniImpurity(testData[2]), 0, 0.001);
    EXPECT_NEAR(Node::getGiniImpurity(testData[3]), 0.56, 0.001);
    EXPECT_NEAR(Node::getGiniImpurity(testData[4]), 0.8, 0.001);
    EXPECT_NEAR(Node::getGiniImpurity(testData[5]), 0, 0.001);
    EXPECT_NEAR(Node::getGiniImpurity(testData[6]), 0.48, 0.001);
    
    //test split
    // feature4
    
    EXPECT_EQ(Node::getSplitTargets(testData, 4, 1)[0][0],1);
    EXPECT_EQ(Node::getSplitTargets(testData, 4, 1)[1][0],0);
    EXPECT_EQ(Node::getSplitTargets(testData, 4, 1)[1][1],1);
    EXPECT_EQ(Node::getSplitTargets(testData, 4, 1)[1][2],1);
    EXPECT_EQ(Node::getSplitTargets(testData, 4, 1)[1][3],0);
    

    //feature1
    EXPECT_EQ(Node::getSplitTargets(testData, 1, 0)[1].size(), 2);
    EXPECT_EQ(Node::getSplitTargets(testData, 1, 0)[0][0],1);
    EXPECT_EQ(Node::getSplitTargets(testData, 1, 1)[0][1],1);
    
    // test best feature
    bestSplitReturn bestChoice = Node::getBestSplit(testData);
    EXPECT_EQ(bestChoice.resultantGini, 0);
    EXPECT_EQ(bestChoice.feature, 0);
    EXPECT_EQ(bestChoice.category, 0);

    DataFrame testData2{ //feature0
    {0, 1, 1, 1, 1}, //feature2
    {0, 1, 1, 2, 0},
    {0, 1, 2, 3, 4},
    {0, 0, 1, 0, 0} //target
    };
    bestSplitReturn bestChoice2 = Node::getBestSplit(testData2);
    EXPECT_EQ(bestChoice2.resultantGini, 0);
    EXPECT_EQ(bestChoice2.feature, 2);
    EXPECT_EQ(bestChoice2.category, 2);
    
    Node testNode = Node(testData);
    EXPECT_EQ(testNode.bestSplit.resultantGini, 0);
    EXPECT_EQ(testNode.bestSplit.feature, 0);
    EXPECT_EQ(testNode.bestSplit.category, 0);

    Node testNode2 = Node(testData2);
    EXPECT_EQ(testNode2.bestSplit.resultantGini, 0);
    EXPECT_EQ(testNode2.bestSplit.feature, 2);
    EXPECT_EQ(testNode2.bestSplit.category, 2);
    //EXPECT_EQ(1, 2);
    //EXPECT_EQ(Node::bestFeature(&testData), 0.48);

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