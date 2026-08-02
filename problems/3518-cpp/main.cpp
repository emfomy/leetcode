// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii
// Title: Smallest Palindromic Rearrangement II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **palindromic** string `s` and an integer `k`.
//
// Return the **k-th** **lexicographically smallest** palindromic permutation of `s`. If there are fewer than `k` distinct palindromic permutations, return an empty string.
//
// **Note:** Different rearrangements that yield the same palindromic string are considered identical and are counted once.
//
// **Example 1:**
//
// ```
// Input: s = "abba", k = 2
// Output: "baab"
// Explanation:
// - The two distinct palindromic rearrangements of `"abba"` are `"abba"` and `"baab"`.
// - Lexicographically, `"abba"` comes before `"baab"`. Since `k = 2`, the output is `"baab"`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aa", k = 2
// Output: ""
// Explanation:
// - There is only one palindromic rearrangement: `"aa"`.
// - The output is an empty string since `k = 2` exceeds the number of possible rearrangements.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "bacab", k = 1
// Output: "abcba"
// Explanation:
// - The two distinct palindromic rearrangements of `"bacab"` are `"abcba"` and `"bacab"`.
// - Lexicographically, `"abcba"` comes before `"bacab"`. Since `k = 1`, the output is `"abcba"`.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^4`
// - `s` consists of lowercase English letters.
// - `s` is guaranteed to be palindromic.
// - `1 <= k <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <string>

using namespace std;

// Count + Permutation (TLE)
//
// First count the letters.
// Fill the first half sorted, and find the k-th permutation.
class Solution {
 public:
  string smallestPalindrome(const string &s, int k) {
    const int n = s.size();
    const int halfN = n / 2;

    // Compute frequency
    auto freqs = array<int, 128>();
    for (char ch : s) {
      ++freqs[ch];
    }

    // Find odd letter
    char oddCh = '\0';
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      if (freqs[ch] % 2) {
        oddCh = ch;
      }
      freqs[ch] /= 2;
    }

    // Construct first half
    string ans;
    ans.reserve(n);
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      ans.append(freqs[ch], ch);
    }

    // Permutation
    for (int i = 1; i < k; ++i) {
      bool done = next_permutation(ans.begin(), ans.end());
      if (!done) return "";  // no enough permutation
    }

    // Construct last half
    if (oddCh) ans.push_back(oddCh);
    ans.resize(n);
    for (int i = 0; i < halfN; ++i) {
      ans[n - i - 1] = ans[i];
    }

    return ans;
  }
};

// Count + Permutation
//
// First count the letters.
// Fill the first half sorted, and find the k-th permutation.
//
// Find the permutation using permutation number.
// Idea:
// For each position, loop for each item `x`.
// Let `c` be the number of permutations when we use `x` in this position.
// If k < c, then we can use `x` in this position.
// Otherwise, skip `x` and try next item, also `k -= c`.
class Solution2 {
 public:
  string smallestPalindrome(const string &s, int k) {
    const int n = s.size();
    const int halfN = n / 2;

    // Compute frequency
    auto freqs = array<int, 128>();
    for (char ch : s) {
      ++freqs[ch];
    }

    // Find odd letter
    char oddCh = '\0';
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      if (freqs[ch] % 2) {
        oddCh = ch;
      }
      freqs[ch] /= 2;
    }

    // Multinomial
    // Permutations number for (c1, c2, ..., cm) = n! / c1! c2! ... cm!
    // However, factorial will overflow, we compute using multiple binomial instead.
    // n! / c1! c2! ... cm! = C(c1+c2, c2) * C(c1+c2+c3, c3) * ...
    //
    // Note that for the result greater than k, we don't need exact number.
    // Therefore we will early stop when the result the too large.
    auto countPerms = [&freqs, k]() -> int {
      int64_t total = 1;
      int acc = 0;
      for (int freq : freqs) {
        for (int i = 1; i <= freq; ++i) {
          total = total * (++acc) / i;
          if (total > k) return k + 1;  // early stop
        }
      }
      return total;
    };

    // Construct first half
    string ans;
    ans.reserve(n);
    for (int i = 0; i < halfN; ++i) {
      bool found = false;
      for (char ch = 'a'; ch <= 'z'; ++ch) {  // try each item
        if (freqs[ch] == 0) continue;

        --freqs[ch];  // try to use ch here
        int perms = countPerms();

        // enough permutation, use ch
        if (k <= perms) {
          ans.push_back(ch);
          found = true;
          break;
        }

        // no enough permutation, skip ch
        k -= perms;
        ++freqs[ch];  // put ch back
      }

      if (!found) return "";
    }

    // Construct last half
    if (oddCh) ans.push_back(oddCh);
    ans.resize(n);
    for (int i = 0; i < halfN; ++i) {
      ans[n - i - 1] = ans[i];
    }

    return ans;
  }
};
