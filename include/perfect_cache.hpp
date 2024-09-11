#ifndef PERFECT_CACHE_HPP
#define PERFECT_CACHE_HPP

#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

template <typename KeyT = int>
class PerfectCache {
    size_t size;
    size_t amount = 0;

    std::list<int> cache_;
    using ListIt = typename std::list<int>::iterator;

    std::unordered_map<KeyT, ListIt> hash_;
    std::unordered_map<KeyT, int> next_hit;

    std::vector<KeyT> input;
    size_t current_page = 0;
    int input_length;

    bool full() const {
        return (size > amount) ? false : true;
    }

    int page_to_key (int page) const {
        return page;
    }

    void update_location(KeyT key) {
        auto hit = hash_.find(key);
        auto eltit = hit->second;
        auto after_eltit = cache_.begin();

        while (next_hit[page_to_key(*eltit)] <= next_hit[page_to_key(*after_eltit)]) {
            after_eltit = std::next(after_eltit);
            if (after_eltit == cache_.end())
                break;
            
        }
        
        cache_.splice(after_eltit, cache_, eltit);
    }

    KeyT find_close(KeyT key) {
        KeyT close_key = page_to_key(*cache_.begin());
        int close_length = next_hit[close_key];

        for (auto it = cache_.begin(); it != cache_.end(); ++it) {
            auto next = it;
            ++next;

            if (close_length >= next_hit[page_to_key(*next)])
                continue;
            return close_key;
        }

        return page_to_key(cache_.back());
    }

    int recount_next_hit (KeyT key) {
        for (int i = current_page; i != input_length; ++i) {
            if (key == input[i]) {
                return i;
            }
        }

        return input_length;
    }
public:
    PerfectCache(size_t& size ,size_t& input_length, std::vector<int>& input) : size(size)
                                                                              , input_length(input_length)
                                                                              , input(input)  {};

    template <typename F>
    bool lookup_update(KeyT key, F slow_get_page) {
        current_page++;
        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            // missed
            if (full()) {
                hash_.erase(cache_.front());
                next_hit.erase(cache_.front());
                cache_.pop_front();
            }

            cache_.push_front(slow_get_page(key));
            hash_[key] = cache_.begin();
            amount++;
            next_hit[key] = recount_next_hit(key);

            update_location(key);

            return false;
        }

        next_hit[key] = recount_next_hit(key);

        if (hit->second != cache_.begin()) {
            cache_.splice(cache_.begin(), cache_, hit->second, std::next(hit->second));
            hit->second = cache_.begin();
        }

        update_location(key);

        return true;
    }
};
#endif
