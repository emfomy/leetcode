// Source: https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum
// Title: Minimum Swaps to Sort by Digit Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `nums` of **distinct** positive integers. You need to sort the array in **increasing** order based on the sum of the digits of each number. If two numbers have the same digit sum, the **smaller** number appears first in the sorted order.
//
// Return the **minimum** number of swaps required to rearrange `nums` into this sorted order.
//
// A **swap** is defined as exchanging the values at two distinct positions in the array.
//
// **Example 1:**
//
// ```
// Input: nums = [37,100]
// Output: 1
// Explanation:
// - Compute the digit sum for each integer: `[3 + 7 = 10, 1 + 0 + 0 = 1] → [10, 1]`
// - Sort the integers based on digit sum: `[100, 37]`. Swap `37` with `100` to obtain the sorted order.
// - Thus, the minimum number of swaps required to rearrange `nums` is 1.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [22,14,33,7]
// Output: 0
// Explanation:
// - Compute the digit sum for each integer: `[2 + 2 = 4, 1 + 4 = 5, 3 + 3 = 6, 7 = 7] → [4, 5, 6, 7]`
// - Sort the integers based on digit sum: `[22, 14, 33, 7]`. The array is already sorted.
// - Thus, the minimum number of swaps required to rearrange `nums` is 0.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [18,43,34,16]
// Output: 2
// Explanation:
// - Compute the digit sum for each integer: `[1 + 8 = 9, 4 + 3 = 7, 3 + 4 = 7, 1 + 6 = 7] → [9, 7, 7, 7]`
// - Sort the integers based on digit sum: `[16, 34, 43, 18]`. Swap `18` with `16`, and swap `43` with `34` to obtain the sorted order.
// - Thus, the minimum number of swaps required to rearrange `nums` is 2.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `nums` consists of **distinct** positive integers.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// First index sort the array.
//
// Next find the number of cycles after sort.
// The answer is N - #(cycle).
class Solution {
 public:
  int minSwaps(const vector<int>& nums) {
    const int n = nums.size();

    // Digit sum
    auto sums = vector<int>();
    sums.reserve(n);
    for (int num : nums) {
      int sum = 0;
      while (num > 0) {
        sum += num % 10;
        num /= 10;
      }
      sums.push_back(sum);
    }

    // Index sort
    auto orders = vector<int>(n);
    const auto comp = [&nums, &sums](int i, int j) -> bool {
      if (sums[i] != sums[j]) return sums[i] < sums[j];
      return nums[i] < nums[j];
    };
    iota(orders.begin(), orders.end(), 0);
    sort(orders.begin(), orders.end(), comp);

    // Count cycles
    int cycles = 0;
    for (int i = 0; i < n; ++i) {
      if (orders[i] < 0) continue;  // visited

      ++cycles;

      int curr = i;
      while (orders[curr] >= 0) {
        int next = orders[curr];
        orders[curr] = -1;  // mark as visited
        curr = next;
      }
    }

    return n - cycles;
  }
};
