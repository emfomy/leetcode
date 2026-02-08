// Source: https://leetcode.com/problems/minimum-deletions-to-make-string-balanced
// Title: Minimum Deletions to Make String Balanced
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` consisting only of characters `'a'` and `'b'`​​​​.
//
// You can delete any number of characters in `s` to make `s` **balanced**. `s` is **balanced** if there is no pair of indices `(i,j)` such that `i < j` and `s[i] = 'b'` and `s[j]= 'a'`.
//
// Return the **minimum** number of deletions needed to make `s` **balanced**.
//
// **Example 1:**
//
// ```
// **Input:** s = "aababbab"
// **Output:** 2
// **Explanation:** You can either:
// Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
// Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
// ```
//
// **Example 2:**
//
// ```
// **Input:** s = "bbaaaaabb"
// **Output:** 2
// **Explanation:** The only solution is to delete the first two characters.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s[i]` is`'a'` or `'b'`​​.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <string>
#include <vector>

using namespace std;

// Three Pass
//
// Loop through the string, and compute the number of `b` before each index.
// Also compute the number of `a` after each index.
//
// Finally check all index and find the minimal sum of above values.
class Solution {
 public:
  int minimumDeletions(string s) {
    int n = s.size();

    // Count A
    auto postAs = vector<int>(n + 1);
    for (int i = n - 1; i >= 0; --i) {
      postAs[i] = postAs[i + 1] + (s[i] == 'a');
    }

    // Count B
    auto preBs = vector<int>(n + 1);
    for (int i = 0; i < n; ++i) {
      preBs[i + 1] = preBs[i] + (s[i] == 'b');
    }

    // Answer
    int ans = INT_MAX;
    for (int i = 0; i <= n; ++i) {
      ans = min(ans, postAs[i] + preBs[i]);
    }

    return ans;
  }
};

// Two Pass
//
// First count the number of `a`.
//
// Next loop though the string, count the number of `a` and `b` before each index.
// We use total count & prefix count to compute the suffix count of `a`.
//
// Finally check all index and infd the minimal count of suffix `a` and prefix `b`.
class Solution2 {
 public:
  int minimumDeletions(string s) {
    int n = s.size();

    // Count total A
    int totalA = count(s.cbegin(), s.cend(), 'a');

    // Count prefix and find answer
    int postA = totalA, preB = 0;
    int ans = postA + preB;
    for (int i = 0; i < n; ++i) {  // prefix count of [0, i]
      postA -= (s[i] == 'a');
      preB += (s[i] == 'b');
      ans = min(ans, postA + preB);
    }

    return ans;
  }
};

// One Pass
//
// We can compute the total count of a along with the prefix/suffix.
// The answer of each index is:
// postA + preB = (totalA - preA) + preB = totalA + (preB - preA)
//
// We can find the minimal of (preB - preA), and add with totalA to get the answer.
class Solution3 {
 public:
  int minimumDeletions(string s) {
    int n = s.size();

    // Count prefix and find answer
    int preA = 0, preB = 0;
    int minDiff = 0;
    for (int i = 0; i < n; ++i) {  // prefix count of [0, i]
      preA += (s[i] == 'a');
      preB += (s[i] == 'b');
      minDiff = min(minDiff, preB - preA);
    }

    return preA + minDiff;  // preA = totalA here
  }
};
