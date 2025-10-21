// Source: https://leetcode.com/problems/next-greater-element-ii
// Title: Next Greater Element II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a circular integer array `nums` (i.e., the next element of `nums[nums.length - 1]` is `nums[0]`), return the **next greater number** for every element in `nums`.
//
// The **next greater number** of a number `x` is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return `-1` for this number.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,1]
// Output: [2,-1,2]
// Explanation: The first 1's next greater number is 2;
// The number 2 can't find next greater number.
// The second 1's next greater number needs to search circularly, which is also 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4,3]
// Output: [2,3,4,-1,4]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^4`
// - `-10^9 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <vector>

using namespace std;

// Monotonic Stack
//
// Use stack from right to left with decreasing values.
class Solution {
 public:
  vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();

    auto st = stack<int>();
    auto ans = vector<int>(n);
    for (auto i = 2 * n - 1; i >= 0; --i) {
      auto num = nums[i % n];
      while (!st.empty() && st.top() <= num) st.pop();
      ans[i % n] = st.empty() ? -1 : st.top();
      st.push(num);
    }

    return ans;
  }
};
