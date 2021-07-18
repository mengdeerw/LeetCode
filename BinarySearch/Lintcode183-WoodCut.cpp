class Solution {
public:
    /**
     * @param L: Given n pieces of wood with length L[i]
     * @param k: An integer
     * @return: The maximum length of the small pieces
     */
    int woodCut(vector<int> &L, int k) {
        // write your code here
        int len_L = L.size();
        if (len_L == 0) return 0;
        int max_L = 0; // max length of wood
        for (int i = 0; i < len_L; i++) {
            max_L = max(max_L, L[i]);
        }
        long long left = 0, right = max_L;
        int mid;
        while (left + 1 < right) {
            mid = (int) (left + (right - left) / 2);
            if (check(L, k, len_L, mid)) { // 如果还能分
                left = mid;
            } else {
                right = mid;
            }
        }
        if (check(L, k, len_L, (int)right)) return right;
        return left;
    }
private:
    bool check(vector<int>& L, int k, int len_L, int target) {
        int count = 0;
        for (int i = 0; i < L.size(); i++) {
            count += L[i] / target;
        }
        // means wood can be cut in more pieces
        if (count >= k) return true;
        return false;
    }
};
