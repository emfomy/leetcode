// Source: https://leetcode.com/problems/minimum-size-subarray-sum
// Title: Minimum Size Subarray Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of positive integers `nums` and a positive integer `target`, return the **minimal length** of a <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:rs:" data-state="closed" class="">subarray</button> whose sum is greater than or equal to `target`. If there is no such subarray, return `0` instead.
//
// **Example 1:**
//
// ```
// Input: target = 7, nums = [2,3,1,2,4,3]
// Output: 2
// Explanation: The subarray [4,3] has the minimal length under the problem constraint.
// ```
//
// **Example 2:**
//
// ```
// Input: target = 4, nums = [1,4,4]
// Output: 1
// ```
//
// **Example 3:**
//
// ```
// Input: target = 11, nums = [1,1,1,1,1,1,1,1]
// Output: 0
// ```
//
// **Constraints:**
//
// - `1 <= target <= 10^9`
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^4`
//
// **Follow up:** If you have figured out the `O(n)` solution, try coding another solution of which the time complexity is `O(n log(n))`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Use Sliding Window
class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int left = 0;
    int right = 0;

    int ans = n + 1;
    int sum = 0;  // sum of [left, right)
    while (right <= n) {
      if (sum < target) {
        if (right == n) {
          break;
        }
        sum += nums[right];
        right++;
      } else {
        ans = min(ans, right - left);
        sum -= nums[left];
        left++;
      }
    }

    if (ans == n + 1) {
      return 0;
    }
    return ans;
  }
};
