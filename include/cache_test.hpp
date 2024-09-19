#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

std::string runBinary(const std::string& binaryPath, const std::string& input) {
    std::string command = binaryPath + " < " + input;
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    char buffer[128];

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

TEST(BinaryTestPerfect, KnownInput) {
    EXPECT_EQ(runBinary("./perfect", "../test/002.dat"), "7\n");
    EXPECT_EQ(runBinary("./perfect", "../test/004.dat"), "18\n");
    EXPECT_EQ(runBinary("./perfect", "../test/011.dat"), "89999\n");
}

TEST(BinaryTestLFU, KnownInput) {
    EXPECT_EQ(runBinary("./lfu", "../test/002.dat"), "6\n");
    EXPECT_EQ(runBinary("./lfu", "../test/004.dat"), "13\n");
    EXPECT_EQ(runBinary("./lfu", "../test/011.dat"), "89999\n");
}