// Source: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters
// Title: Smallest Subsequence of Distinct Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, return the **lexicographically smallest subsequence** of `s` that contains all the distinct characters of `s` exactly once.

// **Example 1:**

// ```
// Input: s = "bcabc"
// Output: "abc"
// ```

// **Example 2:**

// ```
// Input: s = "cbacdcbc"
// Output: "acdb"
// ```

// **Constraints:**

// - `1 <= s.length <= 1000`
// - `s` consists of lowercase English letters.

// **Note:** This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>

using namespace std;

// Greedy + Stack
//
// We construct the subsequence from left to right.
//
// For each letter, we append it into the subsequence if it is not in.
//
// However, before appending, we pop the letters from the back.
// If the end letter is larger (i.e. poping will make the subsequence larger),
// and there are still the same letter not processed (i.e. we can still use it later),
// then we pop that end letter.
//
// We use an array of boolean to check if the letter is in the subsequence.
// We use an array of int (counting) to check if there are same letter not processed.
class Solution {
  using Bool = unsigned char;

 public:
  string smallestSubsequence(const string &s) {
    const int n = s.size();

    // Count
    auto count = array<int, 128>();
    for (char ch : s) ++count[ch];

    // Loop
    string ans;
    ans.reserve(26);
    auto used = array<Bool, 128>({});
    for (char ch : s) {
      --count[ch];
      if (used[ch]) continue;

      // Pop larger letters
      while (!ans.empty() && ans.back() > ch && count[ans.back()] > 0) {
        used[ans.back()] = false;
        ans.pop_back();
      }

      // Push current letter
      used[ch] = true;
      ans.push_back(ch);
    }

    return ans;
  }
};
