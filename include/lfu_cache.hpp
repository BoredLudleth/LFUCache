#pragma once

#include <list>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <format>

template <typename KeyT = int>
class LFUCache {
    using FreqT = size_t;
    using ListIt = typename std::list<int>::iterator;
    using PageT  = int;

    size_t size;
    size_t amount = 0;

    std::list<PageT> cache_;

    std::unordered_map<KeyT, ListIt> hash_;
    std::unordered_map<KeyT, FreqT> freq_;
    std::unordered_map<KeyT, ListIt> hash_data;
    std::unordered_map<FreqT, std::list<int>> data;

    FreqT min_freq = 1;

    bool full() const {
        return (size > amount) ? false : true;
    }

    void replace (KeyT key) {
        auto hit = hash_.find(key);

        data[freq_[key]].erase(hash_data[key]);
        ++freq_[key];
        data[freq_[key]].push_back(key);
        hash_data[key] = --data[freq_[key]].end();
    }

    void erase_min_freq() {
        cache_.erase(hash_[data[min_freq].front()]);
        hash_.erase(data[min_freq].front());
        hash_data.erase(data[min_freq].front());
        data[min_freq].pop_front();
        --amount;
    }

    void update_min_freq(KeyT key) {
        if (data[min_freq].empty() || min_freq > freq_[key])
            min_freq = freq_[key];
    }

public:
    LFUCache(size_t size) : size(size) {};

    template <typename F>
    bool lookup_update(KeyT key, F slow_get_page) {
        auto hit = hash_.find(key);

        // print();
        if (hit == hash_.end()) {
            if (full()) {
                erase_min_freq();
            }

            cache_.push_front(slow_get_page(key));

            if (freq_.find(key) == freq_.end()) {
                freq_[key] = 1;
            } else {
                ++freq_[key];
            }

            hash_[key] = cache_.begin();
            data[freq_[key]].push_back(key);
            hash_data[key] = --data[freq_[key]].end();
            ++amount;

            update_min_freq(key);

            return false;
        }

        replace(key);
        update_min_freq(key);

        return true;
    }

    void print() const {
        for (const auto &page : cache_) {
            std::cout << std::format("{} ", page);
        }

        std::cout << std::endl;
    }
};
