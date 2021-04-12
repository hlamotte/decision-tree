#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include <iostream>
#include "Utilities.hpp"


inline int Add(int a, int b) {
    return a + b;
}



// for a feature calculate the gini impurity
inline float GiniImpurity(int NumberTargetCats, int* NumberEachCat) {
    int TotalSamples = SumIntArray(NumberTargetCats, NumberEachCat);
    float GiniSum = 0.0;
    for (int i = 0; i < NumberTargetCats; i++) {
        //std::cout <<  NumberEachCat[i] << '\n';
        //std::cout <<  TotalSamples << '\n';
        //std::cout <<  (float)NumberEachCat[i] / (float)TotalSamples << '\n';
        float PClass = (float)NumberEachCat[i] / (float)TotalSamples;
        GiniSum += PClass * (1 - PClass);
    }
    return GiniSum;
}

#endif /* EXAMPLE_HPP */
