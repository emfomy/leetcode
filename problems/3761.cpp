// Source: https://leetcode.com/problems/minimum-absolute-distance-between-mirror-pairs
// Title: Minimum Absolute Distance Between Mirror Pairs
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`.
//
// A **mirror pair** is a pair of indices `(i, j)` such that:
//
// - `0 <= i < j < nums.length`, and
// - `reverse(nums[i]) == nums[j]`, where `reverse(x)` denotes the integer formed by reversing the digits of `x`. Leading zeros are omitted after reversing, for example `reverse(120) = 21`.
//
// Return the **minimum** absolute distance between the indices of any mirror pair. The absolute distance between indices `i` and `j` is `abs(i - j)`.
//
// If no mirror pair exists, return `-1`.
//
// **Example 1:**
//
// ```
// Input: nums = [12,21,45,33,54]
// Output: 1
// Explanation:
// The mirror pairs are:
// - (0, 1) since `reverse(nums[0]) = reverse(12) = 21 = nums[1]`, giving an absolute distance `abs(0 - 1) = 1`.
// - (2, 4) since `reverse(nums[2]) = reverse(45) = 54 = nums[4]`, giving an absolute distance `abs(2 - 4) = 2`.
// The minimum absolute distance among all pairs is 1.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [120,21]
// Output: 1
// Explanation:
// There is only one mirror pair (0, 1) since `reverse(nums[0]) = reverse(120) = 21 = nums[1]`.
// The minimum absolute distance is 1.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [21,120]
// Output: -1
// Explanation:
// There are no mirror pairs in the array.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>

using namespace std;

// Hash Map
//
// We use a hash map for number index.
//
// Loop through the array.
// For each number, first find the index of the mirror number.
// Next update the hash map.
class Solution {
  static int reverse(int x) {
    int mirror = 0;
    while (x > 0) {
      mirror = 10 * mirror + x % 10;
      x /= 10;
    }
    return mirror;
  }

 public:
  int minMirrorPairDistance(const vector<int>& nums) {
    const int n = nums.size();

    // Loop
    int minDist = n;
    auto mirrorMap = unordered_map<int, int>();
    mirrorMap.reserve(n);
    for (int i = 0; i < n; ++i) {
      const int num = nums[i];
      if (mirrorMap.contains(num)) {
        minDist = min(minDist, i - mirrorMap[num]);
      }
      mirrorMap[reverse(num)] = i;
    }

    return minDist == n ? -1 : minDist;
  }
};
