#include "DecisionTree.hpp"

// construct DataFrame for children following split
// return two dataframes, one with split cat, one without
TwoDataFrame DecisionTree::splitData(const DataFrame& dataBefore, int feature, int category)
{
    std::vector<int> presSplit; // indexes where category present
    std::vector<int> absSplit; // indexes where category absent

    int idx = 0;
    for(int i : dataBefore[feature]) {

        int val = dataBefore[feature][idx];

        if (val == category) {
            // value is category, add index to trueSplit

            presSplit.push_back(idx);
        } else {

            absSplit.push_back(idx);
        };
        idx += 1;
        
    }

    int numRows = dataBefore.size();
    DataFrame presData;
    std::vector<int> rowBuffer;
    for (int row = 0; row < numRows; row++) {
        int i = 0;
        for(int col : presSplit) {

            rowBuffer.push_back(dataBefore[row][col]);
            i += 1;
        }
        presData.push_back(rowBuffer);
        rowBuffer.clear();

    }


    DataFrame absData;
    for (int row = 0; row < numRows; row++) {
        int i = 0;
        for(int col : absSplit) {
            rowBuffer.push_back(dataBefore[row][col]);
            i += 1;
        }
        absData.push_back(rowBuffer);
        rowBuffer.clear();

    }

    TwoDataFrame returnObj;
    returnObj.pres = presData;
    returnObj.abs = absData;
    return returnObj;
}


// recursively add children nodes until stopping condition satisfied
// uncomment printing statements of tree construction
// funcion should alter the node object
void DecisionTree::constructTree(Node* nodeP) {

    const std::vector<int> outputsBefore = (nodeP->trainingData)[(nodeP->trainingData).size() - 1];
    // if resultant gini from best split less than current gini recurse on children
    float giniBefore = Node::getGiniImpurity(outputsBefore);

    if (nodeP->bestSplit.resultantGini < giniBefore) {
        // recurse on children

        TwoDataFrame childrensData = DecisionTree::splitData(nodeP->trainingData, nodeP->bestSplit.feature, nodeP->bestSplit.category);

        // if data present in split data then build a child node
        if (childrensData.pres[0].size() > 0) {

            Node* newRightChild = new Node(childrensData.pres);
            nodeP->childRightP = newRightChild;
            DecisionTree::constructTree(nodeP->childRightP);
        }

        // if data present in split data then build a child node
        if (childrensData.abs[0].size() > 0) {

            Node* newLeftChild = new Node(childrensData.abs);
            nodeP->childLeftP = newLeftChild;
            DecisionTree::constructTree(nodeP->childLeftP);
        }
    
    };
    
}

void DecisionTree::deleteChildren(Node* nodeP) {

    if (nodeP->childRightP != NULL) {
        // delete right child node
        DecisionTree::deleteChildren(nodeP->childRightP);
    }
    if (nodeP->childLeftP != NULL) {
        // at delete left child node
        DecisionTree::deleteChildren(nodeP->childLeftP);
    }
    delete nodeP;
};

// traverse tree with observations until reach leaf and return prediction
int DecisionTree::recursivelyPredict(Node* nodeP, std::vector<int> observations) {
    int obsCat = observations[nodeP->bestSplit.feature];
    //initialize predictClass
    int predictClass = -1;


    if ((nodeP->childLeftP == NULL) && (nodeP->childRightP == NULL)) {
        // leaf node
        // return outcome category of all data

        predictClass = (nodeP->trainingData)[(nodeP->trainingData).size() - 1][0];
        
        
    } else if (obsCat == nodeP->bestSplit.category) {
        // recurse on right child

        predictClass = DecisionTree::recursivelyPredict(nodeP->childRightP, observations);
    } else {
        // recurse on left child

        predictClass = DecisionTree::recursivelyPredict(nodeP->childLeftP, observations);
    }
    return predictClass;

}


std::vector<int> DecisionTree::predict(std::string path) {

    CSVReader reader;
    DataFrame testData = reader.read(path);
    std::vector<int> predictions;
    // iterate through each observation and make predictions
    int numObs = testData[0].size();
    int numFeatures = testData.size();

    for (int obs = 0; obs < numObs; obs++) {

        // build obs vector and make predictions
        std::vector<int> observations;
        for (int feature = 0; feature < numFeatures; feature++) {
            observations.push_back(testData[feature][obs]);
        }

        predictions.push_back(DecisionTree::recursivelyPredict(this->rootP, observations));
        
    }
    
    return predictions;
};



DecisionTree::DecisionTree(std::string trainPath) {
    CSVReader reader;
    DataFrame trainingData = reader.read(trainPath);
    Node* rootP = new Node(trainingData);
    //call construct tree on root
    constructTree(rootP);
    this->rootP = rootP;

};

DecisionTree::~DecisionTree() {
    //will need to explicitly delete all allocated memory (traverse tree and delete nodes)
    DecisionTree::deleteChildren(this->rootP);
};
