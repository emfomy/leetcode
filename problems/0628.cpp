// Source: https://leetcode.com/problems/maximum-product-of-three-numbers
// Title: Maximum Product of Three Numbers
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, find three numbers whose product is maximum and return the maximum product.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3]
// Output: 6
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4]
// Output: 24
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [-1,-2,-3]
// Output: -6
// ```
//
// **Constraints:**
//
// - `3 <= nums.length <=10^4`
// - `-1000 <= nums[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <vector>

using namespace std;

// Compare
class Solution {
 public:
  int maximumProduct(const vector<int>& nums) {
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;  // largest three numbers
    int min1 = INT_MAX, min2 = INT_MAX;                  // smallest two numbers

    for (int num : nums) {
      if (num > max1) {
        max3 = max2;
        max2 = max1;
        max1 = num;
      } else if (num > max2) {
        max3 = max2;
        max2 = num;
      } else if (num > max3) {
        max3 = num;
      }

      if (num < min1) {
        min2 = min1;
        min1 = num;
      } else if (num < min2) {
        min2 = num;
      }
    }

    return max(max1 * max2 * max3, max1 * min1 * min2);
  }
};

// Swap
//
// Note that min swap need to reassign num to tmp.
class Solution2 {
 public:
  int maximumProduct(const vector<int>& nums) {
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;  // largest three numbers
    int min1 = INT_MAX, min2 = INT_MAX;                  // smallest two numbers

    for (const int num : nums) {
      int tmp = num;
      if (tmp > max1) swap(tmp, max1);
      if (tmp > max2) swap(tmp, max2);
      if (tmp > max3) swap(tmp, max3);

      tmp = num;
      if (tmp < min1) swap(tmp, min1);
      if (tmp < min2) swap(tmp, min2);
    }

    return max(max1 * max2 * max3, max1 * min1 * min2);
  }
};

// DP (slower)
class Solution4 {
 public:
  int maximumProduct(const vector<int>& nums) {
    const int n = nums.size();

    int max1 = max({nums[0], nums[1], nums[2]});  // max number
    int min1 = min({nums[0], nums[1], nums[2]});  // min number

    int max2 = max({nums[0] * nums[1], nums[0] * nums[2], nums[1] * nums[2]});  // max 2-product
    int min2 = min({nums[0] * nums[1], nums[0] * nums[2], nums[1] * nums[2]});  // max 2-product

    int max3 = nums[0] * nums[1] * nums[2];  // max 3-product

    for (int i = 3; i < n; ++i) {
      int num = nums[i];
      max3 = max({max3, max2 * num, min2 * num});
      max2 = max({max2, max1 * num, min1 * num});
      min2 = min({min2, max1 * num, min1 * num});
      max1 = max(max1, num);
      min1 = min(min1, num);
    }

    return max3;
  }
};
