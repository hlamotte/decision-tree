#include "DecisionTree.hpp"
#include "CSVReader.hpp"
#include "TreeNode.hpp"

DecisionTree::DecisionTree(char* trainPath, char* testPath)
{
    CSVReader reader;
    TreeNode* rootP;
    this->trainingData = reader.read(trainPath);
    this->rootNodeP = rootP;


}

    
}

}