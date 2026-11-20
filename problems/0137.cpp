// Source: https://leetcode.com/problems/single-number-ii
// Title: Single Number II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` where every element appears **three times** except for one, which appears **exactly once**. Find the single element and return it.
//
// You must implement a solution with a linear runtime complexity and useonly constant extra space.
//
// **Example 1:**
//
// ```
// Input: nums = [2,2,3,2]
// Output: 3
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,1,0,1,0,1,99]
// Output: 99
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 3 * 10^4`
// - `-2^31 <= nums[i] <= 2^31 - 1`
// - Each element in `nums` appears exactly **three times** except for one element which appears **once**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// Bit Count
class Solution {
 public:
  int singleNumber(const vector<int>& nums) {
    int ans = 0;

    for (int i = 0; i < 32; i++) {
      int count = 0;
      uint32_t bit = 1u << i;
      for (const int num : nums) {
        if (bit & num) count++;
      }
      if (count % 3) ans |= bit;
    }

    return ans;
  }
};

// Bit Manipulation
//
// Use `once` for bits that occurs once (mod 3).
// Use `twice` for bits that occurs twice (mod 3).
// Note that once are twice are mutually exclusive.
//
// For each bit,
// num=0 => keep old value
// num=1, once=0, twice=0 => once=1, twice=0
// num=1, once=1, twice=0 => once=0, twice=1
// num=1, once=0, twice=1 => once=0, twice=0
class Solution2 {
 public:
  int singleNumber(vector<int>& nums) {
    int once = 0;
    int twice = 0;

    for (auto num : nums) {
      int onceNext = (~num & once) | (num & ~once & ~twice);
      int twiceNext = (~num & twice) | (num & once & ~twice);
      once = onceNext, twice = twiceNext;
    }

    return once;
  }
};

// Bit Manipulation
//
// Use `once` for bits that occurs once (mod 3).
// Use `twice` for bits that occurs twice (mod 3).
// Note that once are twice are mutually exclusive.
//
// In the following, we fucus on a single bit.
//
// To update `once`:
// Use `num ^ once` to update, meanwhile `twice` must be 0.
//
// To update `twice`:
// Use `num ^ twice` to update. meanwhile `once` must be 1.
// However, we already updated `once`. Therefore `once` must be 0 now.
//
// Therefore,
// once = (num ^ once) & ~twice
// twice = (num ^ twice) & ~once
class Solution3 {
 public:
  int singleNumber(vector<int>& nums) {
    int once = 0;
    int twice = 0;

    for (int num : nums) {
      once = (num ^ once) & ~twice;
      twice = (num ^ twice) & ~once;
    }

    return once;
  }
};

// Bit Manipulation
//
// Note that (A ^ B) & C = (A ^ C) & (B ^ C).
//
// First we have `(once ^ num) & ~twice = (once & ~twice) ^ (num & ~twice)`.
// Since `once` and `twice` are mutually exclusive, we have `once & ~twice = once`.
// Therefore `once <- once ^ (num & ~twice)`.
//
// Similarly, we have `(twice ^ num) & ~once = (twice & ~once) ^ (num & ~once)`.
// Also, we have `twice & ~once = twice`
// Therefore `twice <- twice ^ (num & ~once)`.
class Solution4 {
 public:
  int singleNumber(vector<int>& nums) {
    int once = 0;
    int twice = 0;

    for (int num : nums) {
      once ^= num & ~twice;
      twice ^= num & ~once;
    }

    return once;
  }
};
