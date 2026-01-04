// Source: https://leetcode.com/problems/n-repeated-element-in-size-2n-array
// Title: N-Repeated Element in Size 2N Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` with the following properties:
//
// - `nums.length == 2 * n`.
// - `nums` contains `n + 1` **unique** elements.
// - Exactly one element of `nums` is repeated `n` times.
//
// Return the element that is repeated `n` times.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,3]
// Output: 3
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,1,2,5,3,2]
// Output: 2
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [5,1,5,2,5,3,5,4]
// Output: 5
// ```
//
// **Constraints:**
//
// - `2 <= n <= 5000`
// - `nums.length == 2 * n`
// - `0 <= nums[i] <= 10^4`
// - `nums` contains `n + 1` **unique** elements and one of them is repeated exactly `n` times.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int repeatedNTimes(vector<int>& nums) {
    auto visited = unordered_set<int>();

    for (auto num : nums) {
      if (visited.contains(num)) {
        return num;
      }
      visited.insert(num);
    }

    return -1;
  }
};

// Math
//
// Denote the repeated number as A.
// Since there are n+1 unique number, there must have n copies of A.
//
// Claim: There exist a pair of A with distance <= 3.
// Proof:
// Assume false, then all distance is greater than 4.
// Then the right most A must be at index >= 4(n-1)+1 = 4n-3 > 2n (since n >= 2)
// Note that for n >= 3, the claim can be reduce to distance <= 2 (since 3n-2 > 2n for n >= 3).
//
// Now loop for all numbers, check if there is a repeated number with 3 range.
class Solution2 {
 public:
  int repeatedNTimes(vector<int>& nums) {
    int m = nums.size();

    // n = 2
    if (m == 4 && nums[0] == nums[3]) return nums[0];

    // n > 2
    for (auto i = 0; i < m; i++) {
      for (auto j = 1; j <= 2 && i + j < m; ++j) {
        if (nums[i] == nums[i + j]) return nums[i];
      }
    }

    return -1;
  }
};

// Math
//
// Denote the repeated number as A.
// Since there are n+1 unique number, there must have n copies of A.
//
// Claim: If we have k copies of A in a 2k-2 range, then there must be a pair of contiguous A.
// Proof:
// Assume false, then the distance between the first and the last A must be >= 2k-1.
// Contradiction to the range size.
//
// Here is the algorithm.
// First check if there is A in nums[0:4]
// If not, then there are at most one A in this range.
// That is, there are at least n-1 copies A in nums[4:] range (with size 2n-4).
// We loop through the range and find contiguous copies.
class Solution3 {
 public:
  int repeatedNTimes(vector<int>& nums) {
    int m = nums.size();

    for (auto i = 0; i < 4; ++i) {
      for (auto j = 0; j < i; ++j) {
        if (nums[i] == nums[j]) return nums[i];
      }
    }

    for (auto i = 5; i < m; i++) {
      if (nums[i - 1] == nums[i]) return nums[i];
    }

    return -1;
  }
};
