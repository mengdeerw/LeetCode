class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        // priority queue with map/pair
        unordered_map<string, int> counter;
        for (string word: words) {
            counter[word]++;
        }
        
        // using minHeap and pop the top node when it reaches size K, using time logK (dont forget to reverse the heap when outputting)
        // If we use maxHeap, it will take logN time to construct the heap
        auto cmp = [](const auto& a, const auto& b) {
          // put on top the pair with less frequency and greater lexicography
          return a.second > b.second || (a.second == b.second && a.first < b.first);  
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq (cmp);
        
        for (auto pair: counter) {
            pq.push(pair);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        
        vector<string> result;
        while (!pq.empty()) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        // at this point, result list is from least frequent words to most frequent words
        reverse(result.begin(), result.end());
        return result;
    }
};
