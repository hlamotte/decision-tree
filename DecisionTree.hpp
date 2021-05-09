#ifndef DECISIONTREE_HPP
#define DECISIONTREE_HPP

#include "CSVReader.hpp"
#include "Node.hpp"


struct TwoDataFrame
{
    DataFrame pres;
    DataFrame abs;
};

// instantiate the node in the heap, then don't need to explicitly allocate member
// variables memory in the heap
class DecisionTree
{
    // Access specifier
    public:
        //at some point need to make private and expose using getters and setters
        Node* rootP;
        //DataFrame trainingData;

        DecisionTree(std::string trainPath);

        ~DecisionTree();

        DecisionTree* DeepCopy() {
            // READ ABOUT DEEP AND SHALLOW COPIES

            // copy stuff
            return this;
        }

        DecisionTree* ShallowCopy() {
            // READ ABOUT DEEP AND SHALLOW COPIES

            // copy stuff
            return this;
        }
        
    
        // Traverse tree
        void traverseTree() const;
        static TwoDataFrame splitData(const DataFrame& dataBefore, int feature, int category);
        static void constructTree(Node* nodeP);
        std::vector<int> predict(std::string path);
        void deleteChildren(Node* nodeP);
        static int recursivelyPredict(Node* nodeP, std::vector<int> observations);
};


#endif /* DECISIONTREE_HPP */
