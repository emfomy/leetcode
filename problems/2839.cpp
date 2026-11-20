// Source: https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i
// Title: Check if Strings Can be Made Equal With Operations I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two strings `s1` and `s2`, both of length `4`, consisting of **lowercase** English letters.
//
// You can apply the following operation on any of the two strings **any** number of times:
//
// - Choose any two indices `i` and `j` such that `j - i = 2`, then **swap** the two characters at those indices in the string.
//
// Return `true` if you can make the strings `s1` and `s2` equal, and `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: s1 = "abcd", s2 = "cdab"
// Output: true
// Explanation: We can do the following operations on s1:
// - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbad".
// - Choose the indices i = 1, j = 3. The resulting string is s1 = "cdab" = s2.
// ```
//
// **Example 2:**
//
// ```
// Input: s1 = "abcd", s2 = "dacb"
// Output: false
// Explanation: It is not possible to make the two strings equal.
// ```
//
// **Constraints:**
//
// - `s1.length == s2.length == 4`
// - `s1` and `s2` consist only of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
  bool canBeEqual(const string& s1, const string& s2) {
    const int n = s1.size();

    // Count
    Sets sets1 = {}, sets2 = {};
    for (int i = 0; i < n; ++i) {
      ++sets1[i % 2][s1[i]];
      ++sets2[i % 2][s2[i]];
    }

    return sets1 == sets2;
  }
};

class Solution2 {
 public:
  bool canBeEqual(const string& s1, const string& s2) {
    return ((s1[0] == s2[0] && s1[2] == s2[2]) || (s1[0] == s2[2] && s1[2] == s2[0])) &&  // even
           ((s1[1] == s2[1] && s1[3] == s2[3]) || (s1[1] == s2[3] && s1[3] == s2[1]));    // odd
  }
};
