// Source: https://leetcode.com/problems/maximum-product-subarray
// Title: Maximum Product Subarray
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, find a <button>subarray</button> that has the largest product, and return the product.
//
// The test cases are generated so that the answer will fit in a **32-bit** integer.
//
// **Note** that the product of an array with a single element is the value of that element.
//
// **Example 1:**
//
// ```
// Input: nums = [2,3,-2,4]
// Output: 6
// Explanation: [2,3] has the largest product 6.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [-2,0,-1]
// Output: 0
// Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 2 * 10^4`
// - `-10 <= nums[i] <= 10`
// - The product of any subarray of `nums` is **guaranteed** to fit in a **32-bit** integer.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// DP, Kadane
class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    int globalMax = nums[0];
    int currMax = 1;
    int currMin = 1;
    for (int num : nums) {
      int nextMax = max({num, currMax * num, currMin * num});
      int nextMin = min({num, currMax * num, currMin * num});
      currMax = nextMax;
      currMin = nextMin;
      globalMax = max(globalMax, currMax);
    }

    return globalMax;
  }
};
