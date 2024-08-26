#include "lfu_cache.hpp"
#include <algorithm>

bool LFUCache::check_page(const KeyT& key) {
    if (find_page(key)) {
        ++freq[key];
        return true;
    }

    load_page(key, slow_get_page);
    ++freq[key];
    return false;
}

bool LFUCache::find_page(const KeyT& key) const {
    if (std::find(cache.begin, cache.end, key) != cache.end)
        return true;

    return false;
}

template <typename F>
void LFUCache::load_page(KeyT key, F slow_get_page) {
    auto least_freq = find_least_freq();

    // delete in list
    // slow_get_page
    // update in vector
}
    
auto LFUCache::find_least_freq() const {
    auto least_freq = cache.begin;
    size_t min_freq = freq[*cache.begin];

    for (auto it = cache.begin; it != cache.end; ++it) {
        if(freq[*it] < min_freq) {
            min_freq = freq[*it];
            least_freq = it;
        }
    }

    return least_freq;
}