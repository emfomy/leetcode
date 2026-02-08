// Source: https://leetcode.com/problems/strings-differ-by-one-character
// Title: Strings Differ by One Character
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a list of strings `dict` where all the strings are of the same length.
//
// Return `true` if there are 2 strings that only differ by 1 character in the same index, otherwise return `false`.
//
// **Example 1:**
//
// ```
// **Input:** dict = ["abcd","acbd", "aacd"]
// **Output:** true
// **Explanation:** Strings "a**b**cd" and "a**a**cd" differ only by one character in the index 1.
// ```
//
// **Example 2:**
//
// ```
// **Input:** dict = ["ab","cd","yz"]
// **Output:** false
// ```
//
// **Example 3:**
//
// ```
// **Input:** dict = ["abcd","cccc","abyd","abab"]
// **Output:** true
// ```
//
// **Constraints:**
//
// - The number of characters in `dict <= 10^5`
// - `dict[i].length == dict[j].length`
// - `dict[i]` should be unique.
// - `dict[i]` contains only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstdint>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// Rolling Hash + Hash Set
//
// Here we use the little-endian hash.
//
// We first precompute all the hash of each string.
//
// Next loop through all possible differ index.
// For each index, loop through all string.
// We substract the hash of that index from the string hash.
// We put the hash into a hash set.
// If the hash is already in the set, then the result is true.
class Solution {
  constexpr static int64_t M1 = 1e9 + 7;
  constexpr static int64_t M2 = 1e9 + 9;

  constexpr static int64_t B1 = 131;
  constexpr static int64_t B2 = 13331;

  // Compute x mod m
  inline int64_t mod(int64_t x, int64_t m) { return ((x % m) + m) % m; }

 public:
  bool differByOne(vector<string>& dict) {
    int n = dict.size(), l = dict[0].size();

    // Compute hashs of all string
    auto strHash1s = vector<int64_t>(n);
    auto strHash2s = vector<int64_t>(n);
    for (int i = 0; i < n; ++i) {
      int64_t hash1 = 0, hash2 = 0;
      int64_t B1i = 1, B2i = 1;  // B^i
      for (auto ch : dict[i]) {
        hash1 = mod(hash1 + ch * B1i, M1);
        hash2 = mod(hash2 + ch * B2i, M2);
        B1i = mod(B1i * B1, M1);
        B2i = mod(B2i * B2, M2);
      }
      strHash1s[i] = hash1;
      strHash2s[i] = hash2;
    }

    // We concat two hashs since the value range of each hash is only 32-bit
    auto hashSet = unordered_set<int64_t>();
    hashSet.reserve(n);

    // Loop through all possible differ index
    int64_t B1i = 1, B2i = 1;  // B^i
    for (int skipIdx = 0; skipIdx < l; ++skipIdx) {
      hashSet.clear();

      // Loop through the strings and compute the hash
      for (auto i = 0; i < n; ++i) {
        auto hash1 = mod(strHash1s[i] - dict[i][skipIdx] * B1i, M1);
        auto hash2 = mod(strHash2s[i] - dict[i][skipIdx] * B2i, M2);

        auto hash = hash1 << 32 | hash2;
        if (hashSet.contains(hash)) return true;
        hashSet.insert(hash);
      }

      B1i = mod(B1i * B1, M1);
      B2i = mod(B2i * B2, M2);
    }

    return false;
  }
};
