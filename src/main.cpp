#include "lfu_cache.hpp"
#include "perfect_cache.hpp"

#include <time.h>
#include <fstream>
#include <iostream>


int slow_get_page(int key) {
    return key;
}

int main() {
    size_t m;          //size
    size_t n;          //number of pages
    
    std::cin >> m >> n;

    std::vector<int> cache_buff;

    for (int i = 0, temp = 0; i < n; i++) {
        std::cin >> temp;
        cache_buff.push_back(temp); 
    }

    unsigned int start_cache = clock ();
    
    LFUCache cache_lfu(m);
    size_t total_hits = 0;

    for (int i = 0; i < n; i++) {
        total_hits += cache_lfu.lookup_update (cache_buff[i], slow_get_page);
    }

    unsigned int end_cache = clock ();

    std::cout << "LFU-cache: " << total_hits << " hits" << std::endl;
    std::cout << "LFU-cache time: " << static_cast<float>(end_cache - start_cache) / static_cast<float>(CLOCKS_PER_SEC) << " sec" << std::endl;

    start_cache = clock ();

    PerfectCache<int> cache_perfect(m, n, cache_buff);
    total_hits = 0;

    for (int i = 0; i < n; i++) {
        total_hits += cache_perfect.lookup_update (cache_buff[i], slow_get_page);
    }

    end_cache = clock ();

    std::cout << "Perfect-cache: " << total_hits << " hits" << std::endl;
    std::cout << "Perfect-cache time: " << static_cast<float>(end_cache - start_cache) / static_cast<float>(CLOCKS_PER_SEC) << " sec" << std::endl;

    return 0;
}