// Source: https://leetcode.com/problems/maximize-active-section-with-trade-i
// Title: Maximize Active Section with Trade I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a binary string `s` of length `n`, where:
//
// - `'1'` represents an **active** section.
// - `'0'` represents an **inactive** section.
//
// You can perform **at most one trade** to maximize the number of active sections in `s`. In a trade, you:
//
// - Convert a contiguous block of `'1'`s that is surrounded by `'0'`s to all `'0'`s.
// - Afterward, convert a contiguous block of `'0'`s that is surrounded by `'1'`s to all `'1'`s.
//
// Return the **maximum** number of active sections in `s` after making the optimal trade.
//
// **Note:** Treat `s` as if it is **augmented** with a `'1'` at both ends, forming `t = '1' + s + '1'`. The augmented `'1'`s **do not** contribute to the final count.
//
// **Example 1:**
//
// ```
// Input: s = "01"
// Output: 1
// Explanation:
// Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 1.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "0100"
// Output: 4
// Explanation:
// - String `"0100"` → Augmented to `"101001"`.
// - Choose `"0100"`, convert `"10**1**001"` → `"1**0000**1"` → `"1**1111**1"`.
// - The final string without augmentation is `"1111"`. The maximum number of active sections is 4.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "1000100"
// Output: 7
// Explanation:
// - String `"1000100"` → Augmented to `"110001001"`.
// - Choose `"000100"`, convert `"11000**1**001"` → `"11**000000**1"` → `"11**111111**1"`.
// - The final string without augmentation is `"1111111"`. The maximum number of active sections is 7.
// ```
//
// **Example 4:**
//
// ```
// Input: s = "01010"
// Output: 4
// Explanation:
// - String `"01010"` → Augmented to `"1010101"`.
// - Choose `"010"`, convert `"10**1**0101"` → `"1**000**101"` → `"1**111**101"`.
// - The final string without augmentation is `"11110"`. The maximum number of active sections is 4.
// ```
//
// **Constraints:**
//
// - `1 <= n == s.length <= 10^5`
// - `s[i]` is either `'0'` or `'1'`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Sliding Window
//
// First count the number of ones.
// Next convert the string into blocks.
//
// Now find the maximum sum of any two contiguous blocks.
// If exist, add the result to the answer.
class Solution {
 public:
  int maxActiveSectionsAfterTrade(const string &s) {
    const int n = s.size();

    // Total ones
    int ones = count(s.cbegin(), s.cend(), '1');

    // Convert to block
    auto blocks = vector<int>();
    blocks.reserve(s.size());
    char prevCh = ' ';
    int block = 0;
    for (int i = 0; i <= n; ++i) {
      char ch = (i == n) ? '1' : s[i];  // end sentinel is 1
      if (ch != prevCh) {
        if (ch == '1' && block > 0) {  // new 1-block, complete previous 0-block
          blocks.push_back(block);
        }
        block = 0;  // reset
      }

      prevCh = ch;
      ++block;
    }
    const int m = blocks.size();

    // Find contiguous sum
    int zeros = 0;
    for (int i = 1; i < m; ++i) {
      zeros = max(zeros, blocks[i - 1] + blocks[i]);
    }

    return ones + zeros;
  }
};

// Sliding Window
//
// Instead of converting to block,
// we can do the sidling window on the fly.
class Solution2 {
 public:
  int maxActiveSectionsAfterTrade(const string &s) {
    const int n = s.size();

    // Total ones
    int ones = count(s.cbegin(), s.cend(), '1');

    // Loop
    char prevCh = ' ';
    int maxZeros = 0;
    int prevBlock = 0, currBlock = 0;
    for (int i = 0; i <= n; ++i) {
      char ch = (i == n) ? '1' : s[i];  // end sentinel is 1
      if (ch != prevCh) {
        if (ch == '1' && currBlock > 0) {  // new 1-block, complete previous 0-block
          if (prevBlock > 0) {             // previous block exist
            maxZeros = max(maxZeros, prevBlock + currBlock);
          }
          prevBlock = currBlock;
        }
        currBlock = 0;  // reset
      }

      prevCh = ch;
      ++currBlock;
    }

    return ones + maxZeros;
  }
};

// Sliding Window
class Solution3 {
 public:
  int maxActiveSectionsAfterTrade(const string &s) {
    const int n = s.size();

    // Total ones
    int ones = count(s.cbegin(), s.cend(), '1');

    // Loop
    int maxZeros = 0;
    int prevBlock = 0;
    auto it0 = find(s.cbegin(), s.cend(), '0');  // find first 0
    while (it0 != s.cend()) {
      auto it1 = find(it0, s.cend(), '1');  // find next 1
      int currBlock = it1 - it0;

      if (prevBlock > 0) {  // previous block exist
        maxZeros = max(maxZeros, prevBlock + currBlock);
      }
      prevBlock = currBlock;

      it0 = find(it1, s.cend(), '0');  // find next 0
    }

    return ones + maxZeros;
  }
};
