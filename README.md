# Decision tree in C++
## How to compile and run tests locally
Ensure you have CMake installed.

Install CMake on MacOS:
```
$ brew install cmake
$ cmake --version
```

This project has been successfully compiled using clang++ compiler on MacOS (AppleClang 11.0.3). Ensure you have Clang installed.

Compiling project:
```
$ mkdir build
$ /usr/local/bin/cmake -S . -B ./build/ -D CMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_VERBOSE_MAKEFILE=ON
$ cd build && make
```
For running tests after successful compilation:
```bash
$ cd test && ./DecisionTests && cd ../..
```
## Using this decision tree classifier
An example jupyter notebook calling this classifier training on the Titanic dataset can be found [here](notebooks/titanic_predictions.ipynb).

As can be seen in the notebook, the classifier implemented here does not produce identical results to the scikit-learn Decision Tree Classifier, but we see 85% accurate results on a test data set compared with the sci-kit learn implementation.


## Overview of this implementation of a decision tree classifier
Decision trees are a simple machine learning algorithm that use a series of features of an observation to create a prediction of a target outcome class.

For example, the target outcome class could be whether a company should interview a candidate for a job, and the series of features could be:

1. The university they attended
2. The subject they studied at university
3. Their highest degree qualification
4. Their previous employer
5. Their previous job title

The decision tree is built ("trained") using a series of observations (training data) with their corresponding outcome class to create a tree that best fits the training data. This tree can then be used to make predictions on a series of observations without knowing the target outcome class.

For the interview screening tool outlined the training data might look like:

| PersonID | University | UniSubject | Degree | PrevEmployer   | PrevTitle      | Interviewed |
|----------|------------|------------|--------|----------------|----------------|-------------|
| 1        | Harvard    | Math       | MSc    | Google         | Data Scientist | Yes         |
| 2        | Stanford   | Math       | MSc    | Microsoft      | Data Analyst   | Yes         |
| 3        | Cornell    | English    | MA     | New York Times | Reporter       | No          |

Where the outcome class used for training is whether the candidate was interviewed or not.

In this repo basic categorical-only decision tree classifier algorithm is implemented in C++ as an exercise to learn a low-level language.

## Training a decision tree classifier
- Have a number of measurements of categorical feature vectors and a corresponding outcome class.
- For each feature calculate the [Gini Gain](https://victorzhou.com/blog/gini-impurity/).
- Select the feature to split on that maximizes the Gini gain.
- Split the data based on that feature to create two new sub-trees.
- Repeat splitting of nodes in each sub-tree until only one outcome class predicted after splitting (gini gain = 0).

## Inputs and outputs
### Inputs
To simplify the problem to the core business logic of a categorical decision tree classifier, we will assume that __all categories are encoded as integers__ then input to the decision tree as a train csv and a test csv. The __header (feature names) will be omitted from the input__ and each *row* will contain all the observations for a feature, a column will represent one individual observation. Note this is rotated 90 degrees from a traditional csv representation.

Assume training data features contain at least one instance of every class that can exist and that classes are indexed from zero.

The last row will be assumed to be the outcomes/target variable in the training dataset. There will be one less row in the test dataset as the outcome would be unknown.


## Required data structures
### Training and test data structure

An array of pointers for all features these pointers point to arrays with the value of that feature for each training or test observation. 

An array of outcome classes for each training and test observation.

### Decision tree architecture structure
Tree architecture.

Each node has following attributes:
1. ChildLeft - pointer to left child node
2. ChildRight - pointer to right child node
3. SplitFeature - feature used at split
4. SplitCategory - category of that feature used at split. Observations containing that category are passed to the right child tree. If leaf, predicted class.
5. GiniGain - gain as a result of split.

## UML
*Tree class*
- Tree()
- ~Tree()
- Node* head
- Traverse()
- Fit()
- Transform()
- CSVReader

Stretch nice to haves:
- Load()
- Save()
- Look into Hdf5 format for saving

*Node class*
- Node()
- ~Node()
- Node* children
- DataFrame data
- int splitFeature
- int splitCategory
- float giniImpurity


## Gini gain
Gini impurity is the probability of incorrectly classifying a randomly chosen element in the dataset if it were randomly labeled *according to the class distribution* in the dataset.

Gini gain is calculated as the original gini impurity of the dataset minus the weighted resultant gini impurities as a result of the split.

We choose the branch that maximises the Gini gain.

## Development using VSCode
Using CMake and GoogleTest framework in VSCode based on this [video](https://www.youtube.com/watch?v=Lp1ifh9TuFI).

Build the binaries with F7. Run tests from the ribbon at the bottom of the VSCode UI.
