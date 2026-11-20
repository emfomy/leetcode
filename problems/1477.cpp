// Source: https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum
// Title: Find Two Non-overlapping Sub-arrays Each With Target Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of integers `arr` and an integer `target`.
//
// You have to find **two non-overlapping sub-arrays** of `arr` each with a sum equal `target`. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is **minimum**.
//
// Return the minimum sum of the lengths of the two required sub-arrays, or return `-1` if you cannot find such two sub-arrays.
//
// **Example 1:**
//
// ```
// Input: arr = [3,2,2,4,3], target = 3
// Output: 2
// Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [7,3,4,7], target = 7
// Output: 2
// Explanation: Although we have three non-overlapping sub-arrays of sum = 7 ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as the sum of their lengths is 2.
// ```
//
// **Example 3:**
//
// ```
// Input: arr = [4,3,2,6,2,3,4], target = 6
// Output: -1
// Explanation: We have only one sub-array of sum = 6.
// ```
//
// **Constraints:**
//
// - `1 <= arr.length <= 10^5`
// - `1 <= arr[i] <= 1000`
// - `1 <= target <= 10^8`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <queue>
#include <vector>

using namespace std;

// Two Pointe
//
// Since the numbers are positive,
// we can use two pointer to find all the subarray with target sum.
// In the process, we also track the shortest subarray that already ends.
class Solution {
  struct Subarray {
    int len;
    int end;
  };

 public:
  int minSumOfLengths(const vector<int>& arr, int target) {
    const int n = arr.size();

    auto que = queue<Subarray>();

    // Loop, subarray = [l, r]
    int l = 0, r = 0;
    int sum = 0;
    int minLen = INT_MAX;
    int ans = INT_MAX;
    for (int r = 0; r < n; ++r) {
      // Move current subarray
      sum += arr[r];
      while (sum > target) sum -= arr[l++];

      // Find ended subarray
      if (!que.empty() && que.front().end < l) {
        minLen = min(minLen, que.front().len);
        que.pop();
      }

      // Find answer
      if (sum == target) {
        int len = r - l + 1;
        que.push({.len = len, .end = r});

        if (minLen < INT_MAX) {
          ans = min(ans, len + minLen);
        }
      }
    }

    return ans == INT_MAX ? -1 : ans;
  }
};
