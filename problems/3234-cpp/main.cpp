// Source: https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones
// Title: Count the Number of Substrings With Dominant Ones
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a binary string `s`.
//
// Return the number of **substrings** with **dominant** ones.
//
// A **substring** is a contiguous **non-empty** sequence of characters within a string.
//
// A string has **dominant** ones if the number of ones in the string is **greater than or equal to** the **square** of the number of zeros in the string.
//
// **Example 1:**
//
// ```
// Input: s = "00011"
// Output: 5
// Explanation:
// The substrings with dominant ones are shown in the table below.
//
// i   j   s[i..j]   Number of Zeros   Number of Ones
// 3   3   1         0                 1
// 4   4   1         0                 1
// 2   3   01        1                 1
// 3   4   11        0                 2
// 2   4   011       1                 2
// ```
//
// <table><thead><tr><th>i</th><th>j</th><th>s[i..j]</th><th>Number of Zeros</th><th>Number of Ones</th></tr></thead><tbody><tr><td>3</td><td>3</td><td>1</td><td>0</td><td>1</td></tr><tr><td>4</td><td>4</td><td>1</td><td>0</td><td>1</td></tr><tr><td>2</td><td>3</td><td>01</td><td>1</td><td>1</td></tr><tr><td>3</td><td>4</td><td>11</td><td>0</td><td>2</td></tr><tr><td>2</td><td>4</td><td>011</td><td>1</td><td>2</td></tr></tbody></table>
//
// **Example 2:**
//
// ```
// Input: s = "101101"
// Output: 16
// Explanation:
// The substrings with **non-dominant** ones are shown in the table below.
// Since there are 21 substrings total and 5 of them have non-dominant ones, it follows that there are 16 substrings with dominant ones.
//
// i   j   s[i..j]   Number of Zeros   Number of Ones
// 1   1   0         1                 0
// 4   4   0         1                 0
// 1   4   0110      2                 2
// 0   4   10110     2                 3
// 1   5   01101     2                 3
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 4 * 10^4`
// - `s` consists only of characters `'0'` and `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Prefix Sum + Binary Search
//
// Loop for all possible substring with x zeros.
// Note that x < sqrt(n).
// For each x, the substring must be at least length x+x^2.
// Now loop for all possible start, use binary search to count valid substrings.
//
// Note that we can't use above trick for x=0, since
// 1. x+x^2 = 0 is might cause empty string
// 2. binary search might fail.
// However it is easy to count string with all ones.
class Solution {
 public:
  int numberOfSubstrings(string s) {
    int n = s.size();
    auto sqn = int(sqrt(n));
    auto ans = 0;

    // Prefix Count zeros
    auto prefix = vector<int>(n + 1);  // zeros in s[0..i]
    for (auto i = 0; i < n; ++i) {
      prefix[i + 1] = prefix[i] + (s[i] == '0');
    }

    // Count substrings with all ones
    auto ones = 0;
    for (auto i = 0; i < n; ++i) {
      if (s[i] == '1') {
        ans += (++ones);
      } else {
        ones = 0;
      }
    }

    // Count other substrings
    for (auto x = 1; x < sqn; ++x) {
      auto minLen = x + x * x;
      for (auto l = 0; l <= n - minLen; ++l) {
        auto [minIt, maxIt] = equal_range(prefix.cbegin() + l + minLen, prefix.cend(), prefix[l] + x);
        ans += maxIt - minIt;
      }
    }

    return ans;
  }
};

// Sliding Window
//
// We first find all the zeros.
// For each x, loop for [l, r) by keeping x zeros.
class Solution2 {
 public:
  int numberOfSubstrings(string s) {
    int n = s.size();
    auto ans = 0;
    auto sqn = int(sqrt(n));

    // Find zeros
    auto zeros = vector<int>();
    for (auto i = 0; i < n; ++i) {
      if (s[i] == '0') zeros.push_back(i);
    }
    int z = zeros.size();  // total zeros
    zeros.push_back(n);

    // Count substrings with all ones
    auto ones = 0;
    for (auto i = 0; i < n; ++i) {
      if (s[i] == '0') {
        ones = 0;
      } else {
        ++ones;
        ans += ones;
      }
    }

    // Count other substrings
    auto maxX = min(sqn, z);
    for (auto x = 1; x <= maxX; ++x) {
      auto minLen = x + x * x;
      auto zid = 0;  // the first zero
      for (auto l = 0; l <= n - minLen; ++l) {
        // Ensure zeros[zid] >= l
        while (zid + x <= z && zeros[zid] < l) ++zid;
        if (zid + x > z) break;

        // Count substrings [l, r] (inclusive)
        auto minR = max(zeros[zid + x - 1], l + minLen - 1);
        auto maxR = zeros[zid + x];
        ans += max(maxR - minR, 0);
      }
    }

    return ans;
  }
};
