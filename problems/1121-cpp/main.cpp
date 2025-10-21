// Source: https://leetcode.com/problems/divide-array-into-increasing-sequences
// Title: Divide Array Into Increasing Sequences
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` sorted in non-decreasing order and an integer `k`, return `true` if this array can be divided into one or more disjoint increasing subsequences of length at least `k`, or `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,2,3,3,4,4], k = 3
// Output: true
// Explanation: The array can be divided into two subsequences [1,2,3,4] and [2,3,4] with lengths at least 3 each.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [5,6,6,7,8], k = 3
// Output: false
// Explanation: There is no way to divide the array using the conditions required.
// ```
//
// **Constraints:**
//
// - `1 <= k <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^5`
// - `nums` is sorted in non-decreasing order.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Math
//
// First count the frequency of each number.
//
// Say there are total n elements.
// Say the maximum frequency if `f`; that is, we need at least `f` subsequences.
// Therefore, we need at least `f * k` total elements.
//
// Now we only need to compare `n >= f * k`.
class Solution {
 public:
  bool canDivideIntoSubsequences(vector<int>& nums, int k) {
    int n = nums.size();
    auto m = nums.back();  // max value

    // Frequency
    auto freqs = vector<int>(m + 1);
    auto f = 0;
    for (auto num : nums) {
      ++freqs[num];
      f = max(f, freqs[num]);
    }

    return n >= f * k;
  }
};

// Math
//
// We don't need to compute the maximum frequency.
// We can check the inequality for each frequency.
class Solution2 {
 public:
  bool canDivideIntoSubsequences(vector<int>& nums, int k) {
    int n = nums.size();
    auto pre = nums[0], cnt = 0;
    for (auto num : nums) {
      if (num == pre) {
        ++cnt;
      } else {
        pre = num;
        cnt = 1;
      }
      if (n < cnt * k) return false;
    }
    return true;
  }
};
