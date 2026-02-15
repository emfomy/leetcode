// Source: https://leetcode.com/problems/grumpy-bookstore-owner
// Title: Grumpy Bookstore Owner
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a bookstore owner that has a store open for `n` minutes. You are given an integer array `customers` of length `n` where `customers[i]` is the number of the customers that enter the store at the start of the `i^th` minute and all those customers leave after the end of that minute.
//
// During certain minutes, the bookstore owner is grumpy. You are given a binary array grumpy where `grumpy[i]` is `1` if the bookstore owner is grumpy during the `i^th` minute, and is `0` otherwise.
//
// When the bookstore owner is grumpy, the customers entering during that minute are not **satisfied**. Otherwise, they are satisfied.
//
// The bookstore owner knows a secret technique to remain **not grumpy** for `minutes` consecutive minutes, but this technique can only be used **once**.
//
// Return the **maximum** number of customers that can be satisfied throughout the day.
//
// **Example 1:**
//
// ```
// Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
// Output: 16
// Explanation:
// The bookstore owner keeps themselves not grumpy for the last 3 minutes.
// The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.
// ```
//
// **Example 2:**
//
// ```
// Input: customers = [1], grumpy = [0], minutes = 1
// Output: 1
// ```
//
// **Constraints:**
//
// - `n == customers.length == grumpy.length`
// - `1 <= minutes <= n <= 2 * 10^4`
// - `0 <= customers[i] <= 1000`
// - `grumpy[i]` is either `0` or `1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <numeric>
#include <vector>

using namespace std;

// Sliding window
//
// Maximize satisfied customers i.e.
// maximum customers in the special windows with grumpy value is 1.
class Solution {
 public:
  int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
    const int n = customers.size();

    const int64_t total = accumulate(customers.cbegin(), customers.cend(), int64_t(0));
    const int64_t totalMad = inner_product(customers.cbegin(), customers.cend(), grumpy.cbegin(), int64_t(0));

    // Sliding window
    int64_t maxMadInWindow = 0;
    int64_t currMadInWindow = 0;
    for (int i = 0; i < n; ++i) {
      currMadInWindow += customers[i] * grumpy[i];

      if (i >= minutes - 1) {
        maxMadInWindow = max(maxMadInWindow, currMadInWindow);

        currMadInWindow -= customers[i - minutes + 1] * grumpy[i - minutes + 1];
      }
    }

    return total - (totalMad - maxMadInWindow);
  }
};
