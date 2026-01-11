// Source: https://leetcode.com/problems/max-dot-product-of-two-subsequences
// Title: Max Dot Product of Two Subsequences
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two arrays `nums1`and `nums2`.
//
// Return the maximum dot product between **non-empty** subsequences of nums1 and nums2 with the same length.
//
// A subsequence of a array is a new array which is formed from the original array by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie,`[2,3,5]`is a subsequence of`[1,2,3,4,5]`while `[1,5,3]`is not).
//
// **Example 1:**
//
// ```
// Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
// Output: 18
// Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
// Their dot product is (2*3 + (-2)*(-6)) = 18.```
//
// **Example 2:**
//
// ```
// Input: nums1 = [3,-2], nums2 = [2,-6,7]
// Output: 21
// Explanation: Take subsequence [3] from nums1 and subsequence [7] from nums2.
// Their dot product is (3*7) = 21.```
//
// **Example 3:**
//
// ```
// Input: nums1 = [-1,-1], nums2 = [1,1]
// Output: -1
// Explanation: Take subsequence [-1] from nums1 and subsequence [1] from nums2.
// Their dot product is -1.```
//
// **Constraints:**
//
// - `1 <= nums1.length, nums2.length <= 500`
// - `-1000 <= nums1[i], nums2[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// 2D-DP
//
// It is similar to sequence alignment algorithm.
// We use the product of any number as the weight.
//
// Let W[i, j] = Num1[i] * Num2[j].
// Let DP[i, j] be the maximum inner product of the any non-empty subsequences of nums1[:i] and nums2[:j].
//
// DP[i, j] = max(
//   W[i, j],               // start from here, for the non-empty constraint
//   DP[i-1, j-1] + W[i, j] // pick current numbers to extend
//   DP[i-1, j], DP[i, j-1] // ignore either of current number
// )
class Solution {
 public:
  int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    auto dp = vector(m + 1, vector(n + 1, int(-1e8)));  // use -1e8 to avoid empty subsequence

    for (auto i = m - 1; i >= 0; --i) {
      for (auto j = n - 1; j >= 0; --j) {
        auto w = nums1[i] * nums2[j];
        dp[i][j] = max({
            w,
            dp[i + 1][j + 1] + w,
            dp[i + 1][j],
            dp[i][j + 1],
        });
      }
    }

    return dp[0][0];
  }
};

// 1D-DP
//
// It is similar to sequence alignment algorithm.
// We use the product of any number as the weight.
//
// Let W[i, j] = Num1[i] * Num2[j].
// Let DP[i, j] be the maximum inner product of the any non-empty subsequences of nums1[:i] and nums2[:j].
//
// DP[i, j] = max(
//   W[i, j],               // start from here, for the non-empty constraint
//   DP[i-1, j-1] + W[i, j] // pick current numbers to extend
//   DP[i-1, j], DP[i, j-1] // ignore either of current number
// )
class Solution2 {
 public:
  int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    auto curr = vector(n + 1, int(-1e8));  // use -1e8 to avoid empty subsequence
    auto prev = vector(n + 1, int(-1e8));

    for (auto i = m - 1; i >= 0; --i) {
      swap(curr, prev);
      for (auto j = n - 1; j >= 0; --j) {
        auto w = nums1[i] * nums2[j];
        curr[j] = max({
            w,
            prev[j + 1] + w,
            prev[j],
            curr[j + 1],
        });
      }
    }

    return curr[0];
  }
};
