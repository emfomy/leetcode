// Source: https://leetcode.com/problems/longest-subsequence-with-non-zero-bitwise-xor
// Title: Longest Subsequence With Non-Zero Bitwise XOR
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`.
//
// Return the length of the **longest <button>subsequence</button>** in `nums` whose bitwise **XOR** is **non-zero**. If no such **subsequence** exists, return 0.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3]
// Output: 2
// Explanation:
// One longest subsequence is `[2, 3]`. The bitwise XOR is computed as `2 XOR 3 = 1`, which is non-zero.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,3,4]
// Output: 3
// Explanation:
// The longest subsequence is `[2, 3, 4]`. The bitwise XOR is computed as `2 XOR 3 XOR 4 = 5`, which is non-zero.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `0 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// A set is bitwise-XOR-zero iff. the XOR of each bit is zero.
// Therefore, we loop through all bits and find the max among all bits.
//
// The XOR of a bit is equal to the parity of the count.
// If the there are total odd bits, then the answer is n.
// Otherwise, unless all the bits are zero, then the answer is n-1 (removing a 1-bit).
class Solution {
 public:
  int longestSubsequence(const vector<int>& nums) {
    const int n = nums.size();

    int sum = 0;
    for (int num : nums) sum ^= num;
    if (sum != 0) return n;

    bool hasNonZero = any_of(nums.cbegin(), nums.cend(), [](int x) { return x != 0; });
    return hasNonZero ? n - 1 : 0;
  }
};
