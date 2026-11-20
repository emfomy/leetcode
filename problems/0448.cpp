// Source: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array
// Title: Find All Numbers Disappeared in an Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `nums` of `n` integers where `nums[i]` is in the range `[1, n]`, return an array of all the integers in the range `[1, n]` that do not appear in `nums`.
//
// **Example 1:**
//
// ```
// Input: nums = [4,3,2,7,8,2,3,1]
// Output: [5,6]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,1]
// Output: [2]
// ```
//
// **Constraints:**
//
// - `n == nums.length`
// - `1 <= n <= 10^5`
// - `1 <= nums[i] <= n`
//
// **Follow up:** Could you do it without extra space and in `O(n)` runtime? You may assume the returned list does not count as extra space.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <unordered_set>
#include <vector>

using namespace std;

// Hash Set
class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();

    // Insert
    auto numSet = unordered_set<int>();
    for (auto num = 1; num <= n; ++num) numSet.insert(num);

    // Erase
    for (auto num : nums) numSet.erase(num);

    // Answer
    auto ans = vector<int>();
    for (auto num : numSet) ans.push_back(num);

    return ans;
  }
};

// Two pointer
class Solution2 {
 public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();

    // Fill the answer
    auto ans = vector<int>(n);
    iota(ans.begin(), ans.end(), 1);

    // Erase
    for (auto num : nums) ans[num - 1] = 0;

    // Swap zero to end
    auto left = 0, right = n;
    while (left < right) {
      if (ans[left] != 0) {
        ++left;
      } else {
        --right;
        swap(ans[left], ans[right]);
      }
    }
    ans.resize(right);

    return ans;
  }
};
