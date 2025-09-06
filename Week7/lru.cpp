#include <vector>
#include <iostream>

using namespace std;


class LRUCache {
private:
    class Tracker{
        public:
        int val;
        int timestamp;
        Tracker(int val): val(val){}
    };
    int capacity;
    unordered_map<int,Tracker*> cache;
    int timestamp;
public:
    /**
     * Initialize the LRU cache with positive size capacity.
     */
    LRUCache(int capacity): capacity(capacity), timestamp(0){
        // How to keep track of the last used key??
        // Can either have a sorted map with O(logn) insertions and removals and O(1) evict
        // So expecting more than capacity get and put operations and 1 evict operation - O(nlogn)
        // Other option is use a normal map with O(1) for get and put. But O(n) to find LRU
        // So expecting more than capacity get and put operations and 1 evict operation - O(n)
    }
    
    /**
     * int get(int key) Return the value of the key if the key exists, otherwise return -1.
     */
    int get(int key) {
        if(cache.find(key) == cache.end()) return -1;
        cache[key]->timestamp = timestamp;
        timestamp++;
        return cache[key]->val;
    }
    
    /**
     * void put(int key, int value) Update the value of the key if the key exists. 
     * Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
     */
    void put(int key, int value) {
        if(cache.find(key) != cache.end()){
            cache[key]->val = value;
            cache[key]->timestamp = timestamp;
            timestamp++;
            return;
        }
        if(cache.size() == capacity){
            evict();
        }

        cache[key] = new Tracker(value);
        cache[key]->timestamp = timestamp;
        timestamp++;
    }

    /**
     * Helper function to evict the least recently used cache
     * O(n) runtime
     */
    void evict(){
        int key = 0;
        int minTimestamp = INT_MAX;

        for(auto pair : cache){
            if(pair.second->timestamp < minTimestamp){
                minTimestamp = pair.second->timestamp;
                key = pair.first;
            }
        }
        delete cache[key];
        cache.erase(key); // Removes the least recently used key
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

void test1(){
    LRUCache cache(2);
    cache.put(1,1);
    cache.put(2,2);
    cout << cache.get(1) << endl;
    cache.put(3,3);
    cout << cache.get(2) << endl;
    cache.put(4,4);
    cout << cache.get(1) << endl;
    cout << cache.get(3) << endl;
    cout << cache.get(4) << endl;

    // [{1, {1,0}},{2, {2,1}}, ]
}

int main(){
    test1();
    return 0;
}