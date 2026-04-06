// Source: https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii
// Title: Check if Strings Can be Made Equal With Operations II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two strings `s1` and `s2`, both of length `n`, consisting of **lowercase** English letters.
//
// You can apply the following operation on **any** of the two strings **any** number of times:
//
// - Choose any two indices `i` and `j` such that `i < j` and the difference `j - i` is **even**, then **swap** the two characters at those indices in the string.
//
// Return `true` if you can make the strings `s1` and `s2` equal, and`false` otherwise.
//
// **Example 1:**
//
// ```
// Input: s1 = "abcdba", s2 = "cabdab"
// Output: true
// Explanation: We can apply the following operations on s1:
// - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbadba".
// - Choose the indices i = 2, j = 4. The resulting string is s1 = "cbbdaa".
// - Choose the indices i = 1, j = 5. The resulting string is s1 = "cabdab" = s2.
// ```
//
// **Example 2:**
//
// ```
// Input: s1 = "abe", s2 = "bea"
// Output: false
// Explanation: It is not possible to make the two strings equal.
// ```
//
// **Constraints:**
//
// - `n == s1.length == s2.length`
// - `1 <= n <= 10^5`
// - `s1` and `s2` consist only of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <string>

using namespace std;

// For first group the letters by index parity.
// The operation can arrange a group into any form.
//
// The problem is true iff. the group sets are equal in both strings.
class Solution {
  using Set = array<int, 128>;
  using Sets = array<Set, 2>;  // even and odd sets

 public:
  bool checkStrings(string s1, string s2) {
    const int n = s1.size();

    // Count
    Sets counts1 = {}, counts2 = {};
    for (int i = 0; i < n; ++i) {
      ++counts1[i % 2][s1[i]];
      ++counts2[i % 2][s2[i]];
    }

    return counts1 == counts2;
  }
};

// Optimized
class Solution2 {
  using Set = array<int, 26>;
  using Sets = array<Set, 2>;  // even and odd sets

 public:
  bool checkStrings(string s1, string s2) {
    const int n = s1.size();

    // Count
    Sets counts = {};
    constexpr Sets zeros = {};
    for (int i = 0; i < n; ++i) {
      ++counts[i % 2][s1[i] - 'a'];
      --counts[i % 2][s2[i] - 'a'];
    }

    return counts == zeros;
  }
};
