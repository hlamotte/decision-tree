#include "../DecisionTree.hpp"

#include <gtest/gtest.h>

TEST(DecisionTreeTests, DecisionTree) {
    //EXPECT_EQ(Add(1, 2), 3);
    

    DataFrame testData{
        {0, 1, 1, 1, 0}, //feature0
        {1, 0, 0, 1, 0}, //feature1
        {0, 0, 0, 0, 0}, //feature2
        {1, 1, 2, 0, 1}, //feature3
        {0, 1, 2, 3, 4}, //feature4
        {0, 0, 0, 0, 0}, //feature5
        {0, 1, 1, 1, 0} //target
    };

    
    //test split tests
    TwoDataFrame testSplit = DecisionTree::splitData(testData, 3, 1);
    EXPECT_EQ(testSplit.pres.size(), 7);
    EXPECT_EQ(testSplit.pres[0].size(), 3);
    EXPECT_EQ(testSplit.pres[4][2], 4);

    EXPECT_EQ(testSplit.abs.size(), 7);
    EXPECT_EQ(testSplit.abs[0].size(), 2);
    EXPECT_EQ(testSplit.abs[4][1], 3);

    
    TwoDataFrame testSplit2 = DecisionTree::splitData(testData, 1, 0);
    EXPECT_EQ(testSplit2.pres.size(), 7);
    EXPECT_EQ(testSplit2.pres[0].size(), 3);
    EXPECT_EQ(testSplit2.abs[0].size(), 2);
    //EXPECT_EQ(testSplit.pres[4][2], 4);

    //try a split when there is only one category
    TwoDataFrame testSplit3 = DecisionTree::splitData(testData, 2, 0);
    EXPECT_EQ(testSplit3.pres[0].size(), 5);
    EXPECT_EQ(testSplit3.abs[0].size(), 0);

    DecisionTree* testTreeP = new DecisionTree("../../test/resources/train.csv");

    std::vector<int> testObs{0, 2, 0};
    int prediction = DecisionTree::recursivelyPredict(testTreeP->rootP, testObs);
    EXPECT_EQ(prediction, 0);

    //out of dataset prediction
    std::vector<int> testObs1{0, 2, 1};
    int prediction1 = DecisionTree::recursivelyPredict(testTreeP->rootP, testObs1);
    
    
    std::vector<int> testPredictions = testTreeP->predict("../../test/resources/test.csv");
    EXPECT_EQ(testPredictions[0], 0);
    EXPECT_EQ(testPredictions[1], 2);
    EXPECT_EQ(testPredictions[2], 2);
    //std::cout << "\nNumber of children = " << DecisionTree::getNumberChildren(testTreeP->rootP);

    delete testTreeP; // delete from heap

    DecisionTree* bigTreeP = new DecisionTree("../../test/resources/bigTrain.csv");

    std::vector<int> bigPredictions = testTreeP->predict("../../test/resources/bigTest.csv");
    EXPECT_EQ(bigPredictions[1], 1);
    //stack overflow?

    delete bigTreeP;
    //EXPECT_EQ(testTree.rootP->bestSplit.feature, 1);
    //std::cout << testTree.rootP->trainingData[0][0];
    //another comment


    //EXPECT_EQ(1, 2);

}