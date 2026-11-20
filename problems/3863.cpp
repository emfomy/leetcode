// Source: https://leetcode.com/problems/minimum-operations-to-sort-a-string
// Title: Minimum Operations to Sort a String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` consisting of lowercase English letters.
//
// In one operation, you can select any **<button>substring</button>** of `s` that is **not** the entire string and **sort** it in **non-descending alphabetical** order.
//
// Return the **minimum** number of operations required to make `s` sorted in **non-descending** order. If it is not possible, return -1.
//
// **Example 1:**
//
// ```
// Input: s = "dog"
// Output: 1
// Explanation:
// - Sort substring `"og"` to `"go"`.
// - Now, `s = "dgo"`, which is sorted in ascending order. Thus, the answer is 1.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "card"
// Output: 2
// Explanation:
// - Sort substring `"car"` to `"acr"`, so `s = "acrd"`.
// - Sort substring `"rd"` to `"dr"`, making `s = "acdr"`, which is sorted in ascending order. Thus, the answer is 2.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "gf"
// Output: -1
// Explanation:
// - It is impossible to sort `s` under the given constraints. Thus, the answer is -1.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` consists of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>

using namespace std;

// Intuition
//
// We can sort twice: [0, n-1) and [1, n).
// If min at front or max at back, then only one sort is needed.
// If exist min or max at [1, n-1), then two sorts are needed.
// Otherwise, three sorts are needed.
class Solution {
 public:
  int minOperations(const string &s) {
    const int n = s.size();

    // Trivial
    if (is_sorted(s.cbegin(), s.cend())) return 0;
    if (n == 2) return -1;

    // Find min and max
    const auto [minIt, maxIt] = minmax_element(s.cbegin(), s.cend());
    const char minCh = *minIt, maxCh = *maxIt;

    // Case
    if (s.front() == minCh || s.back() == maxCh) return 1;
    if (any_of(s.cbegin() + 1, s.cend() - 1, [minCh, maxCh](char ch) { return ch == minCh || ch == maxCh; })) {
      return 2;
    }
    return 3;
  }
};
