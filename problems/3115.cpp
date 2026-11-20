// Source: https://leetcode.com/problems/maximum-prime-difference
// Title: Maximum Prime Difference
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`.
//
// Return an integer that is the **maximum** distance between the **indices** of two (not necessarily different) prime numbers in `nums`.
//
// **Example 1:**
//
// ```
// Input: nums = [4,2,9,5,3]
// Output: 3
// Explanation: `nums[1]`, `nums[3]`, and `nums[4]` are prime. So the answer is `|4 - 1| = 3`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [4,8,2,8]
// Output: 0
// Explanation: `nums[2]` is prime. Because there is just one prime number, the answer is `|2 - 2| = 0`.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 3 * 10^5`
// - `1 <= nums[i] <= 100`
// - The input is generated such that the number of prime numbers in the `nums` is at least one.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

// Find the first prime and the last prime.
class Solution {
  static bool isPrime(const int x) {
    if (x <= 1) return false;
    for (int i = 2; i * i <= x; ++i) {
      if (x % i == 0) return false;
    }
    return true;
  }

 public:
  int maximumPrimeDifference(const vector<int>& nums) {
    auto firstIt = find_if(nums.cbegin(), nums.cend(), isPrime);
    auto lastIt = find_if(nums.crbegin(), nums.crend(), isPrime);
    int dist = distance(firstIt, lastIt.base()) - 1;
    return max(dist, -1);  // return negative when there is no prime
  }
};
