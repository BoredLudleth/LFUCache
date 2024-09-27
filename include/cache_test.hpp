#pragma once

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "lfu_cache.hpp"
#include "perfect_cache.hpp"

extern int slow_get_page(int key);

TEST(TestPerfectLookUp, CacheTest) {
    size_t sz = 4;
    size_t input_length = 12;
    std::vector<int> input{1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4}; 

    PerfectCache<int> cache(sz, input_length, input);

    std::vector<bool> answers{0,0,0,0,1,1,0,1,1,1,1,1};
    for (int i = 0; i < input_length; ++i) {
        EXPECT_EQ(cache.lookup_update(input[i], slow_get_page), answers[i]);
    }
}

TEST(TestLFULookUp, CacheTest) {
    size_t sz = 4;
    size_t input_length = 12;
    std::vector<int> input{1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4}; 

    LFUCache<int> cache(sz);

    std::vector<bool> answers{0,0,0,0,1,1,0,1,1,1,0,1};
    for (int i = 0; i < input_length; ++i) {
        EXPECT_EQ(cache.lookup_update(input[i], slow_get_page), answers[i]);
    }
}

