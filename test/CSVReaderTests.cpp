#include "../CSVReader.hpp"

#include <gtest/gtest.h>

TEST(CSVReader, BasicFile) {
    CSVReader reader;
    //TODO: get exception test working
    // can't get exception test working
    /*
    // test fails with invalid path
    reader.read(std::string("../../test/resources/nonsense.csv"));
    try {
        //char nonsense[] = "nonsense";
        reader.read(std::string("../../test/resources/nonsense.csv"));
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        std::cout << err.what();
        EXPECT_EQ(err.what(),std::string("error while opening file nonsense"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument later catch";
    }
    */


    //char testPath[] = ;
    DataFrame test = reader.read("../../test/resources/test.csv");
    EXPECT_EQ(test.size(), 3);
    EXPECT_EQ(test[0].size(), 5);
    EXPECT_EQ(test[0][4], 1);

    DataFrame train = reader.read("../../test/resources/train.csv");
    EXPECT_EQ(train.size(), 4);
    EXPECT_EQ(train[0].size(), 5);
    EXPECT_EQ(train[2][2], 2);

}