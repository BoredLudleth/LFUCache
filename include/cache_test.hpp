#pragma once

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include <filesystem>

std::string runBinary(const std::string& binaryPath, const std::string& input);

TEST(BinaryTestPerfect, KnownInput) {
    EXPECT_EQ(runBinary("./perfect", "test/002.dat"), "7\n");
    EXPECT_EQ(runBinary("./perfect", "test/004.dat"), "18\n");
    EXPECT_EQ(runBinary("./perfect", "test/006.dat"), "327\n");
    EXPECT_EQ(runBinary("./perfect", "test/011.dat"), "89999\n");
}

TEST(BinaryTestLFU, KnownInput) {
    EXPECT_EQ(runBinary("./lfu", "test/002.dat"), "6\n");
    EXPECT_EQ(runBinary("./lfu", "test/004.dat"), "13\n");
    EXPECT_EQ(runBinary("./lfu", "test/006.dat"), "179\n");
    EXPECT_EQ(runBinary("./lfu", "test/011.dat"), "89999\n");
}
