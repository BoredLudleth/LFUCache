#pragma once

#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <iostream>
#include <format>

template <typename KeyT = int>
class PerfectCache {
    using ListIt = typename std::list<int>::iterator;
    using LengthT = int;

    size_t size;
    size_t amount = 0;

    std::list<int> cache_;

    std::unordered_map<KeyT, ListIt> hash_;
    std::map<LengthT, std::list<KeyT>, std::less<>> next_hit;

    std::unordered_map<KeyT, std::list<int>> input_arr;
    int input_length;
    int current_page = -1;

    bool full() const {
        return (size > amount) ? false : true;
    }

    int recount_next_hit (KeyT key) {
        input_arr[key].pop_front();

        KeyT result = input_arr[key].front();
        return result;
    }

    void erase_farrest() {
        auto it = next_hit.end();
        --it;
        cache_.erase(hash_[it->second.back()]);
        hash_.erase(it->second.back());
        it->second.pop_back();

        if (it->second.empty()) {
            next_hit.erase(it);
        }

        amount--;
    }

public:
    PerfectCache(size_t size ,size_t input_length, const std::vector<int>& input) : size(size)
                                                                             , input_length(input_length) {
        int cur_page = 0;
        for (auto it = input.begin(); it != input.end(); ++it, ++cur_page) {
            input_arr[*it].push_back(cur_page);
        }
        for (auto &cur_page : input_arr) {
            cur_page.second.push_back(input_length);
        }
                                                                             };

    template <typename F>
    bool lookup_update(KeyT key, F slow_get_page) {
        ++current_page;
        // print();

        auto hit = hash_.find(key);

        int length_next_it = recount_next_hit(key);
        if (hit == hash_.end()) {
            if (length_next_it == input_length) {
                slow_get_page(key);
                return false;
            }
            // missed
            if (full()) {
                erase_farrest();
            }

            amount++;
            cache_.push_front(slow_get_page(key));
            hash_[key] = cache_.begin();
            next_hit.erase(current_page);
            next_hit[length_next_it].push_back(key);

            return false;
        }

        next_hit.erase(current_page);
        next_hit[length_next_it].push_back(key);

        return true;
    }

    void print() const {
        for (const auto &page : cache_) {
            std::cout << std::format("{} ", page);
        }

        std::cout << std::endl;
    }
};
