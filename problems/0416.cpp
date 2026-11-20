// Source: https://leetcode.com/problems/partition-equal-subset-sum
// Title: Partition Equal Subset Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return `true` if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: nums = [1,5,11,5]
// Output: true
// Explanation: The array can be partitioned as [1, 5, 5] and [11].
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,5]
// Output: false
// Explanation: The array cannot be partitioned into equal sum subsets.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 200`
// - `1 <= nums[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bitset>
#include <numeric>
#include <vector>

using namespace std;

// DP
//
// First compute the total sum. It must be even.
// The target is to find a subset with half of the total sum.
// Denote this number as `T`.
//
// DP[i]=true if there is a subset with sum i.
// For each number, loop through all valid subset sum and add this number.
class Solution {
 public:
  bool canPartition(const vector<int>& nums) {
    int total = accumulate(nums.cbegin(), nums.cend(), 0);
    if (total % 2) return false;  // total sum must be even
    int half = total / 2;

    // DP
    auto dp = vector<bool>(half + 1);
    dp[0] = true;
    for (const int num : nums) {
      for (int sum = half; sum >= num; --sum) {
        dp[sum] = dp[sum] || dp[sum - num];
      }
      if (dp[half]) break;
    }

    return dp[half];
  }
};

// DP + Bitset
//
// Use bitset instead of boolean array.
class Solution2 {
  using Bits = bitset<10001>;  // The maximum sum is 20000, half of it is 10000.

 public:
  bool canPartition(const vector<int>& nums) {
    int total = accumulate(nums.cbegin(), nums.cend(), 0);
    if (total % 2) return false;  // total sum must be even
    int half = total / 2;

    // DP
    Bits dp;
    dp[0] = 1;
    for (const int num : nums) {
      dp |= dp << num;
      if (dp[half]) break;
    }

    return dp[half];
  }
};

// Math: Generating Function
//
// First compute the total sum. It must be even.
// The target is to find a subset with half of the total sum.
// Denote this number as `T`.
//
// The generating function is G(x) = Prod (1+x^nums[i])
// We only need to know if the x^T term of G(x) is nonzero.
// Since we only care about the zeroness,
// we can compute G(x) in a semi-ring for boolean with OR/AND as addition/multiplication.
// Since we only cares about the x^T term, we can drop the terms higher than x^T,
// and use an boolean array of length T+1 to store the polynomial coffefients.
//
// Note that this solution is identical to the DP solution.
class Solution3 {
  using Poly = bitset<10001>;  // T <= 10000.

 public:
  bool canPartition(const vector<int>& nums) {
    int total = accumulate(nums.cbegin(), nums.cend(), 0);
    if (total % 2) return false;  // total sum must be even
    int half = total / 2;

    // DP
    Poly poly;
    poly[0] = 1;  // P(x) = 1
    for (const int num : nums) {
      poly |= poly << num;  // P(x) *= (1+x^num)
      if (poly[half]) break;
    }

    return poly[half];
  }
};
