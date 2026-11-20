// Source: https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements
// Title: Make Lexicographically Smallest Array by Swapping Elements
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** array of **positive** integers `nums` and a **positive** integer `limit`.
//
// In one operation, you can choose any two indices `i` and `j` and swap `nums[i]` and `nums[j]` **if** `|nums[i] - nums[j]| <= limit`.
//
// Return the **lexicographically smallest array** that can be obtained by performing the operation any number of times.
//
// An array `a` is lexicographically smaller than an array `b` if in the first position where `a` and `b` differ, array `a` has an element that is less than the corresponding element in `b`. For example, the array `[2,10,3]` is lexicographically smaller than the array `[10,2,3]` because they differ at index `0` and `2 < 10`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,5,3,9,8], limit = 2
// Output: [1,3,5,8,9]
// Explanation: Apply the operation 2 times:
// - Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
// - Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
// We cannot obtain a lexicographically smaller array by applying any more operations.
// Note that it may be possible to get the same result by doing different operations.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,7,6,18,2,1], limit = 3
// Output: [1,6,7,18,1,2]
// Explanation: Apply the operation 3 times:
// - Swap nums[1] with nums[2]. The array becomes [1,6,7,18,2,1]
// - Swap nums[0] with nums[4]. The array becomes [2,6,7,18,1,1]
// - Swap nums[0] with nums[5]. The array becomes [1,6,7,18,1,2]
// We cannot obtain a lexicographically smaller array by applying any more operations.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,7,28,19,10], limit = 3
// Output: [1,7,28,19,10]
// Explanation: [1,7,28,19,10] is the lexicographically smallest array we can obtain because we cannot apply the operation on any two indices.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `1 <= limit <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Sort
//
// First sort the numbers (tracking the original indices).
// Next loop the sorted number,
// group them by cutting the numbers with difference greater than the limit.
// Next we sort each groups (in original indices).
class Solution {
 public:
  vector<int> lexicographicallySmallestArray(const vector<int>& nums, int limit) {
    const int n = nums.size();

    // Sort order
    auto orders = vector<int>(n);
    const auto comp = [&nums](int i, int j) -> bool { return nums[i] < nums[j]; };
    iota(orders.begin(), orders.end(), 0);
    sort(orders.begin(), orders.end(), comp);

    // Sort number
    auto sorted = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      sorted[i] = nums[orders[i]];
    }

    // Grouping
    int groupStart = 0;
    for (int i = 1; i < n; ++i) {
      // Same group
      if (sorted[i] - sorted[i - 1] <= limit) continue;

      // Cut here
      sort(orders.begin() + groupStart, orders.begin() + i);
      groupStart = i;
    }
    sort(orders.begin() + groupStart, orders.end());

    // Answer
    auto ans = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      ans[orders[i]] = sorted[i];
    }

    return ans;
  }
};
