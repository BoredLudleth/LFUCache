#ifndef LFU_CACHE_HPP
#define LFU_CACHE_HPP

#include <list>
#include <vector>

template <typename KeyT, typename PageT>
class LFUCache {
    size_t size;
    size_t amount;

    std::vector<std::list<PageT>::iterator> cache;
    std::list<PageT> mem;
    std::vector<int> freq;

    bool full() const;

public:
    LFUCache(size_t size) : size(size) {};
    ~LFUCache() = default;
    bool find_page(KeyT key) const;

    template <typename F>
    void load_page(KeyT key, F slow_get_page);
    
    KeyT find_least_freq();
};

#endif
