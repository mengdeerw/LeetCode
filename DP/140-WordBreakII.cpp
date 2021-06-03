// METHOD-1: bottom-up DP + backtrack
// reusing leetcode139 - word breakI

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        // define dp[i]: whether s[0...i - 1] can be added spaces in a valid way
        vector<bool> dp(n + 1, false); 
        //base case:
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            // check substring s[j, i - 1]
            for (int j = i - 1; j >= 0; j--) { // to optimize speed
                string cur = s.substr(j, i - j);
                if (dp[j] && dict.find(cur) != dict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        vector<string> result;
        if (dp[n]) {
            addSpaces(s, dp, 0, result, "", dict);
        }
        return result;
    }
    
    // backtrack
    void addSpaces(string& s, vector<bool>& dp, int pos, vector<string>& result, string temp, unordered_set<string>& dict) {
        int n = s.length();
        for (int i = pos + 1; i < dp.size(); i++) {
            if (dp[i]) { // means we need to add space at position i
                string newWord = s.substr(pos, i - pos);
                if (dict.count(newWord) != 0) {
                    if (i == n) {
                        result.push_back(temp + newWord);
                        return;
                    }
                    addSpaces(s, dp, i, result, temp + newWord + " ", dict);
                }
            }
        }
    }
};

// METHOD-2: recursion + memorization
class Solution {
public:
    unordered_map<string, vector<string>> memo;
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return wordBreak(s, dict);
    }
    
private:
    vector<string> append(vector<string> prefixes, string word) {
        vector<string> results;
        for (auto& prefix: prefixes) {
            results.push_back(prefix + " " + word);
        }
        return results;
    }
    
    vector<string> wordBreak(string s, unordered_set<string>& dict) {
        if (memo.count(s)) return memo[s];
        
        vector<string> result;
        if (dict.count(s)) {
            result.push_back(s);
        }
        for (int i = 1; i < s.length(); i++) {
            string right = s.substr(i);
            if (!dict.count(right)) continue;
            
            string left = s.substr(0, i);
            vector<string> left_result = append(wordBreak(left, dict), right);
            
            result.insert(result.end(), left_result.begin(), left_result.end());
        }
        
        memo[s].swap(result);
        return memo[s];
    }
};
