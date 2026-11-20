// Source: https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes
// Title: Minimum Changes to Make K Semi-palindromes
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` and an integer `k`, partition `s` into `k` **<button>substrings</button>** such that the letter changes needed to make each substring a **semi-palindrome**are minimized.
//
// Return the **minimum** number of letter changes required.
//
// A **semi-palindrome** is a special type of string that can be divided into **<button>palindromes</button>** based on a repeating pattern. To check if a string is a semi-palindrome:
//
// - Choose a positive divisor `d` of the string's length. `d` can range from `1` up to, but not including, the string's length. For a string of length `1`, it does not have a valid divisor as per this definition, since the only divisor is its length, which is not allowed.
// - For a given divisor `d`, divide the string into groups where each group contains characters from the string that follow a repeating pattern of length `d`. Specifically, the first group consists of characters at positions `1`, `1 + d`, `1 + 2d`, and so on; the second group includes characters at positions `2`, `2 + d`, `2 + 2d`, etc.
// - The string is considered a semi-palindrome if each of these groups forms a palindrome.
//
// Consider the string `"abcabc"`:
//
// - The length of `"abcabc"` is `6`. Valid divisors are `1`, `2`, and `3`.
// - For `d = 1`: The entire string `"abcabc"` forms one group. Not a palindrome.
// - For `d = 2`:
//
// - Group 1 (positions `1, 3, 5`): `"acb"`
// - Group 2 (positions `2, 4, 6`): `"bac"`
// - Neither group forms a palindrome.
//
// - For `d = 3`:
//
// - Group 1 (positions `1, 4`): `"aa"`
// - Group 2 (positions `2, 5`): `"bb"`
// - Group 3 (positions `3, 6`): `"cc"`
// - All groups form palindromes. Therefore, `"abcabc"` is a semi-palindrome.
//
// **Example 1: **
//
// ```
// Input: s = "abcac", k = 2
// Output: 1
// Explanation:  Divide `s` into `"ab"` and `"cac"`. `"cac"` is already semi-palindrome. Change `"ab"` to `"aa"`, it becomes semi-palindrome with `d = 1`.
// ```
//
// **Example 2: **
//
// ```
// Input: s = "abcdef", k = 2
// Output: 2
// Explanation:  Divide `s` into substrings `"abc"` and `"def"`. Each needs one change to become semi-palindrome.
// ```
//
// **Example 3: **
//
// ```
// Input: s = "aabbaa", k = 3
// Output: 0
// Explanation:  Divide `s` into substrings `"aa"`, `"bb"` and `"aa"`. All are already semi-palindromes.
// ```
//
// **Constraints:**
//
// - `2 <= s.length <= 200`
// - `1 <= k <= s.length / 2`
// - `s` contains only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <string>
#include <vector>

using namespace std;

// DP + Preprocessing
//
// Define C[i, j] be the min changes for substr [i, j).
// Loop for all possible divisor d.
// For each d, loop for all possible substr size m = j-i. (m must be multiple of d.)
// For each case, compute the changes required for each i.
//
// Next use DP to compute the total min changes.
// Let DP[i, t] be the min changes for [0, i) with t substrs.
class Solution {
  static constexpr int kInf = INT_MAX / 4;

 public:
  int minimumChanges(const string &s, int k) {
    const int n = s.size();

    // Precompute, O(n^3 logn)
    // d range is O(n)
    // m range is [2d, n], with O(n/d) values
    // i range is n-m = O(n)
    // j range is d
    // l range is m/(2d) = O(n/d)
    //
    // For each d, the complexity is
    // n/d * n * d * n/d = n^3/d
    // Total complexity is
    // sum_d n^3 1/d = n^3 sum_d 1/d ~= n^3 log n
    auto changes = vector(n, vector<int>(n + 1, kInf));
    for (int d = 1; d < n; ++d) {            // divisor
      for (int m = 2 * d; m <= n; m += d) {  // substr size
        for (int i = 0; i + m <= n; ++i) {   // substr [i, i+m)
          // Loop for group
          int required = 0;
          for (int j = 0; j < d; ++j) {  // j, j+d, ...
            for (int l = i + j, r = i + m + j - d; l < r; l += d, r -= d) {
              required += (s[l] != s[r]);
            }
          }

          changes[i][i + m] = min(changes[i][i + m], required);
        }
      }
    }

    // DP, O(k n^2)
    auto dp = vector(n + 1, vector<int>(k + 1, kInf));
    dp[0][0] = 0;
    for (int t = 0; t < k; ++t) {
      // substr [i, j)
      for (int i = 0; i < n; ++i) {
        if (dp[i][t] >= kInf) continue;  // skip INF
        for (int j = i + 2; j <= n; ++j) {
          dp[j][t + 1] = min(dp[j][t + 1], dp[i][t] + changes[i][j]);
        }
      }
    }

    return dp.back().back();
  }
};

