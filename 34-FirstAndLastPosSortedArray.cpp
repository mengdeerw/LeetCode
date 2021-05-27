// METHOD-1: binary search with flag
// time complexity: O(logN)
// space complexity: O(1)
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // no need to check empty array; if nums array is empty, function will both return -1
        int first = findPos(nums, target, true);
        int last = findPos(nums, target, false);
        return {first, last};
    }

private:
    int findPos(vector<int>& nums, int target, bool isFirst) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2; // directly calculate (l+r)/2 might cause overflow!!!
            if (nums[mid] == target) {
                if (isFirst) { // lower bound
                    // check if we find the first index
                    if (mid == left || nums[mid - 1] < target) {
                        //found the first position
                        return mid; 
                    }
                    // not found, keep searching on the left side
                    right = mid; 
                } else { // upper bound
                    // check if we find the last index
                    if (mid + 1 == right || nums[mid + 1] > target) {
                        //found the last position
                        return mid; 
                    }
                    // not found, keep searching on the right side
                    left = mid + 1;
                }
            } else if (nums[mid] > target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
};

// METHOD-2: binary search with flag
// time complexity: O(logN)
// space complexity: O(1)
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // no need to check empty array; if nums array is empty, function will both return -1
        int first = findPos(nums, target, true);
        int last = findPos(nums, target, false);
        return {first, last};
    }

private:
    int findPos(vector<int>& nums, int target, bool isFirst) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2; // directly calculate (l+r)/2 might cause overflow!!!
            if (nums[mid] == target) {
                if (isFirst) { // lower bound
                    // check if we find the first index
                    if (mid == left || nums[mid - 1] < target) {
                        //found the first position
                        return mid; 
                    }
                    // not found, keep searching on the left side
                    right = mid; 
                } else { // upper bound
                    // check if we find the last index
                    if (mid + 1 == right || nums[mid + 1] > target) {
                        //found the last position
                        return mid; 
                    }
                    // not found, keep searching on the right side
                    left = mid + 1;
                }
            } else if (nums[mid] > target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
};
