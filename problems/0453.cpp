// Source: https://leetcode.com/problems/minimum-moves-to-equal-array-elements
// Title: Minimum Moves to Equal Array Elements
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` of size `n`, return the minimum number of moves required to make all array elements equal.
//
// In one move, you can increment `n - 1` elements of the array by `1`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3]
// Output: 3
// Explanation: Only three moves are needed (remember each move increments two elements):
// [1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,1,1]
// Output: 0
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= nums.length <= 10^5`
// - `-10^9 <= nums[i] <= 10^9`
// - The answer is guaranteed to fit in a **32-bit** integer.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// Increment n-1 elements is identical to increment all and decrement 1 element.
// Since increment all doesn't affect the result, we only need to care about the decrement.
//
// The result is equal to the sum of the differences to the minimal number.
class Solution {
 public:
  int minMoves(const vector<int>& nums) {
    const int n = nums.size();
    int minNum = *min_element(nums.cbegin(), nums.cend());
    int sum = accumulate(nums.cbegin(), nums.cend(), 0);

    return sum - n * minNum;
  }
};
