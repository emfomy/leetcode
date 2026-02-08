// Source: https://leetcode.com/problems/number-of-substrings-containing-all-three-characters
// Title: Number of Substrings Containing All Three Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`consisting only of characters a, b and c.
//
// Return the number of substrings containing **at least** one occurrence of all these characters a, b and c.
//
// **Example 1:**
//
// ```
// Input: s = "abcabc"
// Output: 10
// Explanation: The substrings containingat leastone occurrence of the charactersa,bandc are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (**again**).
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aaacb"
// Output: 3
// Explanation: The substrings containingat leastone occurrence of the charactersa,bandc are "aaacb", "aacb" and "acb".
// ```
//
// **Example 3:**
//
// ```
// Input: s = "abc"
// Output: 1
// ```
//
// **Constraints:**
//
// - `3 <= s.length <= 5 x 10^4`
// - `s`only consists ofa, b or ccharacters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Slicing Window
class Solution {
 public:
  int numberOfSubstrings(string s) {
    int n = s.size();

    auto ans = 0;
    auto counts = vector<int>(3);
    auto l = 0, r = 0;  // [l, r]
    while (r < n) {
      ++counts[s[r] - 'a'];
      while (l < r && counts[0] > 0 && counts[1] > 0 && counts[2] > 0) {
        ans += n - r;  // all substring start at l and end after r (including) is valid;
        --counts[s[l] - 'a'];
        ++l;
      }
      ++r;
    }

    return ans;
  }
};

// Loop through the string and store the last index of each character.
// For each character, we know find the left index of last abc.
// Say that index is i.
// Then every string start before i (including) and end here is a valid substring.
class Solution2 {
 public:
  int numberOfSubstrings(string s) {
    int n = s.size();

    auto ans = 0;
    auto lastSeen = vector<int>(3, -1);
    for (auto i = 0; i < n; ++i) {
      lastSeen[s[i] - 'a'] = i;
      auto lastIdx = min({lastSeen[0], lastSeen[1], lastSeen[2]});
      ans += lastIdx + 1;
    }

    return ans;
  }
};
