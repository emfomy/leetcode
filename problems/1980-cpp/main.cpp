// Source: https://leetcode.com/problems/find-unique-binary-string
// Title: Find Unique Binary String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of strings `nums` containing `n` **unique** binary strings each of length `n`, return a binary string of length `n` that **does not appear** in `nums`. If there are multiple answers, you may return **any** of them.
//
// **Example 1:**
//
// ```
// Input: nums = ["01","10"]
// Output: "11"
// Explanation: "11" does not appear in nums. "00" would also be correct.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = ["00","01"]
// Output: "11"
// Explanation: "11" does not appear in nums. "10" would also be correct.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = ["111","011","001"]
// Output: "101"
// Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= n <= 16`
// - `nums[i].length == n`
// - `nums[i] `is either `'0'` or `'1'`.
// - All the strings of `nums` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// The answer must have a digit different to all the input numbers.
// Inspired by the idea of Cantor's diagonal argument,
// we construct the answer by setting the i-th digit different from the i-th number.
class Solution {
 public:
  string findDifferentBinaryString(const vector<string>& nums) {
    const int n = nums.size();

    string ans = "";
    ans.resize(n);

    for (int i = 0; i < n; ++i) {
      ans[i] = nums[i][i] ^ '0' ^ '1';  // swap 0 and 1
    }

    return ans;
  }
};
