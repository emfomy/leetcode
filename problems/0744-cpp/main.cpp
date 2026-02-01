// Source: https://leetcode.com/problems/find-smallest-letter-greater-than-target
// Title: Find Smallest Letter Greater Than Target
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of characters `letters` that is sorted in **non-decreasing order**, and a character `target`. There are **at least two different** characters in `letters`.
//
// Return the smallest character in `letters` that is lexicographically greater than `target`. If such a character does not exist, return the first character in `letters`.
//
// **Example 1:**
//
// ```
// Input: letters = ["c","f","j"], target = "a"
// Output: "c"
// Explanation: The smallest character that is lexicographically greater than 'a' in letters is 'c'.
// ```
//
// **Example 2:**
//
// ```
// Input: letters = ["c","f","j"], target = "c"
// Output: "f"
// Explanation: The smallest character that is lexicographically greater than 'c' in letters is 'f'.
// ```
//
// **Example 3:**
//
// ```
// Input: letters = ["x","x","y","y"], target = "z"
// Output: "x"
// Explanation: There are no characters in letters that is lexicographically greater than 'z' so we return letters[0].
// ```
//
// **Constraints:**
//
// - `2 <= letters.length <= 10^4`
// - `letters[i]` is a lowercase English letter.
// - `letters` is sorted in **non-decreasing** order.
// - `letters` contains at least two different characters.
// - `target` is a lowercase English letter.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Binary Search
class Solution {
 public:
  char nextGreatestLetter(vector<char>& letters, char target) {
    auto it = upper_bound(letters.cbegin(), letters.cend(), target);
    return it != letters.cend() ? *it : letters[0];
  }
};

// Binary Search
class Solution2 {
 public:
  char nextGreatestLetter(vector<char>& letters, char target) {
    int n = letters.size();

    // Binary Search
    // letters[lo-1] <= target < letters[hi], [lo, hi) unknown
    auto lo = 0, hi = n;
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (letters[mid] <= target) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return (lo < n) ? letters[lo] : letters[0];
  }
};
