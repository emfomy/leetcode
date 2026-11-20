// Source: https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii
// Title: Maximum Frequency of an Element After Performing Operations II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and two integers `k` and `numOperations`.
//
// You must perform an **operation** `numOperations` times on `nums`, where in each operation you:
//
// - Select an index `i` that was **not** selected in any previous operations.
// - Add an integer in the range `[-k, k]` to `nums[i]`.
//
// Return the **maximum** possible <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:r1v:" data-state="closed" class="">frequency</button> of any element in `nums` after performing the **operations**.
//
// **Example 1:**
//
// ```
// Input: nums = [1,4,5], k = 1, numOperations = 2
// Output: 2
// Explanation:
// We can achieve a maximum frequency of two by:
// - Adding 0 to `nums[1]`, after which `nums` becomes `[1, 4, 5]`.
// - Adding -1 to `nums[2]`, after which `nums` becomes `[1, 4, 4]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [5,11,20,20], k = 5, numOperations = 1
// Output: 2
// Explanation:
// We can achieve a maximum frequency of two by:
// - Adding 0 to `nums[1]`.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `0 <= k <= 10^9`
// - `0 <= numOperations <= nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Diff Array
//
// For each number x, we treat it as an interval [x-k, x+k].
//
// Assuming that numOperations is large enough.
// Now the problems becomes the maximum number of interval among all positions.
// We can use diff array to solve it.
//
// If the numOperations is not large enough,
// we also count the numbers among all positions.
// The frequency is equal to min(#intervals, count + numOperations)
class Solution {
 public:
  int maxFrequency(vector<int>& nums, int k, int numOperations) {
    auto diffs = unordered_map<int, int>();
    auto counts = unordered_map<int, int>();
    auto numSet = unordered_set<int>();

    // Prepare
    for (auto num : nums) {
      auto left = num - k, right = num + k + 1;
      ++counts[num];
      ++diffs[left];
      --diffs[right];
      numSet.insert(num);
      numSet.insert(left);
      numSet.insert(right);
    }

    // Sort number
    nums = vector<int>(numSet.cbegin(), numSet.cend());
    sort(nums.begin(), nums.end());

    auto ans = 0, intervals = 0;
    for (auto num : nums) {
      auto dIt = diffs.find(num);
      auto cIt = counts.find(num);
      auto diff = dIt == diffs.cend() ? 0 : dIt->second;
      auto count = cIt == counts.cend() ? 0 : cIt->second;

      intervals += diff;
      ans = max(ans, min(intervals, count + numOperations));
    }

    return ans;
  }
};

// Sort + Three pointer
//
// First sort nums.
//
// Use three pointers,
// cIdx points to num, lIdx points to >=num-k, rIdx points to >num+k.
//
// Loop for cIdx.
// Find next different number (nIdx).
// Update lIdx & rIdx.
// Now nIdx-cIdx is the number of current numbers.
// Now rIdx-lIdx is the number of neighbour numbers within [-k, k] range.
//
// Note that we also need to loop for num = nums[cIdx]-k and num = nums[cIdx]+k.
class Solution2 {
 public:
  int maxFrequency(vector<int>& nums, int k, int numOperations) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    // Loop for number as center
    auto ans = 0, cIdx = 0, lIdx = 0, rIdx = 0;
    while (cIdx < n) {
      auto num = nums[cIdx];
      auto nIdx = cIdx;
      while (nIdx < n && nums[nIdx] == nums[cIdx]) ++nIdx;
      while (lIdx < n && nums[lIdx] < num - k) ++lIdx;
      while (rIdx < n && nums[rIdx] <= num + k) ++rIdx;

      auto count = nIdx - cIdx;
      auto neighbour = rIdx - lIdx;
      ans = max(ans, min(neighbour, count + numOperations));

      cIdx = nIdx;
    }

    // Loop for number-k as center
    cIdx = 0, lIdx = 0, rIdx = 0;
    while (cIdx < n) {
      int64_t num = nums[cIdx] - k;
      auto nIdx = cIdx;
      while (nIdx < n && nums[nIdx] == nums[cIdx]) ++nIdx;
      while (lIdx < n && nums[lIdx] < num - k) ++lIdx;
      while (rIdx < n && nums[rIdx] <= num + k) ++rIdx;

      auto neighbour = rIdx - lIdx;
      ans = max(ans, min(neighbour, numOperations));

      cIdx = nIdx;
    }

    // Loop for number+k as center
    cIdx = 0, lIdx = 0, rIdx = 0;
    while (cIdx < n) {
      int64_t num = nums[cIdx] + k;
      auto nIdx = cIdx;
      while (nIdx < n && nums[nIdx] == nums[cIdx]) ++nIdx;
      while (lIdx < n && nums[lIdx] < num - k) ++lIdx;
      while (rIdx < n && nums[rIdx] <= num + k) ++rIdx;

      auto neighbour = rIdx - lIdx;
      ans = max(ans, min(neighbour, numOperations));

      cIdx = nIdx;
    }

    return ans;
  }
};

// Sort + Five pointer
//
// First sort nums.
//
// Use five pointers, points to num+(-2k, -k, 0, 2k, +2k).
// For num   as center, we focus on [-k, k] interval.
// For num-k as center, we focus on [-2k, 0] interval.
// For num+k as center, we focus on [0, 2k] interval.
class Solution3 {
 public:
  int maxFrequency(vector<int>& nums, int k, int numOperations) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    // Loop for number as center
    auto ans = 0, cIdx = 0, lIdx = 0, l2Idx = 0, rIdx = 0, r2Idx = 0;
    while (cIdx < n) {
      int64_t num = nums[cIdx];
      auto nIdx = cIdx;
      while (nIdx < n && nums[nIdx] == num) ++nIdx;
      while (lIdx < n && nums[lIdx] < num - k) ++lIdx;
      while (rIdx < n && nums[rIdx] <= num + k) ++rIdx;
      while (l2Idx < n && nums[l2Idx] < num - 2 * k) ++l2Idx;
      while (r2Idx < n && nums[r2Idx] <= num + 2 * k) ++r2Idx;

      auto count = nIdx - cIdx;
      auto midCount = rIdx - lIdx;
      auto leftCount = nIdx - l2Idx;
      auto rightCount = r2Idx - cIdx;
      ans = max(ans, min(midCount, count + numOperations));
      ans = max(ans, min(leftCount, numOperations));
      ans = max(ans, min(rightCount, numOperations));

      cIdx = nIdx;
    }

    return ans;
  }
};
