// 1. Monotonic Queue
// Time complexity: O(n)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> index;
        vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            while (!index.empty() && nums[i] >= nums[index.back()]) {
                index.pop_back();
            }
            index.push_back(i);
            if (i >= k - 1) result.push_back(nums[index.front()]);
            if (i - k + 1 >= index.front()) index.pop_front();
            
        }
        return result;
    }
};

// 2. BST - Multiset
// Time complexity: O((n-k+1)*logk)

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        multiset<int> window (nums.begin(), nums.begin() + k -1);
        
        for (int i = k - 1; i < nums.size(); i++) {
            window.insert(nums[i]);
            // push into the result with the max of current window
            result.push_back(*window.rbegin());
            if (i >= k - 1)
                window.erase(window.equal_range(nums[i - k + 1]).first);
        }
        return result;
    }
};

// 3. Priority Queue
// Time complexity: O((n-k+1)*logk)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        priority_queue<pair<int, int>> pq;//max heap
        for (int i = 0; i < nums.size(); i++) {
            while (!pq.empty() && (pq.top().second <= i - k)) {
                    pq.pop();
            }
            pq.push({nums[i], i});
            if (i >= k - 1) result.push_back(pq.top().first);
        }
        return result;
    }
};

// 4. Brute Force
// Time complexity: O((n – k + 1) * k)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        for (int i = k - 1; i < nums.size(); i++) {
            result.push_back(*max_element(nums.begin() + i + 1 - k, nums.begin() + i + 1));
        }
        return result;
    }
};
