// Source: https://leetcode.com/problems/1-bit-and-2-bit-characters
// Title: 1-bit and 2-bit Characters
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// We have two special characters:
//
// - The first character can be represented by one bit `0`.
// - The second character can be represented by two bits (`10` or `11`).
//
// Given a binary array `bits` that ends with `0`, return `true` if the last character must be a one-bit character.
//
// **Example 1:**
//
// ```
// Input: bits = [1,0,0]
// Output: true
// Explanation: The only way to decode it is two-bit character and one-bit character.
// So the last character is one-bit character.
// ```
//
// **Example 2:**
//
// ```
// Input: bits = [1,1,1,0]
// Output: false
// Explanation: The only way to decode it is two-bit character and two-bit character.
// So the last character is not one-bit character.
// ```
//
// **Constraints:**
//
// - `1 <= bits.length <= 1000`
// - `bits[i]` is either `0` or `1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  bool isOneBitCharacter(vector<int>& bits) {
    int n = bits.size();

    auto ans = false;
    for (auto i = 0; i < n; ++i) {
      if (bits[i] == 0) {
        ans = true;
      } else {
        ans = false;
        ++i;
      }
    }

    return ans;
  }
};
