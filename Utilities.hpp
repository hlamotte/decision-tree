#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>



// sum of the elements of an integer array
inline int SumIntArray(int ElementNum, int* Array) {
    int sum = 0;
    for (int i = 0; i < ElementNum; i++) {
        sum += Array[i];
    }
    return sum;
}

#endif /* UTILITIES_HPP */
