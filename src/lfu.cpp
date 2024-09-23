#include "lfu_cache.hpp"

// #define DEBUG

#ifdef DEBUG
    #include <time.h>
#endif

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

    #ifdef DEBUG 1
        std::cout << "LFU-cache: " << total_hits << " hits" << std::endl;
        std::cout << "LFU-cache time: " << static_cast<float>(end_cache - start_cache) / static_cast<float>(CLOCKS_PER_SEC) << " sec" << std::endl;
    #else
        std::cout << total_hits << std::endl;
    #endif

    return 0;
}
