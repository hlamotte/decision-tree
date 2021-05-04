#ifndef DECISIONTREE_HPP
#define DECISIONTREE_HPP

#include "CSVReader.hpp"
#include "TreeNode.hpp"


// instantiate the node in the heap, then don't need to explicitly allocate member
// variables memory in the heap
class DecisionTree
{
    // Access specifier
    public:
        //at some point need to make private and expose using getters and setters
        TreeNode* rootNodeP;
        obsArray trainingData;

        DecisionTree(char* trainPath, char* testPath);

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
};


#endif /* DECISIONTREE_HPP */
