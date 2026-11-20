// Source: https://leetcode.com/problems/longest-balanced-substring-ii
// Title: Longest Balanced Substring II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` consisting only of the characters `'a'`, `'b'`, and `'c'`.
//
// A **substring** of `s` is called **balanced** if all **distinct** characters in the **substring** appear the **same** number of times.
//
// Return the **length of the longest balanced substring** of `s`.
//
// **Example 1:**
//
// ```
// Input: s = "abbac"
// Output: 4
// Explanation:
// The longest balanced substring is `"abba"` because both distinct characters `'a'` and `'b'` each appear exactly 2 times.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aabcc"
// Output: 3
// Explanation:
// The longest balanced substring is `"abc"` because all distinct characters `'a'`, `'b'` and `'c'` each appear exactly 1 time.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "aba"
// Output: 2
// Explanation:
// One of the longest balanced substrings is `"ab"` because both distinct characters `'a'` and `'b'` each appear exactly 1 time. Another longest balanced substring is `"ba"`.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` contains only the characters `'a'`, `'b'`, and `'c'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <string>
#include <unordered_map>

using namespace std;

// Hash Map + Prefix Sum
//
// Try all possible combination of the letters.
//
// Denote #a be the number of in a given range.
//
// **Case 1**: the substring contains only 1 unique letter.
// We just loop through the string and find maximum contiguous letters.
//
// **Case 2**: the substring contains only 2 unique letter2.
// Run 3 possible kind of substrings (a+b, b+c, a+c).
//
// Use a+b as an example.
// Denote D[i] be the `#a-#b` in [0, i).
// We first notice that in every valid substring [i, j), we have D[i] = D[j].
// We store the reverse map D[i] -> i in a hashmap (only keep the smallest i).
// Then for each j, we can easily find the longest valid substring.
//
// However, since #c must be zero in [i, j),
// we will clear the hashmap whenever we see any `c`.
//
// **Case3**: the substring contains only 2 unique letter3.
// Using the same idea as above.
// We use store the pair <`#a-#b`, `#a-#c`> in the hashmap.
//
// **Note**:
// In case 2, instead of reset the hashmap, we can use <`#a-#b`, `#c`> has key instead.
class Solution {
 public:
  int longestBalanced(string s) {
    return max({
        longestBalanced1(s),
        longestBalanced23(s),
    });
  }

  // 1 unique letter
  int longestBalanced1(string &s) {
    int n = s.size();

    int maxLen = 0, currLen = 0;
    char prevCh = ' ';
    for (const auto ch : s) {
      // Reset substring
      if (ch != prevCh) {
        currLen = 0;
      }

      ++currLen;
      maxLen = max(maxLen, currLen);
      prevCh = ch;
    }

    return maxLen;
  }

  // 2 & 3 unique letters
  int longestBalanced23(string &s) {
    int n = s.size();
    int maxLen = 0;

    // Helper
    const auto key = [](uint32_t high, uint32_t low) -> uint64_t {  //
      return uint64_t(high) << 32 | uint64_t(low);
    };

    const auto getLenOrSetIdx = [&maxLen](unordered_map<uint64_t, int> &idxMap, const uint64_t key, const int currIdx) {
      if (idxMap.contains(key)) {
        maxLen = max(maxLen, currIdx - idxMap[key]);
      } else {
        idxMap[key] = currIdx;
      }
    };

    // Init hash map
    auto idxMapAB = unordered_map<uint64_t, int>();   // (#a-#b, #c) of [0, i] -> i
    auto idxMapBC = unordered_map<uint64_t, int>();   // (#a-#c, #b) of [0, i] -> i
    auto idxMapAC = unordered_map<uint64_t, int>();   // (#b-#c, #a) of [0, i] -> i
    auto idxMapABC = unordered_map<uint64_t, int>();  // (#a-#b, #a-#c) of [0, i] -> i
    idxMapAB.reserve(n);
    idxMapBC.reserve(n);
    idxMapAC.reserve(n);
    idxMapABC.reserve(n);
    idxMapAB[0] = -1;
    idxMapAC[0] = -1;
    idxMapBC[0] = -1;
    idxMapABC[0] = -1;

    // Loop
    int countA = 0, countB = 0, countC = 0;
    for (auto i = 0; i < n; ++i) {
      const char ch = s[i];

      if (ch == 'a') {
        ++countA;
      } else if (ch == 'b') {
        ++countB;
      } else {  // ch == 'c'
        ++countC;
      }

      const uint64_t keyAB = key(countA - countB, countC);
      const uint64_t keyBC = key(countB - countC, countA);
      const uint64_t keyAC = key(countA - countC, countB);
      const uint64_t keyABC = key(countA - countB, countA - countC);

      // Update
      getLenOrSetIdx(idxMapAB, keyAB, i);
      getLenOrSetIdx(idxMapBC, keyBC, i);
      getLenOrSetIdx(idxMapAC, keyAC, i);
      getLenOrSetIdx(idxMapABC, keyABC, i);
    }

    return maxLen;
  }
};
