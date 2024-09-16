#ifndef PERFECT_CACHE_HPP
#define PERFECT_CACHE_HPP

#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <iostream>
#include <deque>

template <typename KeyT = int>
class PerfectCache {
    using ListIt = typename std::list<int>::iterator;
    using LengthT = int;

    size_t size;
    size_t amount = 0;

    std::list<int> cache_;

    std::unordered_map<KeyT, ListIt> hash_;
    std::map<LengthT, std::list<KeyT>> next_hit;

    // std::deque<KeyT> input;
    int input_length;
    int current_page = 0;

    bool full() const {
        return (size > amount) ? false : true;
    }

    int recount_next_hit (std::deque<KeyT>& keys, KeyT key) {
        auto hit = std::find(keys.begin(), keys.end(), key);

        if (hit == keys.end())
            return input_length;

        return static_cast<int>(hit - keys.begin() + current_page);
    }

public:
    PerfectCache(size_t& size ,size_t& input_length, std::deque<int>& input) : size(size)
                                                                              , input_length(input_length) {};

    template <typename F>
    bool lookup_update(std::deque<KeyT>& keys, F slow_get_page) {
        // print();
        // print_map();
        current_page++;
        KeyT key = keys.front();
        keys.pop_front();

        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            int length_next_it = recount_next_hit(keys, key);

            if (length_next_it == input_length) {
                slow_get_page(key);
                return false;
            }

            // missed
            if (full()) {
                auto it = next_hit.end();
                --it;

                cache_.erase(hash_[it->second.front()]);
                hash_.erase(it->second.front());
                next_hit.erase(it);
                amount--;
            }

            amount++;
            cache_.push_front(slow_get_page(key));
            hash_[key] = cache_.begin();
            next_hit[length_next_it].push_back(key);

            return false;
        }

        next_hit.erase(current_page - 1);
        next_hit[recount_next_hit(keys, key)].push_back(key);

        return true;
    }

    void print() {
        for (auto it = cache_.begin(); it != cache_.end(); ++it) {
            std::cout << *it << " ";
        }

        std::cout << std::endl;
    }

    void print_map() {
        for (auto it = next_hit.begin(); it != next_hit.end(); ++it) {
            std::cout << it->first << "(" << it->second.front() << ") ";
        }

        std::cout << std::endl;
    }
};
#endif
