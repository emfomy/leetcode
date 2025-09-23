// Source: https://leetcode.com/problems/largest-unique-number
// Title: Largest Unique Number
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return the largest integer that only occurs once. If no integer occurs once, return `-1`.
//
// **Example 1:**
//
// ```
// Input: nums = [5,7,3,9,4,9,8,3,1]
// Output: 8
// Explanation: The maximum integer in the array is 9 but it is repeated. The number 8 occurs only once, so it is the answer.```
//
// **Example 2:**
//
// ```
// Input: nums = [9,9,8,8]
// Output: -1
// Explanation: There is no number that occurs only once.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 2000`
// - `0 <= nums[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

// Counter
class Solution {
 public:
  int largestUniqueNumber(vector<int>& nums) {
    auto counter = unordered_map<int, int>();

    // Count
    for (const auto num : nums) {
      ++counter[num];
    }

    // Max
    auto ans = -1;
    for (auto [num, count] : counter) {
      if (count == 1) ans = max(ans, num);
    }

    return ans;
  }
};

// Counter
class Solution2 {
 public:
  int largestUniqueNumber(vector<int>& nums) {
    auto counter = array<int, 1001>();

    // Count
    for (const auto num : nums) {
      ++counter[num];
    }

    // Find
    for (auto i = 1000; i >= 0; --i) {
      if (counter[i] == 1) return i;
    }
    return -1;
  }
};
