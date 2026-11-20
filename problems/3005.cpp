// Source: https://leetcode.com/problems/count-elements-with-maximum-frequency
// Title: Count Elements With Maximum Frequency
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `nums` consisting of **positive** integers.
//
// Return the **total frequencies** of elements in `nums`such that those elements all have the **maximum** frequency.
//
// The **frequency** of an element is the number of occurrences of that element in the array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,2,3,1,4]
// Output: 4
// Explanation: The elements 1 and 2 have a frequency of 2 which is the maximum frequency in the array.
// So the number of elements in the array with maximum frequency is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4,5]
// Output: 5
// Explanation: All elements of the array have a frequency of 1 which is the maximum.
// So the number of elements in the array with maximum frequency is 5.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 100`
// - `1 <= nums[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Counter
class Solution {
 public:
  int maxFrequencyElements(vector<int>& nums) {
    // Count frequency
    auto freqs = vector<int>(101);
    for (auto num : nums) {
      ++freqs[num];
    }

    // Find max frequency
    auto maxFreq = 0;
    for (auto freq : freqs) {
      maxFreq = max(maxFreq, freq);
    }

    // Sum frequency
    auto ans = 0;
    for (auto freq : freqs) {
      if (freq == maxFreq) {
        ans += freq;
      }
    }

    return ans;
  }
};

// Counter + One Pass
class Solution2 {
 public:
  int maxFrequencyElements(vector<int>& nums) {
    auto freqs = vector<int>(101);

    auto ans = 0;
    auto maxFreq = 0;
    for (auto num : nums) {
      auto freq = ++freqs[num];
      if (freq > maxFreq) {
        maxFreq = freq;
        ans = freq;
      } else if (freq == maxFreq) {
        ans += freq;
      }
    }

    return ans;
  }
};
