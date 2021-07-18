// binary search
// 对于假定的时间上限 tm 我们可以使用贪心的思想判断这 k 个人能否完成复印 n 本书的任务: 
// 将尽可能多的书分给同一个人, 判断复印完这 n 本书需要的人数是否不大于 k 即可.
// 而时间上限 tm 与可否完成任务(0或1)这两个量之间具有单调性关系, 所以可以对 tm 进行二分查找, 查找最小的 tm, 使得任务可以完成.
/*
基于答案值域的二分法。 答案的范围在 max(pages)~sum(pages) 之间，
每次二分到一个时间 time_limit 的时候，用贪心法从左到右扫描一下 pages，看看需要多少个人来完成抄袭。 
如果这个值 <= k，那么意味着大家花的时间可能可以再少一些;
如果 > k 则意味着人数不够，需要降低工作量
*/
// 时间复杂度 O(Nlog(sum))

class Solution {
public:
    /**
     * @param pages: an array of integers
     * @param k: An integer
     * @return: an integer
     */
    int copyBooks(vector<int> &pages, int k) {
        // search range: [max(pages), sum(pages)]
        if (pages.empty()) return 0;
        int sum = 0;
        int max = pages[0]; // the max page
        for (int i = 0; i < pages.size(); i++) {
            sum += pages[i];
            if (max < pages[i]) max = pages[i];
        }

        // binary search the time limit (pages): 1 minute to copy 1 page
        int start = max, end = sum;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (countCopiers(pages, mid) > k) { // cannot complete, need more time
                start = mid;
            } else {
                end = mid;
            }
        }
        if (countCopiers(pages, start) <= k) return start; // choose less time
        return end;
    }
private:
    int countCopiers(vector<int>& pages, int limit) {
        int copiers = 1;
        int sum = pages[0];
        for (int i = 1; i < pages.size(); i++) { 
            if (sum + pages[i] > limit) {
                copiers++;
                sum = 0; // reset, because we need a new person to copy
            }
            sum += pages[i];
        }
        return copiers;
    }
};
