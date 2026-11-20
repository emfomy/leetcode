// Source: https://leetcode.com/problems/lexicographically-smallest-palindromic-permutation-greater-than-target
// Title: Lexicographically Smallest Palindromic Permutation Greater Than Target
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two strings `s` and `target`, each of length `n`, consisting of lowercase English letters.
//
// Return the **lexicographically smallest string** that is **both** a **palindromic permutation** of `s` and **strictly** greater than `target`. If no such permutation exists, return an empty string.
//
// **Example 1:**
//
// ```
// Input: s = "baba", target = "abba"
// Output: "baab"
// Explanation:
// - The palindromic permutations of `s` (in lexicographical order) are `"abba"` and `"baab"`.
// - The lexicographically smallest permutation that is strictly greater than `target` is `"baab"`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "baba", target = "bbaa"
// Output: ""
// Explanation:
// - The palindromic permutations of `s` (in lexicographical order) are `"abba"` and `"baab"`.
// - None of them is lexicographically strictly greater than `target`. Therefore, the answer is `""`.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "abc", target = "abb"
// Output: ""
// Explanation:
// `s` has no palindromic permutations. Therefore, the answer is `""`.
// ```
//
// **Example 4:**
//
// ```
// Input: s = "aac", target = "abb"
// Output: "aca"
// Explanation:
// - The only palindromic permutation of `s` is `"aca"`.
// - `"aca"` is strictly greater than `target`. Therefore, the answer is `"aca"`.
// ```
//
// **Constraints:**
//
// - `1 <= n == s.length == target.length <= 300`
// - `s` and `target` consist of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>

using namespace std;

// Greedy
//
// First count the letter frequency of `s`,
// and check if it has palindromic permutation.
//
// Next loop through the letters in `target`.
// Note that we only need to loop for the first half.
//
// For each letter, pick the same letter if possible.
// After that, we try to form the maximum string with the rest of the letters,
// ensuring that we can form a greater permutation.
//
// If there is no such letter or we can't from a greater permutation,
// pick the smallest letter that is greater than the current letter.
// After that, we pick the smallest letters (no constraint) for the rest.
class Solution {
 public:
  string lexPalindromicPermutation(const string& s, const string& target) {
    const int n = s.size();
    const int m = n / 2;
    string ans;
    ans.reserve(n);

    // Edge case: only one letter
    if (n == 1 && s[0] <= target[0]) return "";

    // Frequency
    auto freq = array<int, 128>();
    for (const char ch : s) ++freq[ch];

    // Check palindromic
    char oddCh = '\0';
    for (int ch = 'a'; ch <= 'z'; ++ch) {
      if (freq[ch] % 2 == 1) {
        if (oddCh) return "";
        oddCh = ch;
      }
      freq[ch] /= 2;
    }

    // Helper
    auto canFormGreater = [n, oddCh, &target, &freq, &ans](int i) -> bool {
      // Check first half
      for (char ch = 'z'; ch >= 'a'; --ch) {
        for (int f = 0; f < freq[ch]; ++f) {
          ++i;
          if (ch > target[i]) return true;
          if (ch < target[i]) return false;
        }
      }

      // Check middle
      if (oddCh) {
        ++i;
        if (oddCh > target[i]) return true;
        if (oddCh < target[i]) return false;
      }

      // Check last half
      for (char ch = 'a'; ch <= 'z'; ++ch) {
        for (int f = 0; f < freq[ch]; ++f) {
          ++i;
          if (ch > target[i]) return true;
          if (ch < target[i]) return false;
        }
      }

      // Check filled letters
      for (++i; i < n; ++i) {
        char ch = ans[n - 1 - i];
        if (ch > target[i]) return true;
        if (ch < target[i]) return false;
      }

      return false;  // equal to target
    };

    // Backtrack
    for (int i = 0; i < m; i++) {
      const char ch = target[i];  // current letter

      // Pick the same letter
      if (freq[ch] > 0) {
        --freq[ch];
        ans.push_back(ch);
        if (canFormGreater(i)) continue;

        // can't pick, backtrack
        ans.pop_back();
        ++freq[ch];
      }

      // Pick greater letter
      auto it = find_if(freq.cbegin() + ch + 1, freq.cend(), [](int x) -> bool { return x > 0; });
      if (it == freq.cend()) return "";  // no solution
      char c = it - freq.cbegin();
      --freq[c];
      ans.push_back(c);
      break;
    }

    // Fill the rest
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      for (int f = 0; f < freq[ch]; ++f) {
        ans.push_back(ch);
      }
    }
    if (oddCh) ans.push_back(oddCh);
    for (int j = m - 1; j >= 0; --j) ans.push_back(ans[j]);

    return ans;
  }
};
