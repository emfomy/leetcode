// Source: https://leetcode.com/problems/find-missing-elements
// Title: Find Missing Elements
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` consisting of **unique** integers.
//
// Originally, `nums` contained **every integer** within a certain range. However, some integers might have gone **missing** from the array.
//
// The **smallest** and **largest** integers of the original range are still present in `nums`.
//
// Return a **sorted** list of all the missing integers in this range. If no integers are missing, return an **empty** list.
//
// **Example 1:**
//
// ```
// Input: nums = [1,4,2,5]
// Output: [3]
// Explanation:
// The smallest integer is 1 and the largest is 5, so the full range should be `[1,2,3,4,5]`. Among these, only 3 is missing.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [7,8,6,9]
// Output: []
// Explanation:
// The smallest integer is 6 and the largest is 9, so the full range is `[6,7,8,9]`. All integers are already present, so no integer is missing.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [5,1]
// Output: [2,3,4]
// Explanation:
// The smallest integer is 1 and the largest is 5, so the full range should be `[1,2,3,4,5]`. The missing integers are 2, 3, and 4.
// ```
//
// **Constraints:**
//
// - `2 <= nums.length <= 100`
// - `1 <= nums[i] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

// Hash Set
class Solution {
 public:
  vector<int> findMissingElements(const vector<int>& nums) {
    const int n = nums.size();

    int minNum = *min_element(nums.cbegin(), nums.cend());
    int maxNum = *max_element(nums.cbegin(), nums.cend());
    auto numSet = unordered_set<int>(nums.cbegin(), nums.cend());

    auto ans = vector<int>();
    ans.reserve(n);
    for (int num = minNum; num <= maxNum; ++num) {
      if (!numSet.contains(num)) ans.push_back(num);
    }

    return ans;
  }
};

// Hash Set
//
// Use boolean array as hash set
class Solution2 {
  using Bool = unsigned char;

 public:
  vector<int> findMissingElements(const vector<int>& nums) {
    const int n = nums.size();

    int minNum = *min_element(nums.cbegin(), nums.cend());
    int maxNum = *max_element(nums.cbegin(), nums.cend());
    auto numSet = vector<Bool>(101);
    for (int num : nums) {
      numSet[num] = true;
    }

    auto ans = vector<int>();
    ans.reserve(n);
    for (int num = minNum; num <= maxNum; ++num) {
      if (!numSet[num]) ans.push_back(num);
    }

    return ans;
  }
};
