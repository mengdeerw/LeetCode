// METHOD-1: brute force
/*
  wordBreak("leetcode")  
= wordBreak("") && isInDict("leetcode") 
||wordBreak("l") && isInDict("eetcode")  
||wordBreak("le") && isInDict("etcode")  ....
*/
/*
Time complexity : O(2^n). 
Given a string of length n, there are n + 1 ways to split it into two parts. At each step, we have a choice: to split or not to split. In the worse case, when all choices are to be checked, that results in O(2^n).
Space complexity : O(n). The depth of the recursion tree can go upto n.
*/
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        set<string> wordSet(wordDict.begin(), wordDict.end());
        return wordBreak(s, wordSet, 0);
    }
    
    bool wordBreak(string& s, set<string>& wordSet, int start) {
        if (start == s.length()) return true;
        for (int end = start + 1; end <= s.length(); end++) {
            string cur = s.substr(start, end - start);
            if (wordSet.find(cur) != wordSet.end()
               && wordBreak(s, wordSet, end)) {
                return true;
            }
        }
        return false;
    }
};

//METHOD-2: recursion + memo
/*
n is the length of the input string.
Time complexity : O(n^3). Size of recursion tree can go up to n^2
Space complexity : O(n). The depth of recursion tree can go up to n.
*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<int> memo(s.length(), -1); // -1 means initial state
        return wordBreak(s, wordSet, 0, memo);
    }
    
    bool wordBreak(string& s, set<string>& wordSet, int start, vector<int>& memo) {
        if (start == s.length()) return true;
        // check if memory has the current case
        if (memo[start] != -1) return memo[start];
        
        for (int end = start + 1; end <= s.length(); end++) {
            string cur = s.substr(start, end - start);
            if (wordSet.find(cur) != wordSet.end()
               && wordBreak(s, wordSet, end, memo)) {
                memo[start] = true;
                return memo[start];
            }
        }
        return memo[start] = false;
    }
};

// METHOD-3: iterative BFS
// the idea is pushing ending index i of every possible strings into the queue as the new starting point of BFS, then we need to repeat the same process for string s[i + 1, end] until we hit the last element of the given string
// time complexity: O(N^3)
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        set<string> wordSet(wordDict.begin(), wordDict.end());
        queue<int> q; // save the end index of last string
        vector<bool> visited(s.length(), false); // to avoid duplicate search
        q.push(0);
        while (!q.empty()) {
            int start = q.front();
            q.pop();
            if (visited[start]) continue;
            for (int end = start + 1; end <= s.length(); end++) {
                string cur = s.substr(start, end - start);
                // check if in the dictionary
                if (wordSet.find(cur) != wordSet.end()) {
                    q.push(end);
                    // check if hit the end of the original string
                    if (end == s.length()) return true;
                }
            }
            visited[start] = true;
        }
        return false;
    }
};

// METHOD-4: dp 
// substring s1 = s[0...i] split into s2 = s1[0...j - 1] & s3 = s1[j...i]
// then if dp[j] = true && s[j...i], set dp[i] = true
/*
Time complexity : O(n^3).There are two nested loops, and substring computation at each iteration. Overall that results in O(n^3).
Space complexity : O(n)
*/
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.length() + 1, false);
        dp[0] = true; //empty string is alwys present in dictionary
        
        for (int i = 1; i <= s.length(); i++) {
            for (int j = 0; j < i; j++) {
                string ss = s.substr(j, i - j);
                if (dp[j] && wordSet.find(ss) != wordSet.end()) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.length()];
    }
};
