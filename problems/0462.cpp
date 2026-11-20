// Source: https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii
// Title: Minimum Moves to Equal Array Elements II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` of size `n`, return the minimum number of moves required to make all array elements equal.
//
// In one move, you can increment or decrement an element of the array by `1`.
//
// Test cases are designed so that the answer will fit in a **32-bit** integer.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3]
// Output: 2
// Explanation:
// Only two moves are needed (remember each move increments or decrements one element):
// [1,2,3]  =>  [2,2,3]  =>  [2,2,2]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,10,2,9]
// Output: 16
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= nums.length <= 10^5`
// - `-10^9 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

using namespace std;

// Sort + Median
//
// Say the final value is x.
// We want to prove that it is the median.
//
// We use triangular inequality |p-x| + |q-x| >= |q-p|
// Note that the equality holds when p <= x <= q
//
// Say the number a[i] are sorted.
//
// Case 1: n is even (n = 2k).
// S = sum[i=0~k-1] |x-a[i]| + |a[n-1-i]-x|
//  >= sum[i=0~k-1] |a[n-1-i]-a[i]|
//   = sum[i=0~k-1] (a[n-1-i]-a[i]) = T
// Since T is irrelevant to x, T is the lower bound.
// And the equality holds when a[i] <= x <= a[n-1-i] for all i;
// that is, x is any number between a[k-1] and a[k] (median is one of the answer).
// Note that we can also pick a[k] as the answer (so x = a[n/2] for both cases).
//
// Case 2: n is odd (n = 2k+1)
// Similarly,
// S = |a[k] - x| + sum[i=0~k-1] |x-a[i]| + |a[n-1-i]-x|
//  >= 0          + sum[i=0~k-1] (a[n-1-i]-a[i]) = T
// The equality holds when a[k] = x and a[i] <= x <= a[n-1-i];
// that is, x = a[k] (i.e. the median).
class Solution {
 public:
  int minMoves2(vector<int>& nums) {
    const int n = nums.size();

    // Find median
    sort(nums.begin(), nums.end());
    int x = nums[n / 2];

    // Loop
    int ans = 0;
    for (int num : nums) {
      ans += abs(num - x);
    }

    return ans;
  }
};

// Sort
//
// Instead of computing x, we can compute T directly.
class Solution2 {
 public:
  int minMoves2(vector<int>& nums) {
    const int n = nums.size(), k = n / 2;

    // Sort
    sort(nums.begin(), nums.end());

    // Answer
    int ans = accumulate(nums.crbegin(), nums.crbegin() + k, 0)  //
              - accumulate(nums.cbegin(), nums.cbegin() + k, 0);

    return ans;
  }
};

// Quick Select
//
// Instead of computing x, we can compute T directly.
class Solution3 {
 public:
  int minMoves2(vector<int>& nums) {
    const int n = nums.size(), k = n / 2;

    // Quick select
    nth_element(nums.begin(), nums.begin() + k, nums.end());

    // Answer
    int ans = accumulate(nums.crbegin(), nums.crbegin() + k, 0)  //
              - accumulate(nums.cbegin(), nums.cbegin() + k, 0);

    return ans;
  }
};
