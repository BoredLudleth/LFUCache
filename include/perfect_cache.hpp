#ifndef PERFECT_CACHE_HPP
#define PERFECT_CACHE_HPP

#include <list>

template <typename KeyT, typename PageT>
class PerfectCache {
private:
    size_t size;
    size_t length;

    std::vector<std::list<PageT>::iterator> cache;
    std::list<PageT> mem;
    std::vector<PageT> input;

    bool full() const;



public:
    PerfectCache(size_t size) : size(size) {};

    ~PerfectCache() = default;

    bool find_page(KeyT key) const;

    template <typename F>
    void load_page(KeyT key, F slow_get_page);
    
    KeyT find_least_freq();
};

#endif
