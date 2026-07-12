// Source: https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii
// Title: Concatenate Non-Zero Digits and Multiply by Sum II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` of length `m` consisting of digits. You are also given a 2D integer array `queries`, where `queries[i] = [l_i, r_i]`.
//
// For each `queries[i]`, extract the **<button>substring</button>** `s[l_i..r_i]`. Then, perform the following:
//
// - Form a new integer `x` by concatenating all the **non-zero digits** from the substring in their original order. If there are no non-zero digits, `x = 0`.
// - Let `sum` be the **sum of digits** in `x`. The answer is `x * sum`.
//
// Return an array of integers `answer` where `answer[i]` is the answer to the `i^th` query.
//
// Since the answers may be very large, return them **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: s = "10203004", queries = [[0,7],[1,3],[4,6]]
// Output: [12340, 4, 9]
// Explanation:
// - `s[0..7] = "10203004"`
//   - `x = 1234`
//   - `sum = 1 + 2 + 3 + 4 = 10`
//   - Therefore, answer is `1234 * 10 = 12340`.
// - `s[1..3] = "020"`
//   - `x = 2`
//   - `sum = 2`
//   - Therefore, the answer is `2 * 2 = 4`.
// - `s[4..6] = "300"`
//   - `x = 3`
//   - `sum = 3`
//   - Therefore, the answer is `3 * 3 = 9`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "1000", queries = [[0,3],[1,1]]
// Output: [1, 0]
// Explanation:
// - `s[0..3] = "1000"`
//   - `x = 1`
//   - `sum = 1`
//   - Therefore, the answer is `1 * 1 = 1`.
// - `s[1..1] = "0"`
//   - `x = 0`
//   - `sum = 0`
//   - Therefore, the answer is `0 * 0 = 0`.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "9876543210", queries = [[0,9]]
// Output: [444444137]
// Explanation:
// - `s[0..9] = "9876543210"`
//   - `x = 987654321`
//   - `sum = 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 45`
//   - Therefore, the answer is `987654321 * 45 = 44444444445`.
//   - We return `44444444445 modulo (10^9 + 7) = 444444137`.
// ```
//
// **Constraints:**
//
// - `1 <= m == s.length <= 10^5`
// - `s` consists of digits only.
// - `1 <= queries.length <= 10^5`
// - `queries[i] = [l_i, r_i]`
// - `0 <= l_i <= r_i < m`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// Prefix Sum
//
// Convert the string into a new string without zeros.
// Also create an index array maps the original index to the new one.
//
// Compute the prefix sum of the new string.
// Compute the prefix numbers.
// Compute 10^i for all possible i.
//
// Let sums[i] be the prefix sum of [0, i).
// Let nums[i] be the prefix number of  [0, i).
// Let units[i] be the 10^i.
//
// For any query [i, j):
// sum = sums[j] - sums[i],
// num = nums[j] - nums[i] * units[j-i].
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

  inline int64_t mod(int64_t x) {
    return ((x % modulo) + modulo) % modulo;  //
  }

 public:
  vector<int> sumAndMultiply(const string& s, const vector<vector<int>>& queries) {
    const int m = s.size();

    // Build new string
    auto idxs = vector<int>(m + 1);
    string s2;
    s2.reserve(m);
    for (int i = 0; i < m; ++i) {
      idxs[i] = s2.size();
      if (s[i] == '0') continue;
      s2.push_back(s[i]);
    }
    idxs[m] = s2.size();
    const int n = s2.size();

    // Prefix sums
    auto sums = vector<int64_t>(n + 1);
    auto nums = vector<int64_t>(n + 1);
    auto units = vector<int64_t>(n + 1);
    units[0] = 1;
    for (int i = 0; i < n; ++i) {
      int digit = s2[i] - '0';
      sums[i + 1] = mod(sums[i] + digit);
      nums[i + 1] = mod(nums[i] * 10 + digit);
      units[i + 1] = mod(units[i] * 10);
    }

    // Query
    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (const vector<int>& query : queries) {
      int l = idxs[query[0]], r = idxs[query[1] + 1];
      int64_t sum = mod(sums[r] - sums[l]);
      int64_t num = mod(nums[r] - nums[l] * units[r - l]);
      ans.push_back(mod(sum * num));
    }

    return ans;
  }
};
