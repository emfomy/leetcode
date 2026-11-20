// Source: https://leetcode.com/problems/set-mismatch
// Title: Set Mismatch
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have a set of integers `s`, which originally contains all the numbers from `1` to `n`. Unfortunately, due to some error, one of the numbers in `s` got duplicated to another number in the set, which results in **repetition of one** number and **loss of another** number.
//
// You are given an integer array `nums` representing the data status of this set after the error.
//
// Find the number that occurs twice and the number that is missing and return them in the form of an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,2,4]
// Output: [2,3]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,1]
// Output: [1,2]
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 10^4`
// - `1 <= nums[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

// Math
//
// Say x is the duplicated number, y is the missing number
// Let S be the sum and S2 be the square sum.
// S = n(n+1)/2 + x - y
// S2 = n(n+1)(2n+1)/6 + x^2 - y^2
//
// Define D = x-y and D2 = x^2-y^2 = (x+y)(x-y) = D(x+y)
// x-y = D, x+y = D2/D
// x = (D2/D + D) / 2
// y = (D2/D - D) / 2
class Solution {
 public:
  vector<int> findErrorNums(vector<int>& nums) {
    int64_t n = nums.size();

    int64_t sum = 0;
    int64_t sum2 = 0;
    for (auto num : nums) {
      sum += num;
      sum2 += num * num;
    }

    int diff = sum - n * (n + 1) / 2;
    int diff2 = sum2 - n * (n + 1) * (2 * n + 1) / 6;

    int x = (diff2 / diff + diff) / 2;
    int y = (diff2 / diff - diff) / 2;

    return {x, y};
  }
};

// XOR
//
// Say x, y be the duplicated and the missing number. (not knowing which is which).
// The XOR sum of 1 to n and the array. It is x^y.
//
// Now pick any 1-bit from x^y. (since x != y, x^y != 0, such bit exists).
// We know that one of x & y must contain this bit, and other doesn't.
// WLOG, say x contain this bit and y doesn't.
// WLOG, we pick the lowest 1-bit.
//
// Now group 1 to n into two groups.
// G are the those with this bit, and H are those without this bit. (x in G, y in H).
// Find the XOR sum of 1 to n in G and array in G. It should be x.
// Also do the same for H to find y.
//
// Finally check if x is in the array.
class Solution2 {
 public:
  vector<int> findErrorNums(vector<int>& nums) {
    int64_t n = nums.size();

    // Find x^y
    auto xy = 0u;
    for (auto num = 1; num <= n; ++num) xy ^= num;
    for (auto num : nums) xy ^= num;

    // Find rightmost bit
    auto bit = xy & (-xy);

    // Find x
    auto x = 0u;
    for (auto num = 1; num <= n; ++num) {
      if ((num & bit) != 0) x ^= num;
    }
    for (auto num : nums) {
      if ((num & bit) != 0) x ^= num;
    }

    // Find y
    auto y = 0u;
    for (auto num = 1; num <= n; ++num) {
      if ((num & bit) == 0) y ^= num;
    }
    for (auto num : nums) {
      if ((num & bit) == 0) y ^= num;
    }

    // Check x in array
    if (!count(nums.cbegin(), nums.cend(), x)) swap(x, y);

    return {int(x), int(y)};
  }
};
