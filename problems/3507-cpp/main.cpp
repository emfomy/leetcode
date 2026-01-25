// Source: https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i
// Title: Minimum Pair Removal to Sort Array I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `nums`, you can perform the following operation any number of times:
//
// - Select the **adjacent** pair with the **minimum** sum in `nums`. If multiple such pairs exist, choose the leftmost one.
// - Replace the pair with their sum.
//
// Return the **minimum number of operations** needed to make the array **non-decreasing**.
//
// An array is said to be **non-decreasing** if each element is greater than or equal to its previous element (if it exists).
//
// **Example 1:**
//
// ```
// Input: nums = [5,2,3,1]
// Output: 2
// Explanation:
// - The pair `(3,1)` has the minimum sum of 4. After replacement, `nums = [5,2,4]`.
// - The pair `(2,4)` has the minimum sum of 6. After replacement, `nums = [5,6]`.
// The array `nums` became non-decreasing in two operations.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,2]
// Output: 0
// Explanation:
// The array `nums` is already sorted.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 50`
// - `-1000 <= nums[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Simulation
class Solution {
 public:
  int minimumPairRemoval(vector<int>& nums) {
    int n = nums.size();

    // Helper
    auto check = [&]() -> bool {
      for (auto i = 0; i < nums.size() - 1; ++i) {
        if (nums[i] > nums[i + 1]) return false;
      }
      return true;
    };

    // Loop
    auto ans = 0;
    while (!check()) {
      ++ans;

      // Find minimal
      auto minSum = nums[0] + nums[1];
      auto minIdx = 0;
      for (auto i = 1; i < nums.size() - 1; ++i) {
        auto sum = nums[i] + nums[i + 1];
        if (minSum > sum) {
          minSum = sum;
          minIdx = i;
        }
      }

      nums[minIdx] = minSum;
      nums.erase(nums.cbegin() + minIdx + 1);
    }

    return ans;
  }
};
