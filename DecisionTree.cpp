#include "DecisionTree.hpp"

// construct DataFrame for children following split
// return two dataframes, one with split cat, one without
TwoDataFrame DecisionTree::splitData(const DataFrame& dataBefore, int feature, int category)
{
    std::vector<int> presSplit; // indexes where category present
    std::vector<int> absSplit; // indexes where category absent

    int idx = 0;
    for(int i : dataBefore[feature]) {
        //std::cout  << counts[i] << std::endl;
        int val = dataBefore[feature][idx];
        //std::cout << val;
        if (val == category) {
            // value is category, add index to trueSplit
            //std::cout << "true";
            presSplit.push_back(idx);
        } else {
            //std::cout << "false";
            absSplit.push_back(idx);
        };
        idx += 1;
        
    }
    for (int idx : presSplit) {
        //std::cout << idx << " ";
    }
    //std::cout << "\n\n";

    int numRows = dataBefore.size();
    DataFrame presData;
    std::vector<int> rowBuffer;
    for (int row = 0; row < numRows; row++) {
        int i = 0;
        for(int col : presSplit) {
            //std::cout << dataBefore[row][col] << ' ';
            rowBuffer.push_back(dataBefore[row][col]);
            //std::cout << col << ": ";
            //std::cout << rowBuffer[i] << '\n';
            i += 1;
        }
        presData.push_back(rowBuffer);
        rowBuffer.clear();
        //std::cout << '\n';
    }
    //std::cout << '\n';

    DataFrame absData;
    for (int row = 0; row < numRows; row++) {
        int i = 0;
        for(int col : absSplit) {
            //std::cout << dataBefore[row][col] << ' ';
            rowBuffer.push_back(dataBefore[row][col]);
            //std::cout << col << ": ";
            //std::cout << rowBuffer[i] << '\n';
            i += 1;
        }
        absData.push_back(rowBuffer);
        rowBuffer.clear();
        //std::cout << '\n';
    }

    for (int row = 0; row < presData.size(); row++) {
        for (int col = 0; col < presData[col].size(); col++) {
            //std::cout << presData[row][col] << ' ';
        }
        //std::cout << '\n';
    }
    //std::cout << '\n';

    for (int row = 0; row < absData.size(); row++) {
        for (int col = 0; col < absData[col].size(); col++) {
            //std::cout << absData[row][col] << ' ';
        }
        //std::cout << '\n';
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
    //std::cout << (nodeP->trainingData)[0][0];
    const std::vector<int> outputsBefore = (nodeP->trainingData)[(nodeP->trainingData).size() - 1];
    // if resultant gini from best split less than current gini recurse on children
    float giniBefore = Node::getGiniImpurity(outputsBefore);
    //std::cout << "current state of data obsNumber = " << (nodeP->trainingData)[0].size() << '\n';
    for (int row = 0; row < (nodeP->trainingData).size(); row++) {
        for (int col = 0; col < (nodeP->trainingData)[0].size(); col++) {
            //std::cout << (nodeP->trainingData)[row][col] << ' ';
        }
        //std::cout << '\n';
    }
    //std::cout << "\ncurrent gini on node = " << giniBefore << '\n';
    //std::cout << "current split feature and cat on node = " << nodeP->bestSplit.feature << ", " << nodeP->bestSplit.category << '\n';
    if (nodeP->bestSplit.resultantGini < giniBefore) {
        // recurse on children
        //std::cout << "split improves gini \n";
        TwoDataFrame childrensData = DecisionTree::splitData(nodeP->trainingData, nodeP->bestSplit.feature, nodeP->bestSplit.category);

        // if data present in split data then build a child node
        if (childrensData.pres[0].size() > 0) {
            //std::cout << "\n\nstill data present to pass to right child \n";
            Node* newRightChild = new Node(childrensData.pres);
            nodeP->childRightP = newRightChild;
            DecisionTree::constructTree(nodeP->childRightP);
        }

        // if data present in split data then build a child node
        if (childrensData.abs[0].size() > 0) {
            //std::cout << "\n\nstill data present to pass to left child \n";
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
    //std::cout << "observation feature = " << nodeP->bestSplit.feature << '\n';
    //std::cout << "observation category = " << obsCat << '\n';
    //std::cout << "training data size = " << nodeP->trainingData.size() << '\n';
    //std::cout << "training data below" << '\n';
    for (int row = 0; row < (nodeP->trainingData).size(); row++) {
        for (int col = 0; col < (nodeP->trainingData)[0].size(); col++) {
            //std::cout << (nodeP->trainingData)[row][col] << ' ';
        }
        //std::cout << '\n';
    }
    //std::cout << '\n';
    if ((nodeP->childLeftP == NULL) && (nodeP->childRightP == NULL)) {
        // leaf node
        // return outcome category of all data
        //std::cout << "reached leaf node\n";
        predictClass = (nodeP->trainingData)[(nodeP->trainingData).size() - 1][0];
        
        
    } else if (obsCat == nodeP->bestSplit.category) {
        // recurse on right child
        //std::cout << "recursing on right child\n";
        predictClass = DecisionTree::recursivelyPredict(nodeP->childRightP, observations);
    } else {
        // recurse on left child
        //std::cout << "recursing on left child\n";
        predictClass = DecisionTree::recursivelyPredict(nodeP->childLeftP, observations);
    }
    return predictClass;

}


std::vector<int> DecisionTree::predict(std::string path) {
    //std::cout << "\n\nMaking predictions\n";
    CSVReader reader;
    DataFrame testData = reader.read(path);
    std::vector<int> predictions;
    // iterate through each observation and make predictions
    int numObs = testData[0].size();
    int numFeatures = testData.size();
    //std::cout << "number obs = " << numObs << '\n';
    for (int obs = 0; obs < numObs; obs++) {
        //std::cout << obs << "\n";
        // build obs vector and make predictions
        std::vector<int> observations;
        for (int feature = 0; feature < numFeatures; feature++) {
            observations.push_back(testData[feature][obs]);
        }
        //std::cout << "observations length = " << observations.size() << '\n';
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
