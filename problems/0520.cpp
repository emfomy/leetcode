// Source: https://leetcode.com/problems/detect-capital
// Title: Detect Capital
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// We define the usage of capitals in a word to be right when one of the following cases holds:
//
// - All letters in this word are capitals, like `"USA"`.
// - All letters in this word are not capitals, like `"leetcode"`.
// - Only the first letter in this word is capital, like `"Google"`.
//
// Given a string `word`, return `true` if the usage of capitals in it is right.
//
// **Example 1:**
//
// ```
// Input: word = "USA"
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: word = "FlaG"
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= word.length <= 100`
// - `word` consists of lowercase and uppercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

class Solution {
 public:
  bool detectCapitalUse(string word) {
    int n = word.size();
    auto numUpper = count_if(word.cbegin(), word.cend(), [](auto c) { return isupper(c); });
    return numUpper == 0 || numUpper == n || (numUpper == 1 && isupper(word[0]));
  }
};
