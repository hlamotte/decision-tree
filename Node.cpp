#include "Node.hpp"

#include <iostream>
#include <typeinfo>

// sum of the elements of an integer array
inline int sumIntArray(int ElementNum, int* Array) {
    int sum = 0;
    for (int i = 0; i < ElementNum; i++) {
        sum += Array[i];
    }
    return sum;
};

// for a feature calculate the gini impurity
// NEED TO MAKE CONST
// calculate gini impurity on an obsArray, current interface does not make sense
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

float Node::calcGiniImpurity(DataFrame* dataP, int feature) {
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

Node::Node(DataFrame* nodeDataP) {
    // constructor

    std::cout << "Created tree node" << '\n';

    // define pointers to children as null
    childLeftP = NULL;
    childRightP = NULL;

    // calculate best feature to split on based on node
    // calculate Gini impurity for each feature
    this->calcGiniImpurity(nodeDataP, 0);
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
