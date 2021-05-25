// top down: recursion - TLE
class Solution {
public:
    int rob(vector<int>& nums) {
        return dp(nums, 0);
    }
    
    // the max money in nums[start...]
    int dp(vector<int>& nums, int start) {
        if (start >= nums.size()) return 0;
        int result = max(dp(nums, start + 1), // not robbing, go to next room
                         nums[start] + dp(nums, start + 2)); // robbing, go to next next room
        return result;
    }
};

// top down: optimized recursion + memo
class Solution {
public:
    vector<int> memo;
    
    int rob(vector<int>& nums) {    
        memo.resize(nums.size(), -1);
        return dp(nums, 0);
    }
    
    // the max money in nums[start...]
    int dp(vector<int>& nums, int start) {
        if (start >= nums.size()) return 0;
        // means has already been calculated in previous memory
        if (memo[start] != -1) return memo[start];
        int result = max(dp(nums, start + 1), // not robbing, go to next room
                         nums[start] + dp(nums, start + 2)); // robbing, go to next next room
        // update memory
        memo[start] = result;
        return result;
    }
};

// bottom up: dp version 1
// define dp[i] as the max money we can make at house i (1-based), then this problem can be treated as knapsack problem
// time complexity: O(N)
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 1, 0); // 1-based
        dp[1] = nums[0]; 
        for (int i = 2; i <= n; i++) {
            dp[i] = max(dp[i - 1], // not robbing
                        dp[i - 2] + nums[i - 1]); // robbing at house i 
        }
        return dp[n];
    }
};

// bottom up: dp version 2
// define dp[i]: the max money can get if starting making choice at house i
// time complexity: O(N)
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 2, 0); 
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = max(dp[i + 1], // not robbing
                        dp[i + 2] + nums[i]); // robbing at house i 
        }
        return dp[0];
    }
};

// bottom up: dp version 3
// define dp[i] as the max money we can make at house i (1-based), robbed at the same day
// time complexity: O(N ^ 2)
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 1, 0); // 1-based
        dp[1] = nums[0]; 
        for (int i = 1; i <= n; i++) {
            dp[i] = nums[i - 1];
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i - 1; j++) {
                dp[i] = max(dp[j] + nums[i - 1], dp[i]);
            }
        }
        int max_money = 0;
        for (int d: dp) {
            max_money = max(max_money, d);
        }
        return max_money;
    }
};

// dp 空间压缩
// define dp[i] as the max money we can make at house i (1-based)
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        int dp_i_1 = 0, dp_i_2 = 0;
        int dp_i = 0;
        for (int i = 1; i <= n; i++) {
            dp_i = max(dp_i_1, // not robbing
                       dp_i_2 + nums[i - 1]); // robbing at house i
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }
        return dp_i;
    }
};
