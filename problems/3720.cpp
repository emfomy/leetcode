// Source: https://leetcode.com/problems/lexicographically-smallest-permutation-greater-than-target
// Title: Lexicographically Smallest Permutation Greater Than Target
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two strings `s` and `target`, both having length `n`, consisting of lowercase English letters.
//
// Return the **lexicographically smallest permutation** of `s` that is **strictly** greater than `target`. If no permutation of `s` is lexicographically strictly greater than `target`, return an empty string.
//
// A string `a` is **lexicographically strictly greater**than a string `b` (of the same length) if in the first position where `a` and `b` differ, string `a` has a letter that appears later in the alphabet than the corresponding letter in `b`.
//
// **Example 1:**
//
// ```
// Input: s = "abc", target = "bba"
// Output: "bca"
// Explanation:
// - The permutations of `s` (in lexicographical order) are `"abc"`, `"acb"`, `"bac"`, `"bca"`, `"cab"`, and `"cba"`.
// - The lexicographically smallest permutation that is strictly greater than `target` is `"bca"`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "leet", target = "code"
// Output: "eelt"
// Explanation:
// - The permutations of `s` (in lexicographical order) are `"eelt"`, `"eetl"`, `"elet"`, `"elte"`, `"etel"`, `"etle"`, `"leet"`, `"lete"`, `"ltee"`, `"teel"`, `"tele"`, and `"tlee"`.
// - The lexicographically smallest permutation that is strictly greater than `target` is `"eelt"`.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "baba", target = "bbaa"
// Output: ""
// Explanation:
// - The permutations of `s` (in lexicographical order) are `"aabb"`, `"abab"`, `"abba"`, `"baab"`, `"baba"`, and `"bbaa"`.
// - None of them is lexicographically strictly greater than `target`. Therefore, the answer is `""`.
// ```
//
// **Constraints:**
//
// - `1 <= s.length == target.length <= 300`
// - `s` and `target` consist of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <string>

using namespace std;

// Greedy
//
// First count the letter frequency of `s`.
//
// Next loop through the letters in `target`.
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
  string lexGreaterPermutation(const string& s, const string& target) {
    const int n = s.size();
    string ans;
    ans.reserve(n);

    // Frequency
    auto freq = array<int, 128>();
    for (const char ch : s) ++freq[ch];

    // Helper
    auto canFormGreater = [&target, &freq](int i) -> bool {
      for (char ch = 'z'; ch >= 'a'; --ch) {
        for (int f = 0; f < freq[ch]; ++f) {
          ++i;
          if (ch > target[i]) return true;
          if (ch < target[i]) return false;
        }
      }
      return false;  // equal to target
    };

    // Backtrack
    for (int i = 0; i < n; i++) {
      const char ch = target[i];  // current letter

      // Pick the same letter
      if (freq[ch] > 0) {
        --freq[ch];
        if (canFormGreater(i)) {
          ans.push_back(ch);
          continue;
        }
        ++freq[ch];  // can't pick, backtrack
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

    return ans;
  }
};
