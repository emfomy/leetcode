// Source: https://leetcode.com/problems/max-consecutive-ones-iii
// Title: Max Consecutive Ones III
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary array `nums` and an integer `k`, return the maximum number of consecutive `1`'s in the array if you can flip at most `k` `0`'s.
//
// **Example 1:**
//
// ```
// Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
// Output: 6
// Explanation: [1,1,1,0,0,**1**,1,1,1,1,**1**]
// Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.```
//
// **Example 2:**
//
// ```
// Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
// Output: 10
// Explanation: [0,0,1,1,**1**,**1**,1,1,1,**1**,1,1,0,0,0,1,1,1,1]
// Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `nums[i]` is either `0` or `1`.
// - `0 <= k <= nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// DP, TLE
//
// Let DP[j] be the max count with j flip.
//
// If nums[i] = 0:
// DP[0][i] = 0
// DP[j][i] = DP[j-1][i-1]+1
//
// If nums[i] = 1:
// DP[j][i] = DP[j][i-1]+1
class Solution {
 public:
  int longestOnes(vector<int>& nums, int k) {
    auto counts = vector<int>(k + 1);
    int maxCount = 0;

    for (int num : nums) {
      if (num == 0) {
        for (int j = k; j > 0; --j) {
          counts[j] = counts[j - 1] + 1;
        }
        counts[0] = 0;
      } else {
        for (int j = k; j >= 0; --j) {
          ++counts[j];
        }
      }
      maxCount = max(maxCount, *max_element(counts.cbegin(), counts.cend()));
    }

    return maxCount;
  }
};

// Sliding window
//
// Count the number of ones before each zero. Assuming there is a zero at the end.
// Use sliding on k+1 zeros.
class Solution2 {
 public:
  int longestOnes(const vector<int>& nums, int k) {
    const int n = nums.size();

    // Count ones before zeros
    auto counts = vector<int>();
    counts.reserve(n + 1);
    {
      int count = 0;
      for (int num : nums) {
        if (num == 0) {
          counts.push_back(count + 1);  // include this zero
          count = 0;
        } else {
          ++count;
        }
      }
      counts.push_back(count + 1);
    }

    // Sliding window
    const int m = counts.size();
    int count = 0;
    int maxCount = 0;
    for (int i = 0; i < m; ++i) {
      count += counts[i];
      maxCount = max(maxCount, count - 1);  // exclude last zero
      if (i >= k) {
        count -= counts[i - k];
      }
    }

    return maxCount;
  }
};

// Two pointer
//
// Loop through the array and count the zeros.
// When there is more than k zeros, move the left pointer.
class Solution3 {
 public:
  int longestOnes(const vector<int>& nums, int k) {
    const int n = nums.size();

    // Loop, range is (left, right]
    int left = -1;
    int zeros = 0;
    int maxCount = 0;
    for (int right = 0; right < n; ++right) {
      // Update zero count
      if (nums[right] == 0) ++zeros;

      // Move left
      while (zeros > k) {
        if (nums[++left] == 0) --zeros;
      }

      // Update max length
      maxCount = max(maxCount, right - left);
    }

    return maxCount;
  }
};
