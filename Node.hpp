#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

// create an alias for the data structure we are going to use to store observations
using DataFrame = std::vector<std::vector<int>>;

struct bestSplitReturn
{
    float resultantGini;
    int feature;
    int category;
};

// instantiate the node in the heap, then don't need to explicitly allocate member
// variables memory in the heap
class Node
{
    // Access specifier
    public:
        //at some point need to make private and expose using getters and setters
        Node* childLeftP;
        Node* childRightP;
        DataFrame trainingData;
        bestSplitReturn bestSplit; // column index of split feature
        //float giniBefore;


        Node(const DataFrame& data); //constructor

        ~Node();

        Node* DeepCopy() {
            // READ ABOUT DEEP AND SHALLOW COPIES

            // copy stuff
            return this;
        }

        Node* ShallowCopy() {
            // READ ABOUT DEEP AND SHALLOW COPIES

            // copy stuff
            return this;
        }
        static float getGiniImpurity(const std::vector<int>& outcomes);
        static DataFrame getSplitTargets(const DataFrame& dataP, int feature, int category);
        static bestSplitReturn getBestSplit(const DataFrame& dataP); //don't pass by reference
    

};


#endif /* NODE_HPP */
