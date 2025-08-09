// Source: https://leetcode.com/problems/longest-substring-without-repeating-characters
// Title: Longest Substring Without Repeating Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, find the length of the **longest substring** without duplicate characters.
//
// A **substring** is a contiguous **non-empty** sequence of characters within a string.
//
// **Example 1:**
//
// ```
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3.
// Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
// ```
//
// **Constraints:**
//
// - `0 <= s.length <= 5 * 10^4`
// - `s` consists of English letters, digits, symbols and spaces.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <unordered_map>

using namespace std;

// Use Sliding Window & Hash Map
class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    int n = s.size();

    unordered_map<char, int> counter;
    int left = 0;
    int right = 0;
    int ans = 0;
    while (right < n) {
      if (counter[s[right]] > 0) {
        counter[s[left]]--;
        left++;
      } else {
        counter[s[right]]++;
        right++;
      }
      ans = max(ans, right - left);
    }

    return ans;
  }
};
