#include "Node.hpp"

#include <iostream>
#include <typeinfo>

// sum of the elements of an integer array
/*
inline int sumIntArray(int ElementNum, int* Array) {
    int sum = 0;
    for (int i = 0; i < ElementNum; i++) {
        sum += Array[i];
    }
    return sum;
};
*/

// for a feature calculate the gini impurity
// NEED TO MAKE CONST
// calculate gini impurity on an obsArray, current interface does not make sense
/*
float giniImpurityOld(const int& NumberTargetCats, int* NumberEachCat) {
    int TotalSamples = sumIntArray(NumberTargetCats, NumberEachCat);
    float GiniSum = 0.0;
    for (int i = 0; i < NumberTargetCats; i++) {
        //std::cout <<  NumberEachCat[i] << '\n';
        //std::cout <<  TotalSamples << '\n';
        //std::cout <<  (float)NumberEachCat[i] / (float)TotalSamples << '\n';
        float PClass = (float)NumberEachCat[i] / (float)TotalSamples;
        GiniSum += PClass * (1 - PClass);
    }
    return GiniSum;
};
*/
/*
// calculate Gini impurity for a feature
float Node::calcGiniImpurity(DataFrame* dataP, int feature) {
    // gini impurity is only calculated for the target class
    //int numElems = dataP[feature].size();
    float giniSum = 0.0;
    //new std::vector<int> featureV = dataP[feature];
    // for each class work out the count
    // store count for each class in a vector
    // initialize vector with length equal to number of classes with all counts equal to zero
    
    // iterate through feature vector
    //std::cout << (*dataP)[feature][0];
    int max =  *max_element((*dataP)[feature].begin(), (*dataP)[feature].end());
    //std::cout << "max = "<< max;
    // initialize length as number of classes
    int counts[max + 1];
    std::memset(counts, 0, sizeof(counts));

    // count instances of each class in counts array
    for(int i : (*dataP)[feature]) {
        //std::cout  << counts[i] << std::endl;
        counts[i] += 1;
        
    }

    for(int j = 0; j <= max; j++) {
        //std::cout << "size = " << (float)(*dataP)[feature].size() << std::endl;
        //std::cout << (float)counts[j] << std::endl;
        float pClass = (float)counts[j] / (float)(*dataP)[feature].size();
        //std::cout << pClass << std::endl;
        giniSum += pClass * (1 - pClass);
        //std::cout << "j = " << j << " " << counts[j] << "\n";
    }
    //std::cout << giniSum;
    return giniSum;
};
*/

