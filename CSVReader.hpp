#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Node.hpp"

class CSVReader
{
    // Access specifier
    public:

    DataFrame read(std::string filePath);
};

#endif /* CSVREADER_HPP */
