// METHOD-1 bottom-up dp:
// define dp[i][j] as the min number of operations to convert word1[0...i) to word2[0...j)
/*
there are totally four kinds of operations in two cases:
case1: if word1[i - 1] == word2[j - 1]:
       do 1. skip; dp[i][j] = dp[i - 1][j - 1]
case2: if word1[i] != word2[j]: 
take the minimum steps of operations to word1:
          2. insert: dp[i][j] = dp[i - 1][j] + 1
          3. delete: dp[i][j] = dp[i][j - 1]  +1
          4. replace:dp[i][j] = dp[i - 1][j - 1] + 1
*/
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.length(), len2 = word2.length();
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 2, 0));
        // base case1: word2 has finished comparison
        for (int i = 1; i <= len1; i++) {
            dp[i][0] = i;
        }
        // base case2: word1 has finished comparison
        for (int j = 1; j <= len2; j++) {
            dp[0][j] = j;
        }
        // bottom-up
        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min_3(
                        dp[i - 1][j] + 1, // insert char to word1
                        dp[i][j - 1] + 1, // delete char in word1
                        dp[i - 1][j - 1] + 1 // replace char in word1
                    );
                }
            }
        }
        return dp[len1][len2];
    }
    
private:
    int min_3(int a, int b, int c) {
        return min(a, min(b, c));
    }
};


// METHOD-2: top-down recursion + memorization
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size(), len2 = word2.size();
        //base cases
        if (len1 == 0) return len2;
        if (len2 == 0) return len1;
        vector<vector<int>> memo (len1, vector<int>(len2, -1));
        return stepsToMatch(word1, word2, 0, 0, memo);
    }
    
    int stepsToMatch(string& s1, string& s2, int i, int j, vector<vector<int>>& memo) {
        // base cases
        if (s1.length() == i) return s2.size() - j;
        if (s2.length() == j) return s1.size() - i;
        // check if current case is already in memory
        if (memo[i][j] != -1) return memo[i][j];
        
        if (s1[i] == s2[j]) { // do skip operation
            memo[i][j] = stepsToMatch(s1, s2, i + 1, j + 1, memo);
        } else {
            memo[i][j] = min(
                stepsToMatch(s1, s2, i + 1, j, memo) + 1, // insert to s1
                stepsToMatch(s1, s2, i, j + 1, memo) + 1, // delete char in s1
                stepsToMatch(s1, s2, i + 1, j + 1, memo) + 1 // replace char in s1 from s2
            );
        }
        return memo[i][j];
    } 
private:
    int min(int a, int b, int c) {
        return std::min(a, std::min(b, c));
    }
};

// version2: with pointers in reversed index traversal: recursion + memorization
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size(), len2 = word2.size();
        //base cases
        if (len1 == 0) return len2;
        if (len2 == 0) return len1;
        vector<vector<int>> memo (len1, vector<int>(len2, -1));
        return stepsToMatch(word1, word2, len1 - 1, len2 - 1, memo);
    }
    
    int stepsToMatch(string& s1, string& s2, int i, int j, vector<vector<int>>& memo) {
        // base cases
        if (i == -1) return j + 1;
        if (j == -1) return i + 1;
        // check if current case is already in memory
        if (memo[i][j] != -1) return memo[i][j];
        
        if (s1[i] == s2[j]) { // do skip operation
            memo[i][j] = stepsToMatch(s1, s2, i - 1, j - 1, memo);
        } else {
            memo[i][j] = min(
                stepsToMatch(s1, s2, i, j - 1, memo) + 1, // insert to s1
                stepsToMatch(s1, s2, i - 1, j, memo) + 1, // delete char in s1
                stepsToMatch(s1, s2, i - 1, j - 1, memo) + 1 // replace char in s1 from s2
            );
        }
        return memo[i][j];
    } 
private:
    int min(int a, int b, int c) {
        return std::min(a, std::min(b, c));
    }
};
