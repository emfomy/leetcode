// Source: https://leetcode.com/problems/range-sum-query-immutable
// Title: Range Sum Query - Immutable
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, handle multiple queries of the following type:
//
// - Calculate the **sum** of the elements of `nums` between indices `left` and `right` **inclusive** where `left <= right`.
//
// Implement the `NumArray` class:
//
// - `NumArray(int[] nums)` Initializes the object with the integer array `nums`.
// - `int sumRange(int left, int right)` Returns the **sum** of the elements of `nums` between indices `left` and `right` **inclusive** (i.e. `nums[left] + nums[left + 1] + ... + nums[right]`).
//
// **Example 1:**
//
// ```
// Input:
// ["NumArray", "sumRange", "sumRange", "sumRange"]
// [[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
//
// Output:
// [null, 1, -1, -3]
//
// Explanation:
// NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
// numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
// numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
// numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^4`
// - `-10^5 <= nums[i] <= 10^5`
// - `0 <= left <= right < nums.length`
// - At most `10^4` calls will be made to `sumRange`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix Sum
class NumArray {
  vector<int> data;  // data[i] = sum of [0, i)

 public:
  NumArray(const vector<int>& nums) {
    const int n = nums.size();
    data.assign(n + 1, 0);

    // Build: O(N)
    for (int i = 0; i < n; ++i) {
      data[i + 1] = data[i] + nums[i];
    }
  }

  // Query O(1); sum of [left, right]
  int sumRange(int left, int right) const {
    ++right;  // convert to close-open range
    return data[right] - data[left];
  }
};
