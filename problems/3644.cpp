// Source: https://leetcode.com/problems/maximum-k-to-sort-a-permutation
// Title: Maximum K to Sort a Permutation
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n`, where `nums` is a **permutation** of the numbers in the range `[0..n - 1]`.
//
// You may swap elements at indices `i` and `j` **only if** `nums[i] AND nums[j] == k`, where `AND` denotes the bitwise AND operation and `k` is a **non-negative** integer.
//
// Return the **maximum** value of `k` such that the array can be sorted in **non-decreasing** order using any number of such swaps. If `nums` is already sorted, return 0.
//
// **Example 1:**
//
// ```
// Input: nums = [0,3,2,1]
// Output: 1
// Explanation:
// Choose `k = 1`. Swapping `nums[1] = 3` and `nums[3] = 1` is allowed since `nums[1] AND nums[3] == 1`, resulting in a sorted permutation: `[0, 1, 2, 3]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,1,3,2]
// Output: 2
// Explanation:
// Choose `k = 2`. Swapping `nums[2] = 3` and `nums[3] = 2` is allowed since `nums[2] AND nums[3] == 2`, resulting in a sorted permutation: `[0, 1, 2, 3]`.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [3,2,1,0]
// Output: 0
// Explanation:
// Only `k = 0` allows sorting since no greater `k` allows the required swaps where `nums[i] AND nums[j] == k`.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 10^5`
// - `0 <= nums[i] <= n - 1`
// - `nums` is a permutation of integers from `0` to `n - 1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Assume that k is an answer.
//
// Say we want to swap A and B.
// Then there is a chain A, C1, C2, ..., Ct, B, s.t.
// A & C1 = k, C1 & C2 = k, ..., Ct & B = k.
// That is, k ⊆ A & B. (⊆ means bits(k) is a subset of bits(A & B)).
//
// Therefore, we apply bit-and on all dislocated numbers.
// Say the bit-and of these numbers is m.
// We know that k ⊆ m (and k <= m).
//
// Note that m < n, therefore m exists in the array (since nums is permutation of 0~n-1).
// Since m is the intersection of all dislocated numbers A,
// we know that m & A = m.
// Therefore, we can sort all these numbers by swapping with m.
//
// Hence largest k is m.
class Solution {
 public:
  int sortPermutation(const vector<int>& nums) {
    const int n = nums.size();

    int k = -1;  // all bits
    for (int i = 0; i < n; ++i) {
      if (nums[i] != i) {
        k &= nums[i];
      }
    }

    return max(k, 0);  // if k = -1, then the array is already sorted
  }
};
