// Source: https://leetcode.com/problems/make-sum-divisible-by-p
// Title: Make Sum Divisible by P
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of positive integers `nums`, remove the **smallest** subarray (possibly **empty**) such that the **sum** of the remaining elements is divisible by `p`. It is **not** allowed to remove the whole array.
//
// Return the length of the smallest subarray that you need to remove, or `-1` if it's impossible.
//
// A **subarray** is defined as a contiguous block of elements in the array.
//
// **Example 1:**
//
// ```
// Input: nums = [3,1,4,2], p = 6
// Output: 1
// Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [6,3,5,2], p = 9
// Output: 2
// Explanation: We cannot remove a single element to get a sum divisible by 9. The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3], p = 3
// Output: 0
// Explanation: Here the sum is 6. which is already divisible by 3. Thus we do not need to remove anything.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `1 <= p <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>

using namespace std;

// Hash Map
//
// First compute the remainder of the total sum (say its r).
// Now the problems becomes the smallest subarray with remainder r.
//
// Next compute the prefix sum of each position,
// and use a hash map to store the rightmost index of each remainder.
//
// For each position, we can use this hash map to find the correspond staring index
// for a valid subarray.
class Solution {
 public:
  int minSubarray(vector<int>& nums, int p) {
    int n = nums.size();

    // Total sum
    auto totalR = 0;
    for (auto num : nums) totalR = (totalR + num) % p;
    if (totalR == 0) return 0;
    auto negR = p - totalR;  // the complement of total remainder

    // Prefix sum
    auto ans = n;
    auto idxs = unordered_map<int, int>();  // rightmost index of each remainder

    idxs[0] = -1;  // handle the case where subarray is the whole prefix

    auto currR = 0;
    for (int i = 0; i < n; ++i) {
      currR = (currR + nums[i]) % p;
      idxs[currR] = i;

      auto targetR = (currR + negR) % p;
      if (idxs.contains(targetR)) {
        ans = min(ans, i - idxs[targetR]);
      }
    }

    return ans != n ? ans : -1;
  }
};
