// Source: https://leetcode.com/problems/rotate-function
// Title: Rotate Function
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n`.
//
// Assume `arr_k` to be an array obtained by rotating `nums` by `k` positions clock-wise. We define the **rotation function** `F` on `nums` as follow:
//
// - `F(k) = 0 * arr_k[0] + 1 * arr_k[1] + ... + (n - 1) * arr_k[n - 1].`
//
// Return the maximum value of `F(0), F(1), ..., F(n-1)`.
//
// The test cases are generated so that the answer fits in a **32-bit** integer.
//
// **Example 1:**
//
// ```
// Input: nums = [4,3,2,6]
// Output: 26
// Explanation:
// F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
// F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
// F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
// F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
// So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [100]
// Output: 0
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= n <= 10^5`
// - `-100 <= nums[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// F(i)   = A[0]*i     + ... + A[n-i-1]*(n-1) + A[n-i]*0     + A[n-i+1]*1 + ... + A[n-1]*(i-1)
// F(i-1) = A[0]*(i-1) + ... + A[n-i-1]*(n-2) + A[n-i]*(n-1) + A[n-i+1]*0 + ... + A[n-1]*(i-2)
//
// F(i)-F(i-1) = A[0] + ... + A[n-i-1] - A[n-i]*(n-1) + A[n-i+1] + ... + A[n-1]
//           = sum(A) - A[n-i] * n
class Solution {
 public:
  int maxRotateFunction(const vector<int>& nums) {
    const int n = nums.size();

    // Prepare
    int sum = accumulate(nums.cbegin(), nums.cend(), 0);
    int f = 0;
    for (int i = 0; i < n; ++i) f += nums[i] * i;

    // Loop Max
    int maxF = f;
    for (int i = 1; i < n; ++i) {
      f += sum - nums[n - i] * n;
      maxF = max(maxF, f);
    }

    return maxF;
  }
};
