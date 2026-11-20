// Source: https://leetcode.com/problems/greatest-sum-divisible-by-three
// Title: Greatest Sum Divisible by Three
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return the **maximum possible sum **of elements of the array such that it is divisible by three.
//
// **Example 1:**
//
// ```
// Input: nums = [3,6,5,1,8]
// Output: 18
// Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).```
//
// **Example 2:**
//
// ```
// Input: nums = [4]
// Output: 0
// Explanation: Since 4 is not divisible by 3, do not pick any number.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3,4,4]
// Output: 12
// Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 4 * 10^4`
// - `1 <= nums[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Greedy
//
// Group the number by modulo 3.
// Let cnt1 / cnt2 be the number in class 1 / 2 respectively.
// If cnt1 - cnt2 = 0 (mod 3), then we can pick all numbers.
// If cnt1 - cnt2 = 1 (mod 3), then there has an extra class 1 or two extra class 2.
// If cnt1 - cnt2 = 2 (mod 3), then there has an extra class 2 or two extra class 1.
class Solution {
 public:
  int maxSumDivThree(vector<int>& nums) {
    // Count
    int sum = 0;
    int cnt1 = 0, cnt2 = 0;
    int min1a = 1e5, min1b = 1e5;
    int min2a = 1e5, min2b = 1e5;
    for (auto num : nums) {
      sum += num;
      if (num % 3 == 1) {
        ++cnt1;
        if (num < min1a) {
          min1b = min1a;
          min1a = num;
        } else if (num < min1b) {
          min1b = num;
        }
      } else if (num % 3 == 2) {
        ++cnt2;
        if (num < min2a) {
          min2b = min2a;
          min2a = num;
        } else if (num < min2b) {
          min2b = num;
        }
      }
    };

    // Answer
    auto diff = (((cnt1 - cnt2) % 3) + 3) % 3;
    if (diff == 0) return sum;

    // WLOG, assume diff == 1
    if (diff == 2) {
      swap(cnt1, cnt2);
      swap(min1a, min2a);
      swap(min1b, min2b);
    }

    // Check if there is enough number
    if (cnt1 < 1) return sum - (min2a + min2b);
    if (cnt2 < 2) return sum - min1a;
    return sum - min(min1a, min2a + min2b);
  }
};
