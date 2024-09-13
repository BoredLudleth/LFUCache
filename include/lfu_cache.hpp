#ifndef LFU_CACHE_HPP
#define LFU_CACHE_HPP

#include <list>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <iostream>
#include <algorithm>

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
    std::unordered_map<FreqT, std::list<int>> data;

    FreqT min_freq = 1;

    bool full() const {
        return (size > amount) ? false : true;
    }

public:
    LFUCache(size_t& size) : size(size) {};

    void replace (KeyT key) {
        auto hit = hash_.find(key);

        // data[freq_[key]].erase(std::find(data[freq_[key]].begin(), data[freq_[key]].end(), key));
        ++freq_[key];
        data[freq_[key]].push_back(key);
    }

    template <typename F>
    bool lookup_update(KeyT key, F slow_get_page) {
        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                cache_.erase(hash_[data[min_freq].front()]);
                hash_.erase(data[min_freq].front());
                data[min_freq].pop_front();
                --amount;
            }

            cache_.push_front(slow_get_page(key));

            if (freq_.find(key) == freq_.end()) {
                freq_[key] = 1;
            } else {
                ++freq_[key];
            }

            hash_[key] = cache_.begin();
            data[freq_[key]].push_back(key);

            ++amount;

            if (data[min_freq].empty() || min_freq > freq_[key]) {
                min_freq = freq_[key];
            }

            return false;
        }

        replace(key);

        if (data[min_freq].empty()) {
            min_freq = freq_[key];
        }

        return true;
    }

    void print() {
        for (auto it = cache_.begin(); it != cache_.end(); ++it) {
            std::cout << *it << "(" << freq_[*it] << ")"<< " ";
        }

        std::cout << std::endl;
    }
};
#endif
