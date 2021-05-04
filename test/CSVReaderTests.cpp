#include "../CSVReader.hpp"

#include <gtest/gtest.h>

TEST(CSVReader, BasicFile) {
    CSVReader reader;
    char filePath[] = "../../test/resources/test.csv";
    reader.read(filePath);
    EXPECT_EQ(1, 2);

}