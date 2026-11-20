// Source: https://leetcode.com/problems/minimum-operations-to-sort-a-permutation
// Title: Minimum Operations to Sort a Permutation
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n`, where `nums` is a **permutation** of the integers from 0 to `n - 1`.
//
// You may perform **only** the following operations:
//
// - **Reverse** the entire array.
// - **Rotate Left by One**: Move the first element to the end of the array, and rest elements to left by one position.
//
// Return an integer denoting the **minimum** number of operations required to sort the array in **increasing** order. If it is **not possible** to sort the array using only the given operations, return -1.
//
// **Example 1:**
//
// ```
// Input: nums = [0,2,1]
// Output: 2
// Explanation:
// - Rotate Left by one: `[2, 1, 0]`
// - Reverse the array: `[0, 1, 2]`
//
// The array becomes sorted in 2 operations, which is minimal.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,0,2]
// Output: 2
// Explanation:
// - Reverse the array: `[2, 0, 1]`
// - Rotate Left by one: `[0, 1, 2]`
// The array becomes sorted in 2 operations, which is minimal.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [2,0,1,3]
// Output: -1
// Explanation:
// It is impossible to reach `[2, 0, 1, 3]`. Thus, the answer is -1.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 10^5`
// - `0 <= nums[i] <= n - 1`
// - `nums` is a permutation of integers from 0 to `n - 1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Intuition
//
// First assume that it is cyclic sorted (otherwise returns -1).
// Say 0 is at nums[k].
//
// Case A: 1 at nums[k+1].
// Case A1:
// - shift left for k steps (0 at nums[0])
// Case A2:
// - reverse                    (0 at nums[n-k-1])
// - shift left for n-k-1 steps (0 at nums[0])
// - shift left for 1 step      (0 at nums[n-1])
// - reverse                    (0 at nums[0])
// That is, min(k, n-k+2) steps.
//
// Case B: 1 at nums[k-1].
// Case B1:
// - shift left for k steps (0 at nums[0])
// - shift left for 1 step  (0 at nums[n-1])
// - reverse                    (0 at nums[0])
// Case B2:
// - reverse                    (0 at nums[n-k-1])
// - shift left for n-k-1 steps (0 at nums[0])
// That is, min(k+2, n-k) steps.
class Solution {
 public:
  int minOperations(const vector<int>& nums) {
    const int n = nums.size();

    // Trivial
    if (n <= 1) return 0;

    // Find 0
    int k = find(nums.cbegin(), nums.cend(), 0) - nums.cbegin();

    // Case A
    if (nums[(k + 1) % n] == 1) {
      // Check cyclic sorted
      for (int i = 2; i < n; ++i) {
        if (nums[(k + i) % n] != i) return -1;
      }

      return min(k, n - k + 2);
    }

    // Case B
    if (nums[(k + n - 1) % n] == 1) {
      // Check cyclic sorted
      for (int i = 2; i < n; ++i) {
        if (nums[(k + n - i) % n] != i) return -1;
      }

      return min(k + 2, n - k);
    }

    return -1;
  }
};
