
class LFUCache {
    int capacity, minFreq;
    unordered_map<int, pair<int,int>> cache;
    unordered_map<int, list<int>> freqList;
    unordered_map<int, list<int>::iterator> pos;

    void updateFreq(int key) {
        int freq = cache[key].second;
        freqList[freq].erase(pos[key]);
        if (freqList[freq].empty()) {
            freqList.erase(freq);
            if (minFreq == freq) minFreq++;
        }
        cache[key].second++;
        int newFreq = cache[key].second;
        freqList[newFreq].push_front(key);
        pos[key] = freqList[newFreq].begin();
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) return -1;
        int value = cache[key].first;
        updateFreq(key);
        return value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (cache.find(key) != cache.end()) {
            cache[key].first = value;
            updateFreq(key);
            return;
        }

        if (cache.size() == capacity) {
            int keyToRemove = freqList[minFreq].back();
            freqList[minFreq].pop_back();
            if (freqList[minFreq].empty()) freqList.erase(minFreq);
            cache.erase(keyToRemove);
            pos.erase(keyToRemove);
        }

        cache[key] = {value, 1};
        freqList[1].push_front(key);
        pos[key] = freqList[1].begin();
        minFreq = 1;
    }
};
