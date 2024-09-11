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
    size_t size;
    size_t amount = 0;

    std::list<int> cache_;
    using ListIt = typename std::list<int>::iterator;

    std::unordered_map<KeyT, ListIt> hash_;
    std::unordered_map<KeyT, int> freq_;

    bool full() const {
        return (size > amount) ? false : true;
    }

    int page_to_key (int page) {
        return page;
    }

    void update_location(KeyT key) {
        auto hit = hash_.find(key);
        auto eltit = hit->second;
        auto after_eltit = std::next(eltit);

        if (after_eltit != cache_.end()) {
            while (freq_[*eltit] >= freq_[*after_eltit]) {
                after_eltit = std::next(after_eltit);
                if (after_eltit == cache_.end())
                    break;
                
            }
            
            cache_.splice(after_eltit, cache_, eltit);
        }
    }

public:
    LFUCache(size_t& size) : size(size) {};

    template <typename F>
    bool lookup_update(KeyT key, F slow_get_page) {
        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                hash_.erase(cache_.front());
                cache_.pop_front();
            }

            cache_.push_front(slow_get_page(key));
            hash_[key] = cache_.begin();
            freq_[key]++;
            amount++;
            update_location(key);

            return false;
        }

        freq_[key]++;
        update_location(key);


        return true;
    }
};
#endif
