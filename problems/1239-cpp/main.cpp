// Source: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters
// Title: Maximum Length of a Concatenated String with Unique Characters
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of strings `arr`. A string `s` is formed by the **concatenation** of a **subsequence** of `arr` that has **unique characters**.
//
// Return the **maximum** possible length of `s`.
//
// A **subsequence** is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// **Example 1:**
//
// ```
// Input: arr = ["un","iq","ue"]
// Output: 4
// Explanation: All the valid concatenations are:
// - ""
// - "un"
// - "iq"
// - "ue"
// - "uniq" ("un" + "iq")
// - "ique" ("iq" + "ue")
// Maximum length is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: arr = ["cha","r","act","ers"]
// Output: 6
// Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").
// ```
//
// **Example 3:**
//
// ```
// Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
// Output: 26
// Explanation: The only string in arr has all 26 characters.
// ```
//
// **Constraints:**
//
// - `1 <= arr.length <= 16`
// - `1 <= arr[i].length <= 26`
// - `arr[i]` contains only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

using namespace std;

// Bit Mask + Back tracking + Memo
//
// For each string, compute the bit mask of letters.
// Next backtrack all possible combinations.
class Solution {
  using Mask = bitset<26>;
  Mask getMask(string_view sv) {
    Mask mask;
    for (char ch : sv) {
      if (mask.test(ch - 'a')) return {};  // empty mask
      mask.set(ch - 'a');
    }
    return mask;
  }

  using MemoKey = int64_t;
  using Memo = unordered_set<MemoKey>;
  static MemoKey memoHash(const Mask mask, const int idx) {  //
    return (mask.to_ullong() << 32) | idx;
  }

 public:
  int maxLength(const vector<string>& arr) {
    // Prepare masks
    auto masks = vector<Mask>();
    masks.reserve(arr.size());
    for (const string& str : arr) {
      Mask mask = getMask(str);
      if (mask.any()) masks.push_back(mask);
    }

    // Dedup
    const auto comp = [](const Mask& a, const Mask& b) -> bool { return a.to_ulong() < b.to_ulong(); };
    sort(masks.begin(), masks.end(), comp);
    masks.erase(unique(masks.begin(), masks.end()), masks.cend());
    const int n = masks.size();

    // Backtracking
    int ans = 0;
    Memo memo;
    backtrack(masks, 0, Mask{}, ans, memo);

    return ans;
  }

 private:
  void backtrack(const vector<Mask>& masks, int idx, Mask mask, int& ans, Memo& memo) {
    // End loop
    const int n = masks.size();
    if (idx >= n) return;

    // Update memo
    MemoKey memoKey = memoHash(mask, idx);
    if (memo.contains(memoKey)) return;
    memo.insert(memoKey);

    // Skip this string
    backtrack(masks, idx + 1, mask, ans, memo);

    // Use this string
    if ((mask & masks[idx]).none()) {
      mask |= masks[idx];
      ans = max(ans, static_cast<int>(mask.count()));
      backtrack(masks, idx + 1, mask, ans, memo);
    }
  }
};
