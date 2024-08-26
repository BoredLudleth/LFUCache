#include "perfect_cache.hpp"

bool PerfectCache::find_page(const KeyT& key) const {
    if (std::find(cache.begin, cache.end, key) != cache.end)
        return true;

    return false;
}