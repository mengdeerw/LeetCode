/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// recursion: TLE
class Solution {
public:
    int rob(TreeNode* root) {
        if (!root) return 0;
        
        int rob_it = root->val
                  + (root->left == NULL ? 0 : rob(root->left->left) + rob(root->left->right))
                  + (root->right == NULL ? 0 : rob(root->right->left) + rob(root->right->right));
        int not_rob = rob(root->left) + rob(root->right);
        return max(rob_it, not_rob);
    }
};

// recursion + memorization
class Solution {
public:
    unordered_map<TreeNode*, int> memo;
    
    int rob(TreeNode* root) {
        if (!root) return 0;
        if (memo[root] != 0) return memo[root];
        
        // rob the current root and go to grandchildren
        int rob_it = root->val
                   + (root->left == NULL ? 0 : rob(root->left->left) + rob(root->left->right))
                   + (root->right == NULL ? 0 : rob(root->right->left) + rob(root->right->right));
        // not rob current root, go to next child
        int not_rob = rob(root->left) + rob(root->right);
        int result = max(rob_it, not_rob);
        // update memo
        memo[root] = result;
        return result;
    }
};

// Redefine rob(root) as a new function which will return an array of two elements, the first element of which denotes the maximum amount of money that can be robbed if root is not robbed, while the second element signifies the maximum amount of money robbed if it is robbed.
class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> result = robSub(root);
        return max(result[0], result[1]);
    }
    
    // result[0]: not robbed; result[1]: robbed
    vector<int> robSub(TreeNode* root) {
        if (!root) return vector<int>(2);
        vector<int> left = robSub(root->left);
        vector<int> right = robSub(root->right);
        vector<int> result (2);
        
        result[0] = max(left[0], left[1]) + max(right[0], right[1]); // not robbed
        result[1] = root->val + left[0] + right[0]; // robbed
        
        return result;
    }
};
