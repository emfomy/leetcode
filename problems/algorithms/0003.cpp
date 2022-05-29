// Source: https://leetcode.com/problems/longest-substring-without-repeating-characters/
// Title: Longest Substring Without Repeating Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string, find the length of the longest substring without repeating characters.
//
// Example 1:
//
//   Input: "abcabcbb"
//   Output: 3
//   Explanation: The answer is "abc", with the length of 3.
//
// Example 2:
//
//   Input: "bbbbb"
//   Output: 1
//   Explanation: The answer is "b", with the length of 1.
//
// Example 3:
//
//   Input: "pwwkew"
//   Output: 3
//   Explanation: The answer is "wke", with the length of 3.
//                Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
//
// Constraints:
//
//   0 <= s.length <= 5 * 10^4
//   s consists of English letters, digits, symbols and spaces.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Solution {
 public:
  int lengthOfLongestSubstring( string str ) {
    unordered_set<char> s;
    size_t max_len = 0;
    auto it0 = str.begin(), it1 = str.begin();
    while ( it1 != str.end() ) {
      if ( s.count(*it1) ) {
        s.erase(*it0);
        ++it0;
      } else {
        s.insert(*it1);
        ++it1;
      }
      max_len = max(s.size(), max_len);
    }
    return max_len;
  }
};
