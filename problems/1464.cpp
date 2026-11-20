// Source: https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array
// Title: Maximum Product of Two Elements in an Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the array of integers `nums`, you will choose two different indices `i` and `j` of that array. Return the maximum value of `(nums[i]-1)*(nums[j]-1)`.
//
// **Example 1:**
//
// ```
// Input: nums = [3,4,5,2]
// Output: 12
// Explanation: If you choose the indices i=1 and j=2 (indexed from 0), you will get the maximum value, that is, (nums[1]-1)*(nums[2]-1) = (4-1)*(5-1) = 3*4 = 12.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,5,4,5]
// Output: 16
// Explanation: Choosing the indices i=1 and j=3 (indexed from 0), you will get the maximum value of (5-1)*(5-1) = 16.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [3,7]
// Output: 12
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 500`
// - `1 <= nums[i] <= 10^3`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProduct(const vector<int>& nums) {
    int max1 = INT_MIN, max2 = INT_MIN;  // max two num-1
    int min1 = INT_MAX, min2 = INT_MAX;  // min two num-1
    for (int num : nums) {
      --num;

      if (num > max1) {
        max2 = max1;
        max1 = num;
      } else if (num > max2) {
        max2 = num;
      }

      if (num < min1) {
        min2 = min1;
        min1 = num;
      } else if (num < min2) {
        min2 = num;
      }
    }

    return max(max1 * max2, min1 * min2);
  }
};
