#include <stdexcept>

#include "CSVReader.hpp"

DataFrame CSVReader::read(std::string filePath) {

    std::string line;                    /* string to hold each line */
    DataFrame array;      /* vector of vector<int> for 2d array */

    std::ifstream f (filePath);   /* open file */

    try {
        if (!f.is_open()) {     /* validate file open for reading */
            throw (filePath);
        };
    } catch (char* filePath) {
        throw std::invalid_argument(("error while opening file " + std::string(filePath)).c_str());
    }

    while (getline (f, line)) {         /* read each line */
        std::string val;                     /* string to hold value */
        std::vector<int> row;                /* vector for row of values */
        std::stringstream s (line);          /* stringstream to parse csv */
        while (getline (s, val, ','))   /* for each value */
            row.push_back (stoi(val));  /* convert to int, add to row */
        array.push_back (row);          /* add row to array */
    }
    f.close();
    return array;
}
