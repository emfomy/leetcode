// Source: https://leetcode.com/problems/shortest-unsorted-continuous-subarray
// Title: Shortest Unsorted Continuous Subarray
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, you need to find one **continuous subarray** such that if you only sort this subarray in non-decreasing order, then the whole array will be sorted in non-decreasing order.
//
// Return the shortest such subarray and output its length.
//
// **Example 1:**
//
// ```
// Input: nums = [2,6,4,8,10,9,15]
// Output: 5
// Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4]
// Output: 0
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1]
// Output: 0
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^4`
// - `-10^5 <= nums[i] <= 10^5`
//
// **Follow up:** Can you solve it in `O(n)` time complexity?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <stack>
#include <vector>

using namespace std;

// Sort & Compare
class Solution {
 public:
  int findUnsortedSubarray(vector<int>& nums) {
    auto nums2 = vector<int>(nums);

    sort(nums2.begin(), nums2.end());

    int n = nums.size();
    auto lo = 0, hi = n;
    while (lo < hi && nums[lo] == nums2[lo]) ++lo;
    while (lo < hi && nums[hi - 1] == nums2[hi - 1]) --hi;

    return hi - lo;
  }
};

// Stack
class Solution2 {
 public:
  int findUnsortedSubarray(vector<int>& nums) {
    int n = nums.size();

    auto leftSt = stack<int>();  // indices for increasing
    auto leftIdx = INT_MAX;      // left index of unsorted number
    for (auto i = 0; i < n; ++i) {
      while (!leftSt.empty() && nums[leftSt.top()] > nums[i]) {
        leftIdx = min(leftIdx, leftSt.top());
        leftSt.pop();
      }
      leftSt.push(i);
    }

    auto rightSt = stack<int>();  // indices for increasing
    auto rightIdx = INT_MIN;      // right index of unsorted number
    for (auto i = n - 1; i >= 0; --i) {
      while (!rightSt.empty() && nums[rightSt.top()] < nums[i]) {
        rightIdx = max(rightIdx, rightSt.top());
        rightSt.pop();
      }
      rightSt.push(i);
    }

    if (leftIdx == INT_MAX && rightIdx == INT_MIN) return 0;

    return rightIdx - leftIdx + 1;
  }
};

// Two pointer
//
// Find the minimal number `lo` after first decreasing.
// Also (go reverse) find the max number `hi` after first increasing.
//
// Go from left and find a number larger than `lo`, this number is not sorted.
// Go from right and find a number less than `hi`, this number is not sorted.
//
// The range is what we want.
class Solution3 {
 public:
  int findUnsortedSubarray(vector<int>& nums) {
    int n = nums.size();

    auto lo = INT_MAX;
    auto loFlag = false;
    for (auto i = 1; i < n; ++i) {
      // starts decreasing
      if (nums[i] < nums[i - 1]) loFlag = true;

      // find minimal
      if (loFlag) lo = min(lo, nums[i]);
    }

    auto hi = INT_MIN;
    auto hiFLag = false;
    for (auto i = n - 2; i >= 0; --i) {
      // starts increasing
      if (nums[i] > nums[i + 1]) hiFLag = true;

      // find minimal
      if (hiFLag) hi = max(hi, nums[i]);
    }

    // Is sorted
    if (lo == INT_MAX && hi == INT_MIN) return 0;

    // Find first larger
    auto l = 0;
    while (l < n && nums[l] <= lo) ++l;

    // Find first less
    auto r = n - 1;
    while (r >= 0 && nums[r] >= hi) --r;

    return r - l + 1;
  }
};
