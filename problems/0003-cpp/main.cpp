// Source: https://leetcode.com/problems/longest-substring-without-repeating-characters
// Title: Longest Substring Without Repeating Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, find the length of the **longest substring** without duplicate characters.
//
// **Example 1:**
//
// ```
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3. Note that `"bca"` and `"cab"` are also correct answers.
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
#include <vector>

using namespace std;

// Sliding Window + Hash Map (Array)
//
// Store the last index of each letter.
class Solution {
 public:
  int lengthOfLongestSubstring(const string &s) {
    const int n = s.size();

    auto lastIdxs = vector<int>(128, -1);  // -1 means no occurrence

    int maxLen = 0;     // max substring length
    int startIdx = -1;  // (startIdx, i] is current substring
    for (int i = 0; i < n; ++i) {
      char ch = s[i];
      startIdx = max(startIdx, lastIdxs[ch]);
      maxLen = max(maxLen, i - startIdx);
      lastIdxs[ch] = i;
    }

    return maxLen;
  }
};
