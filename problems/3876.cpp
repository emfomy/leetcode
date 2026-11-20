// Source: https://leetcode.com/problems/construct-uniform-parity-array-ii
// Title: Construct Uniform Parity Array II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `nums1` of `n` **distinct** integers.
//
// You want to construct another array `nums2` of length `n` such that the elements in `nums2` are either **all odd or all even**.
//
// For each index `i`, you must choose **exactly one** of the following (in any order):
//
// - `nums2[i] = nums1[i]`
// - `nums2[i] = nums1[i] - nums1[j]`, for an index `j != i`, such that `nums1[i] - nums1[j] >= 1`
//
// Return `true` if it is possible to construct such an array, otherwise return `false`.
//
// **Example 1:**
//
// ```
// Input: nums1 = [1,4,7]
// Output: true
// Explanation:
// - Set `nums2[0] = nums1[0] = 1`.
// - Set `nums2[1] = nums1[1] - nums1[0] = 4 - 1 = 3`.
// - Set `nums2[2] = nums1[2] = 7`.
// - `nums2 = [1, 3, 7]`, and all elements are odd. Thus, the answer is `true`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [2,3]
// Output: false
// Explanation:
// It is not possible to construct `nums2` such that all elements have the same parity. Thus, the answer is `false`.
// ```
//
// **Example 3:**
//
// ```
// Input: nums1 = [4,6]
// Output: true
// Explanation:
// - Set `nums2[0] = nums1[0] = 4`.
// - Set `nums2[1] = nums1[1] = 6`.
// - `nums2 = [4, 6]`, and all elements are even. Thus, the answer is `true`.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums1.length <= 10^5`
// - `1 <= nums1[i] <= 10^9`
// - `nums1` consists of distinct integers.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Sort
//
// We can only substract by smaller numbers.
// Therefore, we sort `nums1` first, and loop through the array.
//
// We track the existence of odd and even number,
// and check if we can make odd / even number.
//
// Note that since the numbers are distinct,
// we don't need to care about the case nums1[i] = nums1[j].
// Sort
//
// We can only substract by smaller numbers.
// Therefore, we sort `nums1` first, and loop through the array.
//
// We track the existence of odd and even number,
// and check if we can make odd / even number.
//
// Note that since the numbers are distinct,
// we don't need to care about the case nums1[i] = nums1[j].
class Solution {
 public:
  bool uniformArray(vector<int>& nums1) {
    // Sort
    sort(nums1.begin(), nums1.end());

    // Loop
    bool hasOdd = false;
    bool canOdd = true, canEven = true;
    for (int num : nums1) {
      if (num % 2) {  // num is odd
        if (!hasOdd) canEven = false;
        hasOdd = true;
      } else {  // num is even
        if (!hasOdd) canOdd = false;
      }
    }

    return canEven || canOdd;
  }
};

// We need to change one parity to another by substracting an odd number.
// There are two cases: changing all odd / even numbers.
//
// To change all odd number, we need a smaller odd number of them.
// This is impossible since the smallest odd number has no smaller one.
//
// To change all even number, we also need a smaller odd number of them.
// That is, the smallest number must be odd.
class Solution2 {
 public:
  bool uniformArray(const vector<int>& nums1) {
    bool allEven = all_of(nums1.cbegin(), nums1.cend(), [](int x) { return x % 2 == 0; });
    bool minOdd = (*min_element(nums1.cbegin(), nums1.cend())) % 2 == 1;

    return allEven || minOdd;
  }
};
