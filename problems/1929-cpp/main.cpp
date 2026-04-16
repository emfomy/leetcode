// Source: https://leetcode.com/problems/concatenation-of-array
// Title: Concatenation of Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` of length `n`, you want to create an array `ans` of length `2n` where `ans[i] == nums[i]` and `ans[i + n] == nums[i]` for `0 <= i < n` (**0-indexed**).
//
// Specifically, `ans` is the **concatenation** of two `nums` arrays.
//
// Return the array `ans`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,1]
// Output: [1,2,1,1,2,1]
// Explanation: The array ans is formed as follows:
// - ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]
// - ans = [1,2,1,1,2,1]```
//
// **Example 2:**
//
// ```
// Input: nums = [1,3,2,1]
// Output: [1,3,2,1,1,3,2,1]
// Explanation: The array ans is formed as follows:
// - ans = [nums[0],nums[1],nums[2],nums[3],nums[0],nums[1],nums[2],nums[3]]
// - ans = [1,3,2,1,1,3,2,1]
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= n <= 1000`
// - `1 <= nums[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// In-Place
class Solution {
 public:
  vector<int> getConcatenation(vector<int>& nums) {
    const int n = nums.size();

    // Resize
    nums.reserve(2 * n);

    // Concat
    for (int i = 0; i < n; ++i) {
      nums.push_back(nums[i]);
    }

    return nums;
  }
};

// Out-Place
class Solution2 {
 public:
  vector<int> getConcatenation(const vector<int>& nums) {
    const int n = nums.size();

    // Reserve
    auto ans = vector<int>();
    ans.reserve(2 * n);

    // Insert Twice
    ans.insert(ans.end(), nums.cbegin(), nums.cend());
    ans.insert(ans.end(), nums.cbegin(), nums.cend());

    return ans;
  }
};
