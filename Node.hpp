#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

// create an alias for the data structure we are going to use to store observations
using DataFrame = std::vector<std::vector<int>>;


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
        int splitFeature; // column index of split feature
        int splitCategory; // category of split to left child
        float giniImpurity;


        Node(DataFrame* nodeDataP);

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
        static float calcGiniImpurity(DataFrame* dataP, int feature);
        
    

};


#endif /* NODE_HPP */
