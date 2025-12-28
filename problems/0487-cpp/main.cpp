// Source: https://leetcode.com/problems/max-consecutive-ones-ii
// Title: Max Consecutive Ones II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary array `nums`, return the maximum number of consecutive `1`'s in the array if you can flip at most one `0`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,0,1,1,0]
// Output: 4
// Explanation:
// - If we flip the first zero, nums becomes [1,1,1,1,0] and we have 4 consecutive ones.
// - If we flip the second zero, nums becomes [1,0,1,1,1] and we have 3 consecutive ones.
// The max number of consecutive ones is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,0,1,1,0,1]
// Output: 4
// Explanation:
// - If we flip the first zero, nums becomes [1,1,1,1,0,1] and we have 4 consecutive ones.
// - If we flip the second zero, nums becomes [1,0,1,1,1,1] and we have 4 consecutive ones.
// The max number of consecutive ones is 4.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `nums[i]` is either `0` or `1`.
//
// **Follow up:** What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Use DP
//
// DP0 is the maximum number of consecutive 1 without flipping
// DP1 is the maximum number of consecutive 1 with flipping
class Solution {
 public:
  int findMaxConsecutiveOnes(vector<int>& nums) {
    auto ans = 0;
    auto fp0 = 0, fp1 = 0;
    for (auto curr : nums) {
      if (curr == 1) {
        ++fp0;
        ++fp1;
      } else {
        fp1 = fp0 + 1;
        fp0 = 0;
      }
      ans = max({ans, fp0, fp1});
    }

    return ans;
  }
};

// Tracking current and previous consecutive 1's.
class Solution2 {
 public:
  int findMaxConsecutiveOnes(vector<int>& nums) {
    auto ans = 0;
    auto prev = -1, curr = 0;
    for (auto num : nums) {
      if (num == 1) {
        ++curr;
      } else {
        prev = curr;
        curr = 0;
      }
      ans = max(ans, curr + prev + 1);  // current + previous + flipped
    }

    return ans;
  }
};
