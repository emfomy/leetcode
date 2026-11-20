// Source: https://leetcode.com/problems/k-concatenation-maximum-sum
// Title: K-Concatenation Maximum Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `arr` and an integer `k`, modify the array by repeating it `k` times.
//
// For example, if `arr = [1, 2]` and `k = 3 `then the modified array will be `[1, 2, 1, 2, 1, 2]`.
//
// Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be `0` and its sum in that case is `0`.
//
// As the answer can be very large, return the answer **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: arr = [1,2], k = 3
// Output: 9
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [1,-2,1], k = 5
// Output: 2
// ```
//
// **Example 3:**
//
// ```
// Input: arr = [-1,-2], k = 7
// Output: 0
// ```
//
// **Constraints:**
//
// - `1 <= arr.length <= 10^5`
// - `1 <= k <= 10^5`
// - `-10^4 <= arr[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <numeric>
#include <vector>

using namespace std;

// DP (Kadane)
//
// Let PreMax/SufMax be the maximum prefix/suffix subarray sum.
// Let InMax be the maximum subarray sum.
//
// If k = 1, apply Kadane on arr.
// If k >= 2, sum(arr) < 0, apply Kadane on arr+arr.
// If k >= 2, sum(arr) >= 0, apply Kadane on arr+arr and added by sum(arr)*(k-2).
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

 private:
  int64_t kadane(const vector<int>& arr, int repeat) {
    int64_t maxSum = 0;
    int64_t currSum = 0;
    for (int i = 0; i < repeat; ++i) {
      for (int64_t num : arr) {
        currSum = max(currSum + num, num);
        maxSum = max(maxSum, currSum);
      }
    }

    return maxSum;
  }

 public:
  int kConcatenationMaxSum(const vector<int>& arr, const int k) {
    const int n = arr.size();

    // Guard
    if (k <= 0) return 0;

    // k = 1
    if (k == 1) {
      return kadane(arr, 1) % modulo;
    }

    // k >= 2
    int64_t arrSum = accumulate(arr.cbegin(), arr.cend(), int64_t(0));
    int64_t maxSum = kadane(arr, 2);
    if (arrSum > 0) {
      maxSum += arrSum * (k - 2);
    }
    return maxSum % modulo;
  }
};
