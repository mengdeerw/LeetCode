/*
1. 把n本书分给k个人复印，想要使每个人复印的总时间的最大值最小化，很明显答案是具有单调性的。
    为什么呢？因为假如时间time1足以完成n本书的复印，那么令time2>time1，我们可以说，在time2的时间内也可以完成n本书的复印。所以我们对完成所有复印所需要的时间进行二分：
2. 令times[]为每个人复印一本书所需要的时间，left 和 right 分别表示所需时间的上下界，我们可以初始化 left = 0，right = n *times[0]。
3. 令check函数返回是否能够在mid的时间内复印完成n本书，是为True，否为False。
在每一次查找的过程中，如果check(mid)返回True，说明时间为mid可行，继续查找更小的答案，我们使 right = mid ；如果check(mid)返回False，说明时间为mid不可行，mid还不够大，继续查找更大的答案，我们使 left = mid 。
最后判断 left 和 right 作为总时间是否可行，优先返回left 。
那么check(mid)怎么实现呢？
对于每个人，我们求出在mid的时间范围内最多能复印多少本书mid/times[]，最后累加的值如果大于n，说明足够返回True；否则返回False。
*/
// 二分时间复杂度O(logn)，每次判断为O(k)，时间复杂度O(klogn)
class Solution {
public:
    /**
     * @param n: An integer
     * @param times: an array of integers
     * @return: an integer
     */
    int copyBooksII(int n, vector<int> &times) {
        int left = 0, right = n * times[0];
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (check(times, n, mid)) { // can finish
                right = mid;
            } else {
                left = mid;
            }
        }
        if (check(times, n, left)) return left;
        return right;
    }
private:
    // whether can finish n books in time
    bool check(vector<int>& times, int n, int limit) {
        int count = 0;
        for (int i = 0; i < times.size(); i++) {
            count += limit / times[i];
        }
        return count >= n;
    }
};
