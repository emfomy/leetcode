// Source: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum
// Title: Number of Sub-arrays With Odd Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `arr`, return the number of subarrays with an **odd** sum.
//
// Since the answer can be very large, return it modulo `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: arr = [1,3,5]
// Output: 4
// Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
// All sub-arrays sum are [1,4,9,3,8,5].
// Odd sums are [1,9,3,5] so the answer is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [2,4,6]
// Output: 0
// Explanation: All subarrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
// All sub-arrays sum are [2,6,12,4,10,6].
// All sub-arrays have even sum and the answer is 0.
// ```
//
// **Example 3:**
//
// ```
// Input: arr = [1,2,3,4,5,6,7]
// Output: 16
// ```
//
// **Constraints:**
//
// - `1 <= arr.length <= 10^5`
// - `1 <= arr[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// DP
//
// Use DP to count the number of subarrays with even / odd sum.
// Let Even[i] / Odd[i] be the count that end at i.
// If num[i] is even, then Even[i] = Even[i-1] + 1, Odd[i] = Odd[i-1].
// If num[i] is odd, then Even[i] = Odd[i-1], Odd[i] = Even[i-1] + 1.
class Solution {
  static constexpr int64_t modulo = 1e9 + 7;  // modulo

 public:
  int numOfSubarrays(const vector<int>& arr) {
    int64_t ans = 0;
    int even = 0, odd = 0;

    for (int num : arr) {
      if (num % 2 == 0) {  // even
        ++even;
      } else {
        swap(even, odd);
        ++odd;
      }

      ans += odd;
    }

    return ans % modulo;
  }
};

// Count Prefix Sum
//
// A subarray [i, j) is the difference of two prefix sum `j` and `i`.
// A subarray with odd sum is the difference of an odd and an even prefix.
// Note that the order is determined by the size of i and j (i.e. i < j).
class Solution2 {
  static constexpr int64_t modulo = 1e9 + 7;  // modulo

 public:
  int numOfSubarrays(const vector<int>& arr) {
    const int n = arr.size();
    int odd = 0;     // prefix sum count, empty prefix is even
    int parity = 0;  // parity of prefix sum
    for (int num : arr) {
      parity ^= (num & 1);
      odd += parity;
    }
    int64_t even = (n + 1) - odd;  // total n+1 prefixes, including empty and full

    return (even * odd) % modulo;
  }
};
