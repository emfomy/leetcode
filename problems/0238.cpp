// Source: https://leetcode.com/problems/product-of-array-except-self
// Title: Product of Array Except Self
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.
//
// The product of any prefix or suffix of `nums` is **guaranteed** to fit in a **32-bit** integer.
//
// You must write an algorithm that runs in`O(n)`time and without using the division operation.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,4]
// Output: [24,12,8,6]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [-1,1,0,-3,3]
// Output: [0,0,9,0,0]
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 10^5`
// - `-30 <= nums[i] <= 30`
// - The input is generated such that `answer[i]` is **guaranteed** to fit in a **32-bit** integer.
//
// **Follow up:**Can you solve the problem in `O(1)`extraspace complexity? (The output array **does not** count as extra space for space complexity analysis.)
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix Prod
//
// Compute the prefix/suffix product.
class Solution {
 public:
  vector<int> productExceptSelf(const vector<int>& nums) {
    const int n = nums.size();

    // Prefix Prod
    auto prefixs = vector<int>(n + 1);  // prod of [0, i)
    prefixs[0] = 1;
    for (int i = 0; i < n; ++i) {
      prefixs[i + 1] = prefixs[i] * nums[i];
    }

    // Suffix Prod
    auto suffixs = vector<int>(n + 1);  // prod of [i, n)
    suffixs[n] = 1;
    for (int i = n - 1; i >= 0; --i) {
      suffixs[i] = suffixs[i + 1] * nums[i];
    }

    // Answer
    auto ans = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      ans[i] = prefixs[i] * suffixs[i + 1];
    }

    return ans;
  }
};

// Prefix Prod
//
// No extra space.
class Solution2 {
 public:
  vector<int> productExceptSelf(const vector<int>& nums) {
    const int n = nums.size();
    auto ans = vector<int>(n);

    // Prefix product
    int prefix = 1;  // prod of [0, i)
    for (int i = 0; i < n; ++i) {
      ans[i] = prefix;
      prefix *= nums[i];
    }

    // Suffix product
    int suffix = 1;  // prod of (i, n)
    for (int i = n - 1; i >= 0; --i) {
      ans[i] *= suffix;
      suffix *= nums[i];
    }

    return ans;
  }
};
