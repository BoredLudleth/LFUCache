#pragma once

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include <filesystem>

std::string runBinary(const std::string& binaryPath, const std::string& input);

TEST(BinaryTestPerfect, KnownInput) {
    std::filesystem::path cur_path = std::filesystem::current_path().relative_path();

    std::string exe;
    std::string test;

    if (cur_path.filename() == "build") {
        exe = "./perfect";
        test = "../test/";
    } else {
        exe = "./build/perfect";
        test = "test/";
    }
    EXPECT_EQ(runBinary(exe, test + "002.dat"), "7\n");
    EXPECT_EQ(runBinary(exe, test + "004.dat"), "18\n");
    EXPECT_EQ(runBinary(exe, test + "006.dat"), "327\n");
    EXPECT_EQ(runBinary(exe, test + "011.dat"), "89999\n");
}

TEST(BinaryTestLFU, KnownInput) {
    std::filesystem::path cur_path = std::filesystem::current_path().relative_path();

    std::string exe;
    std::string test;

    if (cur_path.filename() == "build") {
        exe = "./lfu";
        test = "../test/";
    } else {
        exe = "./build/lfu";
        test = "test/";
    }
    EXPECT_EQ(runBinary(exe, test + "002.dat"), "6\n");
    EXPECT_EQ(runBinary(exe, test + "004.dat"), "13\n");
    EXPECT_EQ(runBinary(exe, test + "006.dat"), "179\n");
    EXPECT_EQ(runBinary(exe, test + "011.dat"), "89999\n");
}
