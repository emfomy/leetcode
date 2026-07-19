// Source: https://leetcode.com/problems/sum-of-gcd-of-formed-pairs
// Title: Sum of GCD of Formed Pairs
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n`.
//
// Construct an array `prefixGcd` where for each index `i`:
//
// - Let `mx_i = max(nums[0], nums[1], ..., nums[i])`.
// - `prefixGcd[i] = gcd(nums[i], mx_i)`.
//
// After constructing `prefixGcd`:
//
// - Sort `prefixGcd` in **non-decreasing** order.
// - Form pairs by taking the **smallest unpaired** element and the **largest unpaired** element.
// - Repeat this process until no more pairs can be formed.
// - For each formed pair, **compute** the `gcd` of the two elements.
// - If `n` is odd, the **middle** element in the `prefixGcd` array remains **unpaired** and should be ignored.
//
// Return an integer denoting the **sum of the GCD** values of all formed pairs.
// The term `gcd(a, b)` denotes the **greatest common divisor** of `a` and `b`.
//
// **Example 1:**
//
// ```
// Input: nums = [2,6,4]
// Output: 2
// Explanation:
// Construct `prefixGcd`:
//
// | i | nums[i] | mx_i | prefixGcd[i] |
// |---|---------|------|--------------|
// | 0 | 2       | 2    | 2            |
// | 1 | 6       | 6    | 6            |
// | 2 | 4       | 6    | 2            |
//
// `prefixGcd = [2, 6, 2]`. After sorting, it forms `[2, 2, 6]`.
// Pair the smallest and largest elements: `gcd(2, 6) = 2`. The remaining middle element 2 is ignored. Thus, the sum is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,6,2,8]
// Output: 5
// Explanation:
// Construct `prefixGcd`:
//
// | i | nums[i] | mx_i | prefixGcd[i] |
// |---|---------|------|--------------|
// | 0 | 3       | 3    | 3            |
// | 1 | 6       | 6    | 6            |
// | 2 | 2       | 6    | 2            |
// | 3 | 8       | 8    | 8            |
//
// `prefixGcd = [3, 6, 2, 8]`. After sorting, it forms `[2, 3, 6, 8]`.
// Form pairs: `gcd(2, 8) = 2` and `gcd(3, 6) = 3`. Thus, the sum is `2 + 3 = 5`.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  long long gcdSum(const vector<int>& nums) {
    const int n = nums.size();

    // Compute prefix GCD
    int mx = 0;
    auto prefixGcd = vector<int>();
    prefixGcd.reserve(n);
    for (int num : nums) {
      mx = max(mx, num);
      prefixGcd.push_back(gcd(num, mx));
    }

    // Sort
    sort(prefixGcd.begin(), prefixGcd.end());

    // Pair
    long long sum = 0;
    for (int i = 0, j = n - 1; i < j; ++i, --j) {
      sum += gcd(prefixGcd[i], prefixGcd[j]);
    }

    return sum;
  }
};
