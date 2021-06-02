// dp
// iterate through each word and see if it can be formed by using other words. A word can only be formed by words shorter than it. So we can first sort the input by length of each word, and only try to form one word by using words in front of it.
class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> result;
        unordered_set<string> dict;
        sort(words.begin(), words.end(), [](auto &a, auto &b){
            return a.size() < b.size();
        });
        for (string& word: words) {
            if (canForm(word, dict)) {
                result.push_back(word);
            }
            dict.insert(word);
        }
        return result;
    }
private:
    // leetcode 139 word break
    bool canForm(string& s, unordered_set<string>& dict) {
        int n = s.length();
        if (n == 0) return false;
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
           for (int j = 0; j < i; j++) {
               string ss = s.substr(j, i - j);
               if (dp[j] && dict.find(ss) != dict.end()) {
                   dp[i] = true;
                   break;
               }
           } 
        }
        return dp[n];
    }
}