// DP + Preprocessing
//
// Denote s[l:r:d] as s[l]+s[l+d]+...+s[r-d]+s[r] (r inclusive).
// Note that s[l:r:d] = s[l]+s[l+d:r-d:d]+s[r]
// The cost for s[l:r:d] can be computed from s[l+d:r-d:d].
//
// Therefore, for fixed d,
// C[i, i+m] can be computed from C[i+d, i+m-d] (i.e. i => i+d, m => m-2d).
class Solution2 {
  static constexpr int kInf = INT_MAX / 4;

 public:
  int minimumChanges(const string &s, int k) {
    const int n = s.size();

    // Precompute, O(n^3)
    // d range is O(n)
    // m range is [2d, n], with O(n/d) values
    // i range is n-m = O(n)
    // j range is d
    //
    // For each d, the complexity is n/d * n * d = n^2
    // Therefore, total complexity is O(n^3)
    auto changes = vector(n, vector<int>(n + 1, kInf));
    auto subchanges = vector(n, vector<int>(n + 1, kInf));  // for each d
    for (int d = 1; d < n; ++d) {                           // divisor

      // m = 2d
      {
        int m = 2 * d;
        for (int i = 0; i + m <= n; ++i) {  // substr [i, i+m)
          // Loop for group
          int required = 0;
          for (int j = 0; j < d; ++j) {  // j, j+d
            required += (s[i + j] != s[i + j + d]);
          }
          subchanges[i][i + m] = required;
          changes[i][i + m] = min(changes[i][i + m], required);
        }
      }

      // m = 3d
      {
        int m = 3 * d;
        for (int i = 0; i + m <= n; ++i) {  // substr [i, i+m)
          // Loop for group
          int required = 0;
          for (int j = 0; j < d; ++j) {  // j, j+d, j+2d
            required += (s[i + j] != s[i + j + 2 * d]);
          }
          subchanges[i][i + m] = required;
          changes[i][i + m] = min(changes[i][i + m], required);
        }
      }

      // m > 3d
      for (int m = 4 * d; m <= n; m += d) {  // substr size
        for (int i = 0; i + m <= n; ++i) {   // substr [i, i+m)
          int required = subchanges[i + d][i + m - d];
          for (int j = 0; j < d; ++j) {  // j, j+d, ...
            required += (s[i + j] != s[i + m + j - d]);
          }
          subchanges[i][i + m] = required;
          changes[i][i + m] = min(changes[i][i + m], required);
        }
      }
    }

    // DP, O(k n^2)
    auto dp = vector(n + 1, vector<int>(k + 1, kInf));
    dp[0][0] = 0;
    for (int t = 0; t < k; ++t) {
      // substr [i, j)
      for (int i = 0; i < n; ++i) {
        if (dp[i][t] >= kInf) continue;  // skip INF
        for (int j = i + 2; j <= n; ++j) {
          dp[j][t + 1] = min(dp[j][t + 1], dp[i][t] + changes[i][j]);
        }
      }
    }

    return dp.back().back();
  }
};

// DP + Preprocessing
//
// Improve inner loop for m.
class Solution3 {
  static constexpr int kInf = INT_MAX / 4;

 public:
  int minimumChanges(const string &s, int k) {
    const int n = s.size();

    // Precompute, O(n^3)
    auto changes = vector(n, vector<int>(n + 1, kInf));
    auto subchanges = vector(n, vector<int>(n + 1, kInf));  // for each d

    // Init for m=0
    for (int i = 0; i < n; ++i) subchanges[i][i] = 0;

    // Loop d
    for (int d = 1; d < n; ++d) {
      // Init for m=d
      for (int i = 0; i + d < n; ++i) subchanges[i][i + d] = 0;

      // Loop m
      for (int m = 2 * d; m <= n; m += d) {  // substr size
        for (int i = 0; i + m <= n; ++i) {   // substr [i, i+m)
          int required = subchanges[i + d][i + m - d];
          for (int j = 0; j < d; ++j) {  // j, j+d, ...
            required += (s[i + j] != s[i + m + j - d]);
          }
          subchanges[i][i + m] = required;
          changes[i][i + m] = min(changes[i][i + m], required);
        }
      }
    }

    // DP, O(k n^2)
    auto dp = vector(n + 1, vector<int>(k + 1, kInf));
    dp[0][0] = 0;
    for (int t = 0; t < k; ++t) {
      // substr [i, j)
      for (int i = 0; i < n; ++i) {
        if (dp[i][t] >= kInf) continue;  // skip INF
        for (int j = i + 2; j <= n; ++j) {
          dp[j][t + 1] = min(dp[j][t + 1], dp[i][t] + changes[i][j]);
        }
      }
    }

    return dp.back().back();
  }
};
