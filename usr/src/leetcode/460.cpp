#include <iostream>
#include <vector>

/*
LC 460 LFU Cache

Design a cache that evicts the Least Frequently Used key.
  LFUCache(int capacity)    the cache holds at most `capacity` keys.
  int get(int key)          the key's value, or -1 if the key isn't there.
  void put(int key, int value)
                            update the key's value if it is there; otherwise
                            insert it. If inserting would go over capacity,
                            first evict the key with the smallest use count.
                            On a tie, evict the least recently used of them.
A key's use count starts at 1 when it is inserted. Every get or put on a key
that is already there adds 1. get and put must each run in O(1) on average.
1 <= capacity <= 1e4, 0 <= key <= 1e5, 0 <= value <= 1e9,
at most 2e5 calls to get and put.

The tests run under LeakSanitizer, so anything you `new` must be freed by
the time the cache is destroyed.
*/

class LFUCache {
    public:
    LFUCache(int capacity) {
    }

    int get(int key) {
        return -1;
    }

    void put(int key, int value) {
    }
};

#ifndef TEST
int main() {
    LFUCache cache(2);
    cache.put(1, 1);                     // counts: 1->1
    cache.put(2, 2);                     // counts: 1->1, 2->1
    std::cout << cache.get(1) << '\n';   // 1     counts: 1->2, 2->1
    cache.put(3, 3);                     // evict 2 (count 1)
    std::cout << cache.get(2) << '\n';   // -1
    std::cout << cache.get(3) << '\n';   // 3     counts: 1->2, 3->2
    cache.put(4, 4);                     // tie at 2: evict 1, used longer ago
    std::cout << cache.get(1) << '\n';   // -1
    std::cout << cache.get(3) << '\n';   // 3
    std::cout << cache.get(4) << '\n';   // 4
    return 0;
}
#endif
