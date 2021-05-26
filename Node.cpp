#include "Node.hpp"

#include <iostream>
#include <typeinfo>

// calculate Gini impurity of a vector of outcomes
float Node::getGiniImpurity(const std::vector<int>& outcomes) {
    // gini impurity is only calculated for the target class

    if (outcomes.size() == 0) {  
        return 0.0;
    }

    float giniSum = 0.0;

    // for each class work out the count
    // store count for each class in a vector
    // initialize vector with length equal to number of classes with all counts equal to zero

    const int max =  *std::max_element(outcomes.begin(), outcomes.end());

    // initialize length as number of classes
    int counts[max + 1];
    std::memset(counts, 0, sizeof(counts));

    // count instances of each class in counts array
    for(int i : outcomes) {
        counts[i] += 1;     
    }

    for(int j = 0; j <= max; j++) {
        
        float pClass = (float)counts[j] / (float)outcomes.size();
        giniSum += pClass * (1 - pClass);

    }
    //std::cout << giniSum;
    return giniSum;
};

// split targets based on feature and category then return resultant split of outcomes
// returns a DataFrame with the first row containing target categories where feature
// category, second row contains target categories where feature category was absent
DataFrame Node::getSplitTargets(const DataFrame& dataP, int feature, int category) {
    std::vector<int> trueSplit; // indexes where category present
    std::vector<int> falseSplit; // indexes where absent present

    int idx = 0;
    for(int i : dataP[feature]) {

        int val = dataP[feature][idx];

        if (val == category) {
            // value is category, add index to trueSplit

            trueSplit.push_back(idx);
        } else {
            //std::cout << "false";
            falseSplit.push_back(idx);
        };
        idx += 1;
        
    }
    // replace inplace indexes with values of associated outcomes
    std::vector<int> allOutcomes = dataP[dataP.size() - 1];

    std::vector<int> trueOutcomes; // indexes where category present
    std::vector<int> falseOutcomes; // indexes where absent present


    for (auto& it : falseSplit) {
        falseOutcomes.push_back(allOutcomes[it]);
    }

    for (auto& it : trueSplit) {
        trueOutcomes.push_back(allOutcomes[it]);
    }

    DataFrame returnData{
        trueOutcomes, 
        falseOutcomes};
    return returnData;
};

// return the best feature and category to split on and the resultant Gini
bestSplitReturn Node::getBestSplit(const DataFrame& dataP) {
    // giniImpurity before split
    const std::vector<int> outputsBefore = dataP[dataP.size() - 1];
    const float giniBefore = Node::getGiniImpurity(outputsBefore);
    // get number of features
    int features = dataP.size() - 1;
    bestSplitReturn bestChoice; // resultant GiniImpurity, feature
    bestChoice.resultantGini = giniBefore;
    bestChoice.feature = 0;
    bestChoice.category = 0;
    for (int feature = 0; feature < features; feature++) {
        // get number of categories in that feature
        std::vector<int> featureVec = dataP[feature];
        int cats = *max_element(featureVec.begin(), featureVec.end()) + 1;
        //std::cout << cats << "\n";
        // calculate Gini Impurity for splitting every feature by every category
        for (int cat = 0; cat < cats; cat++) {

            DataFrame split = Node::getSplitTargets(dataP, feature, cat);
            float trueGini = Node::getGiniImpurity(split[0]);
            float weightedTrueGini = trueGini * split[0].size() / outputsBefore.size();
            float falseGini = Node::getGiniImpurity(split[1]);

            float weightedFalseGini = falseGini * split[1].size() / outputsBefore.size();

            float weightedGiniSum = weightedTrueGini + weightedFalseGini;

            if(weightedGiniSum < bestChoice.resultantGini) {
                //splitting here improves on current gini impurity
                bestChoice.resultantGini = weightedGiniSum;
                bestChoice.feature = feature;
                bestChoice.category = cat;
            }
        }
    }

    return bestChoice;
}

Node::Node(const DataFrame& data) {
    // constructor

    // initialize pointers to children as null
    this->childLeftP = NULL;
    this->childRightP = NULL;
    const std::vector<int> outputsBefore = data[data.size() - 1];
    this->trainingData = data;


    // calculate best feature to split on
    this->bestSplit = Node::getBestSplit(data);

}

Node::~Node() {

}