// calculate Gini impurity of a vector of outcomes
float Node::getGiniImpurity(const std::vector<int>& outcomes) {
    // gini impurity is only calculated for the target class
    //int numElems = dataP[feature].size();
    if (outcomes.size() == 0) {  
        //std::cout << "size zero";
        return 0.0;
    }
    
    float giniSum = 0.0;
    //new std::vector<int> featureV = dataP[feature];
    // for each class work out the count
    // store count for each class in a vector
    // initialize vector with length equal to number of classes with all counts equal to zero
    
    // iterate through feature vector
    //std::cout << (*dataP)[feature][0];
    const int max =  *max_element(outcomes.begin(), outcomes.end());
    //std::cout << "max = "<< max;
    // initialize length as number of classes
    int counts[max + 1];
    std::memset(counts, 0, sizeof(counts));

    // count instances of each class in counts array
    for(int i : outcomes) {
        //std::cout  << counts[i] << std::endl;
        counts[i] += 1;
        
    }

    for(int j = 0; j <= max; j++) {
        //std::cout << "size = " << (float)(*dataP)[feature].size() << std::endl;
        //std::cout << (float)counts[j] << std::endl;
        
        float pClass = (float)counts[j] / (float)outcomes.size();
        //std::cout << pClass << std::endl;
        giniSum += pClass * (1 - pClass);
        //std::cout << "j = " << j << " " << counts[j] << "\n";
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
        //std::cout  << counts[i] << std::endl;
        int val = dataP[feature][idx];
        //std::cout << val;
        if (val == category) {
            // value is category, add index to trueSplit
            //std::cout << "true";
            trueSplit.push_back(idx);
        } else {
            //std::cout << "false";
            falseSplit.push_back(idx);
        };
        idx += 1;
        
    }
    // replace inplace indexes with values of associated outcomes
    std::vector<int> allOutcomes = dataP[dataP.size() - 1];
    //for (auto& it : allOutcomes) {
        //std::cout << allOutcomes[it] << ' ';
        //trueSplit[idx] = allOutcomes[it];
        //idx += 1;
        //std::cout << it << " ";
    //}

    std::vector<int> trueOutcomes; // indexes where category present
    std::vector<int> falseOutcomes; // indexes where absent present
    //int idx = 0;
    //std::cout << "false indexes: ";
    for (auto& it : falseSplit) {
        //std::cout << it << ' ';
        //falseSplit[idx] = allOutcomes[it];
        falseOutcomes.push_back(allOutcomes[it]);
        //idx += 1;
    }
    //idx = 0;
    //std::cout << "true indexes: ";
    for (auto& it : trueSplit) {
        //std::cout << it << ' ';
        //trueSplit[idx] = allOutcomes[it];
        //idx += 1;
        trueOutcomes.push_back(allOutcomes[it]);
    }
    //std::cout << '\n';
    //for(int val : trueSplit) {
        //std::cout << val << ' ';
    //    std::cout << trueSplit[i] << std::endl;
    //}
    //std::cout << allOutcomes[1];
    DataFrame returnData{
        trueOutcomes, //feature0
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
            //std::cout << "feature = " << feature << "\n";
            //std::cout << "category = " << cat << "\n";
            DataFrame split = Node::getSplitTargets(dataP, feature, cat);
            //std::cout << "truecount = " << split[0].size() << "\n";
            //std::cout << "trueVals = ";
            for(int val:split[0]){
                //std::cout << val << " ";
            }
            //std::cout << '\n';
            //if (split[0].size() != 0) {
            float trueGini = Node::getGiniImpurity(split[0]);
            //std::cout << "trueGini = " << trueGini << "\n";
            float weightedTrueGini = trueGini * split[0].size() / outputsBefore.size();
            //std::cout << "weightedTrueGini = " << weightedTrueGini << "\n";
            //}
            
            //std::cout << "falsecount = " << split[1].size() << "\n";
            //std::cout << "falseVals = ";
            for(int val:split[1]){
                //std::cout << val << " ";
            }
            //std::cout << '\n';
            float falseGini = Node::getGiniImpurity(split[1]);
            //std::cout << "falseGini = " << falseGini << "\n";
            float weightedFalseGini = falseGini * split[1].size() / outputsBefore.size();
            //std::cout << "weightedFalseGini = " << weightedFalseGini << "\n";
            float weightedGiniSum = weightedTrueGini + weightedFalseGini;
            //std::cout << "giniBefore = " << giniBefore << "\n";
            //std::cout << "weightedGiniSum = " << weightedGiniSum << "\n";
            
            if(weightedGiniSum < bestChoice.resultantGini) {
                //splitting here improves on current gini impurity
                //std::cout << "less than previous best gini \n";
                bestChoice.resultantGini = weightedGiniSum;
                bestChoice.feature = feature;
                bestChoice.category = cat;
            }
            //std::cout << '\n';
        }
    }
    //std::cout << bestChoice.resultantGini;
    //std::cout << bestChoice.feature;
    //std::cout << bestChoice.category;
    return bestChoice;
}

Node::Node(const DataFrame& data) {
    // constructor

    //std::cout << "Created tree node" << '\n';

    // initialize pointers to children as null
    this->childLeftP = NULL;
    this->childRightP = NULL;

    // calculate best feature to split on
    this->bestSplit = Node::getBestSplit(data);

    //this->calcGiniImpurity(nodeDataP, 0);
}

Node::~Node() {

}

/*
void Node::traverseTree() const {
    // return if both children are null
    if (this->childLeftP != NULL) {
        this->childLeftP->traverseTree();
    }

    if (this->childRightP != NULL) {
        this->childRightP->traverseTree();
    }

    std::cout << this->giniGain << '\n';
}
*/
