#include "CSVReader.hpp"



obsArray CSVReader::read(char* filePath) {

    std::string line;                    /* string to hold each line */
    obsArray array;      /* vector of vector<int> for 2d array */

    //if (argc < 2) { /* validate at least 1 argument given */
    //    cerr << "error: insufficient input.\n"
    //            "usage: " << argv[0] << " filename\n";
    //    return 1;
    //}

    std::ifstream f (filePath);   /* open file */

    try {
        if (!f.is_open()) {     /* validate file open for reading */
            throw (filePath);
        };
    } catch (char* filePath) {
        std::cout << (("error while opening file " + std::string(filePath)).c_str());
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

    std::cout << "complete array\n\n";
    for (auto& row : array) {           /* iterate over rows */
        for (auto& val : row)           /* iterate over vals */
            std::cout << val << "  ";        /* output value      */
        std::cout << "\n";                   /* tidy up with '\n' */
    }
    return array;
}
