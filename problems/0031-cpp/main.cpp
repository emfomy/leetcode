// Source: https://leetcode.com/problems/next-permutation
// Title: Next Permutation
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **permutation** of an array of integers is an arrangement of its members into a sequence or linear order.
//
// - For example, for `arr = [1,2,3]`, the following are all the permutations of `arr`: `[1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1]`.
//
// The **next permutation** of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the **next permutation** of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).
//
// - For example, the next permutation of `arr = [1,2,3]` is `[1,3,2]`.
// - Similarly, the next permutation of `arr = [2,3,1]` is `[3,1,2]`.
// - While the next permutation of `arr = [3,2,1]` is `[1,2,3]` because `[3,2,1]` does not have a lexicographical larger rearrangement.
//
// Given an array of integers `nums`, find the next permutation of `nums`.
//
// The replacement must be **in place** (http://en.wikipedia.org/wiki/In-place_algorithm) and use only constant extra memory.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3]
// Output: [1,3,2]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,2,1]
// Output: [1,2,3]
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,1,5]
// Output: [1,5,1]
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 100`
// - `0 <= nums[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Built-in
class Solution {
 public:
  void nextPermutation(vector<int>& nums) {  //
    next_permutation(nums.begin(), nums.end());
  }
};

// Algorithm:
// 1. Find last i such that a[i] < a[i+1]
// 2. Find minimal a[j] > a[i] with j > i
// 3. Swap a[i] and a[j], and reverse a[i+1 ... n-1]
//
// Explain:
// In order to find the next lexicographically greater permutation, we need to "increase" the array.
// If the array is decreasing, we can't increase it by permutation.
//
// We use [2 3 6 5 4 1] as an example.
//
// We first find the last increasing point 3->6. Note that [6 5 4 1] is already maximum.
//
// Next we want to slightly increate 3; that is, find the minimal greater value after it.
// Note that since [6 5 4 1] is decreasing, it is the same as finding the last greater value.
// Here we find 4.
//
// Next we swap 3 and 4. Now the array becomes [2 '4' 6 5 '3' 1].
// Note that after swapping, the tail subarray [6 5 3 1] is still decreasing
// (since everything after 4 is smaller than 3).
//
// Finally, since we increase 3 to 4, the tail must be the minimize.
// We reverse the tail subarray (since it was decreasing).
class Solution2 {
  using Iter = vector<int>::reverse_iterator;

 public:
  void nextPermutation(vector<int>& nums) {  //
    int n = nums.size();
    if (n <= 1) return;

    // Find last increasing point
    auto it1 = find_last_inc(nums);

    // Last premutation
    if (it1 == nums.rend()) {
      reverse(nums.rbegin(), nums.rend());
      return;
    }

    // Find last greater
    auto it2 = upper_bound(nums.rbegin(), it1, *it1);

    // Get next permutation
    iter_swap(it1, it2);
    reverse(nums.rbegin(), it1);
  }

 private:
  inline Iter find_last_inc(vector<int>& nums) {
    for (auto it = nums.rbegin() + 1; it != nums.rend(); ++it) {
      if (*it < *(it - 1)) return it;
    }
    return nums.rend();
  }
};
