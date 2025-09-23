// Source: https://leetcode.com/problems/find-peak-element
// Title: Find Peak Element
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A peak element is an element that is strictly greater than its neighbors.
//
// Given a **0-indexed** integer array `nums`, find a peak element, and return its index. If the array contains multiple peaks, return the index to **any of the peaks**.
//
// You may imagine that `nums[-1] = nums[n] = -∞`. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.
//
// You must write an algorithm that runs in `O(log n)` time.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,1]
// Output: 2
// Explanation: 3 is a peak element and your function should return the index number 2.```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,1,3,5,6,4]
// Output: 5
// Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1000`
// - `-2^31 <= nums[i] <= 2^31 - 1`
// - `nums[i] != nums[i + 1]` for all valid `i`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// One pass, O(n)
class Solution {
 public:
  int findPeakElement(vector<int>& nums) {
    int n = nums.size();

    if (n == 1) return 0;
    if (nums[0] > nums[1]) return 0;
    if (nums[n - 1] > nums[n - 2]) return n - 1;

    for (auto i = 1; i < n - 1; i++) {
      if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) {
        return i;
      }
    }

    return -1;
  }
};

// Binary Search
//
// Let d[i] = sign(nums[i]-nums[i-1]) be the sign of the differences.
// We know that d[0] > 0 and d[n] < 0 since outside is -inf.
//
// Say `nums[p]` is the peak number. We have d[p] > 0 and d[p+1] < 0.
// By intermediate value theorem, such p exists.
//
// We can use binary search to find it.
class Solution2 {
 public:
  int findPeakElement(vector<int>& nums) {
    int n = nums.size();

    if (n == 1) return 0;
    if (nums[0] > nums[1]) return 0;
    if (nums[n - 1] > nums[n - 2]) return n - 1;

    // Binary search
    auto lo = 1, hi = n;  // [1, n) is unknown
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      auto d = nums[mid] - nums[mid - 1];
      if (d > 0) {
        lo = mid + 1;  // [mid+1, hi)
      } else {
        hi = mid;  // [lo, mid)
      }
    }
    // d[lo-1] > 0, d[lo=hi] < 0

    return lo - 1;
  }
};
