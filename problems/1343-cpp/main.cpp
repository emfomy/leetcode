// Source: https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold
// Title: Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `arr` and two integers `k` and `threshold`, return the number of sub-arrays of size `k` and average greater than or equal to `threshold`.
//
// **Example 1:**
//
// ```
// Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
// Output: 3
// Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6 respectively. All other sub-arrays of size 3 have averages less than 4 (the threshold).
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
// Output: 6
// Explanation: The first 6 sub-arrays of size 3 have averages greater than 5. Note that averages are not integers.
// ```
//
// **Constraints:**
//
// - `1 <= arr.length <= 10^5`
// - `1 <= arr[i] <= 10^4`
// - `1 <= k <= arr.length`
// - `0 <= threshold <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// Sliding Window
//
// Average >= threshold iff. Sum >= k*threshold.
class Solution {
 public:
  int numOfSubarrays(vector<int>& arr, int k, int threshold) {
    int n = arr.size();

    if (k <= 0 || n < k) return 0;

    // Loop
    int count = 0;
    int64_t targetSum = int64_t(k) * threshold;
    int64_t windowSum = 0;
    for (int i = 0; i < n; ++i) {
      windowSum += arr[i];

      if (i >= k - 1) {
        if (windowSum >= targetSum) ++count;
        windowSum -= arr[i - k + 1];
      }
    }

    return count;
  }
};
