// dp version1
/* 
three cases:
1. not robbing at both first and last house
2. only robs at the first house, not rob the last house
3. only robs at the last house, not rob the first house
case1 is included in case 2 & 3 already
*/
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        return max(robRange(nums, 0, n - 2),  // case 2
                   robRange(nums, 1, n - 1)); // case 3
    }
    
    int robRange(vector<int>& nums, int start, int end) {
        int n = nums.size();
        vector<int> dp(n + 2, 0); 
        for (int i = end; i >= start; i--) {
            dp[i] = max(dp[i + 1], // not robbing
                        dp[i + 2] + nums[i]); // robbing at house i 
        }
        return dp[start];
    }
};

//dp version2
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        return max(robRange(nums, 0, n - 2),
                   robRange(nums, 1, n - 1));
    }
    
    int robRange(vector<int>& nums, int start, int end) {
        int n = nums.size();
        int dp_i_1 = 0, dp_i_2 = 0;
        int dp_i = 0;
        for (int i = start; i <= end; i++) {
            dp_i = max(dp_i_1, // not robbing
                       dp_i_2 + nums[i]); // robbing at house i
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }
        return dp_i;
    }
};
