// Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd
// Title: Find the Number of Subsequences With Equal GCD
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`.
//
// Your task is to find the number of pairs of **non-empty** <button>subsequences</button> `(seq1, seq2)` of `nums` that satisfy the following conditions:
//
// - The subsequences `seq1` and `seq2` are **disjoint**, meaning **no index** of `nums` is common between them.
// - The <button>GCD</button> of the elements of `seq1` is equal to the GCD of the elements of `seq2`.
//
// Return the total number of such pairs.
//
// Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,4]
// Output: 10
// Explanation:
// The subsequence pairs which have the GCD of their elements equal to 1 are:
// - `([**1**, 2, 3, 4], [1, **2**, **3**, 4])`
// - `([**1**, 2, 3, 4], [1, **2**, **3**, **4**])`
// - `([**1**, 2, 3, 4], [1, 2, **3**, **4**])`
// - `([**1**, **2**, 3, 4], [1, 2, **3**, **4**])`
// - `([**1**, 2, 3, **4**], [1, **2**, **3**, 4])`
// - `([1, **2**, **3**, 4], [**1**, 2, 3, 4])`
// - `([1, **2**, **3**, 4], [**1**, 2, 3, **4**])`
// - `([1, **2**, **3**, **4**], [**1**, 2, 3, 4])`
// - `([1, 2, **3**, **4**], [**1**, 2, 3, 4])`
// - `([1, 2, **3**, **4**], [**1**, **2**, 3, 4])`
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [10,20,30]
// Output: 2
// Explanation:
// The subsequence pairs which have the GCD of their elements equal to 10 are:
// - `([**10**, 20, 30], [10, **20**, **30**])`
// - `([10, **20**, **30**], [**10**, 20, 30])`
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,1,1,1]
// Output: 50
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 200`
// - `1 <= nums[i] <= 200`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// 3D-DP
//
// Let N be the array length, and M be the maximum number.
// We first observe that the gcd(a, b) <= min(a, b).
// Therefore, the GCD of the subsequences is less than M.
// Since M and N are small, we can do DP on M and N.
//
// Let A, B be the two subsequences.
// Let DP[i][a][b] be the number of the possible states,
// where we only choose numbers from [0, i), A's GCD is a, and B's GCD is b.
//
// First, DP[0][0][0] = 1 since there are no numbers.
//
// From DP[i][a][b], we can compute DP[i][?][?].
// For the i-th number (say x), we have three choices:
//
// - Add it to A; then A's gcd becomes gcd(a, x); that is
//   DP[i+1][gcd(a, x)][b] += DP[i][a][b].
//
// - Add it to B; then B's gcd becomes gcd(b, x); that is
//   DP[i+1][a][gcd(b, x)] += DP[i][a][b].
//
// - Discard it; then both GCD are unchanges; that is
//   DP[i+1][a][b] += DP[i][a][b].
class Solution {
  constexpr static int modulo = 1e9 + 7;

  inline int mod(int x) {  //
    return x % modulo;
  }

 public:
  int subsequencePairCount(const vector<int>& nums) {
    const int n = nums.size();
    const int m = *max_element(nums.begin(), nums.end());

    // Use 1-indexing for i
    auto dp = vector<vector<vector<int>>>(n + 1, vector<vector<int>>(m + 1, vector<int>(m + 1, 0)));
    dp[0][0][0] = 1;
    for (int i = 0; i < n; ++i) {
      int num = nums[i];

      for (int a = 0; a <= m; ++a) {
        int newA = gcd(a, num);
        for (int b = 0; b <= m; ++b) {
          int cnt = dp[i][a][b];
          if (cnt == 0) continue;  // skip

          int newB = gcd(b, num);
          dp[i + 1][newA][b] = mod(dp[i + 1][newA][b] + cnt);
          dp[i + 1][a][newB] = mod(dp[i + 1][a][newB] + cnt);
          dp[i + 1][a][b] = mod(dp[i + 1][a][b] + cnt);
        }
      }
    }

    // Count answer
    int count = 0;
    for (int a = 1; a <= m; ++a) {  // skip a=0 empty subsequence
      count = mod(count + dp.back()[a][a]);
    }

    return count;
  }
};

// 2D-DP
class Solution2 {
  constexpr static int modulo = 1e9 + 7;

  inline int mod(int x) {  //
    return x % modulo;
  }

 public:
  int subsequencePairCount(const vector<int>& nums) {
    const int m = *max_element(nums.begin(), nums.end());

    // DP
    auto curr = vector<vector<int>>(m + 1, vector<int>(m + 1));
    auto prev = vector<vector<int>>(m + 1, vector<int>(m + 1));
    curr[0][0] = 1;
    for (const int num : nums) {
      swap(curr, prev);
      for (auto& row : curr) {  // reset
        fill(row.begin(), row.end(), 0);
      }

      for (int a = 0; a <= m; ++a) {
        int newA = gcd(a, num);
        for (int b = 0; b <= m; ++b) {
          int cnt = prev[a][b];
          if (cnt == 0) continue;  // skip

          int newB = gcd(b, num);
          curr[newA][b] = mod(curr[newA][b] + cnt);
          curr[a][newB] = mod(curr[a][newB] + cnt);
          curr[a][b] = mod(curr[a][b] + cnt);
        }
      }
    }

    // Count answer
    int count = 0;
    for (int a = 1; a <= m; ++a) {  // skip a=0 empty subsequence
      count = mod(count + curr[a][a]);
    }

    return count;
  }
};
