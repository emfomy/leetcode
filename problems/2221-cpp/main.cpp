// Source: https://leetcode.com/problems/find-triangular-sum-of-an-array
// Title: Find Triangular Sum of an Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** integer array `nums`, where `nums[i]` is a digit between `0` and `9` (**inclusive**).
//
// The **triangular sum** of `nums` is the value of the only element present in `nums` after the following process terminates:
//
// - Let `nums` comprise of `n` elements. If `n == 1`, **end** the process. Otherwise, **create** a new **0-indexed** integer array `newNums` of length `n - 1`.
// - For each index `i`, where `0 <= i <n - 1`, **assign** the value of `newNums[i]` as `(nums[i] + nums[i+1]) % 10`, where `%` denotes modulo operator.
// - **Replace** the array `nums` with `newNums`.
// - **Repeat** the entire process starting from step 1.
//
// Return the triangular sum of `nums`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2022/02/22/ex1drawio.png
//
// ```
// Input: nums = [1,2,3,4,5]
// Output: 8
// Explanation:
// The above diagram depicts the process from which we obtain the triangular sum of the array.```
//
// **Example 2:**
//
// ```
// Input: nums = [5]
// Output: 5
// Explanation:
// Since there is only one element in nums, the triangular sum is the value of that element itself.```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1000`
// - `0 <= nums[i] <= 9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <vector>

using namespace std;

// Brute-Force
class Solution {
 public:
  int triangularSum(vector<int>& nums) {
    int n = nums.size();
    for (auto i = n - 1; i >= 1; --i) {
      for (auto j = 0; j < i; ++j) {
        nums[j] = (nums[j] + nums[j + 1]) % 10;
      }
    }

    return nums[0];
  }
};

// Math
// Precompute binomial coefficients
class Solution2 {
 public:
  int triangularSum(vector<int>& nums) {
    static auto binom = makeBinom(1000);

    int n = nums.size();
    auto& coeff = binom[n - 1];

    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      ans = (ans + nums[i] * coeff[i]) % 10;
    }

    return ans;
  }

 private:
  vector<vector<int>> makeBinom(int n) {
    auto binom = vector<vector<int>>(n);
    binom[0] = {1};
    for (auto i = 1; i < n; ++i) {
      binom[i].resize(i + 1);
      binom[i][0] = binom[i - 1][0];
      binom[i][i] = binom[i - 1][i - 1];
      for (auto j = 1; j < i; ++j) {
        binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % 10;
      }
    }

    return binom;
  }
};

// Math
//
// Using Lucas's theorem
//
// By Lucas, C(m, n) = Prod_[n=0~k] C(m_i, n_i) (mod p),
// where m = m_k p^k + ... + m_0 p^0,
//       n = n_k p^k + ... + n_0 p^0, are the base p expansions of m and n respectively.
//
// Now we pick p = 2 and 5.
// Note that for p = 2, C(m_i, n_i) = 0 iff. m_i = 0 & n_i = 1.
// That is, `~m & n != 0`.
//
// Say C(m, n) = c_2 (mod 2), C(m, n) = c_5 (mod 5).
// By Chinese Remainder Theorem (CRT),
// C(m, n) = c_2 M_2 (M_2^(-1) mod 2) + c_5 M_5 (M_5^(-1) mod 5) (mod 10),
// where M_2 = 10/2 = 5, M_2^(-1) mod 2 = 1,
//       M_5 = 10/5 = 2, M_5^(-1) mod 5 = 3.
// That is, C(m, n) = 5 c_2 + 6 c_5 (mod 10)
class Solution3 {
 public:
  int triangularSum(vector<int>& nums) {
    int n = nums.size();

    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      ans = (ans + nums[i] * binom10(n - 1, i)) % 10;
    }

    return ans;
  }

 private:
  inline int binom10(int m, int n) {  //
    auto c2 = binom2(m, n), c5 = binom5(m, n);
    return (5 * c2 + 6 * c5) % 10;
  }

  inline int binom2(int m, int n) {  //
    return (~m & n) == 0;
  }

  inline int binom5(int m, int n) {
    static constexpr int C5[5][5] = {{1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 2, 1, 0, 0}, {1, 3, 3, 1, 0}, {1, 4, 1, 4, 1}};

    auto res = 1;
    while (res && (m > 0 || n > 0)) {  // also break if res is zero
      auto mi = m % 5, ni = n % 5;
      res = (res * C5[mi][ni]) % 5;
      m /= 5, n /= 5;
    }

    return res;
  }
};
