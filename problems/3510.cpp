// Source: https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii
// Title: Minimum Pair Removal to Sort Array II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `nums`, you can perform the following operation any number of times:
//
// - Select the **adjacent** pair with the **minimum** sum in `nums`. If multiple such pairs exist, choose the leftmost one.
// - Replace the pair with their sum.
//
// Return the **minimum number of operations** needed to make the array **non-decreasing**.
//
// An array is said to be **non-decreasing** if each element is greater than or equal to its previous element (if it exists).
//
// **Example 1:**
//
// ```
// Input: nums = [5,2,3,1]
// Output: 2
// Explanation:
// - The pair `(3,1)` has the minimum sum of 4. After replacement, `nums = [5,2,4]`.
// - The pair `(2,4)` has the minimum sum of 6. After replacement, `nums = [5,6]`.
// The array `nums` became non-decreasing in two operations.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,2]
// Output: 0
// Explanation:
// The array `nums` is already sorted.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `-10^9 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <cstdint>
#include <list>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// Simulation
class Solution {
 public:
  int minimumPairRemoval(vector<int>& nums) {
    auto nums64 = vector<int64_t>(nums.cbegin(), nums.cend());
    int n = nums64.size();

    // Helper
    auto check = [&]() -> bool {
      for (auto i = 0; i < nums64.size() - 1; ++i) {
        if (nums64[i] > nums64[i + 1]) return false;
      }
      return true;
    };

    // Loop
    auto ans = 0;
    while (!check()) {
      ++ans;

      // Find minimal
      auto minSum = nums64[0] + nums64[1];
      auto minIdx = 0;
      for (auto i = 1; i < nums64.size() - 1; ++i) {
        auto sum = nums64[i] + nums64[i + 1];
        if (minSum > sum) {
          minSum = sum;
          minIdx = i;
        }
      }

      nums64[minIdx] = minSum;
      nums64.erase(nums64.cbegin() + minIdx + 1);
    }

    return ans;
  }
};

// Linked List + Heap
//
// Use a boolean array for valid start ranges.
// Use an array to for the end of each range. (ignored for invalid start)
// Use a heap for pair sums.
//
// For the terminal condition, we count the number of bad pairs.
// For each merge, update this number.
// The algorithm ends when bad pairs is zero.
class Solution2 {
  using Pair = tuple<int64_t, int, int>;  // sum, start, end

 public:
  int minimumPairRemoval(vector<int>& nums) {
    int n = nums.size();

    // Init
    auto badCount = 0;
    auto merged = vector<bool>(n + 1);
    auto vals = vector<int64_t>(n + 1);
    auto prev = vector<int>(n + 1);  // previous index
    auto next = vector<int>(n + 1);  // next index
    for (auto i = 0; i <= n; ++i) {
      vals[i] = i < n ? nums[i] : INT64_MAX;
      prev[i] = i - 1;
      next[i] = i + 1;
    }

    auto heap = priority_queue(greater(), std::move(vector<Pair>()));  // min-heap
    for (auto i = 0; i < n - 1; ++i) {
      int64_t left = vals[i], right = vals[i + 1];
      badCount += (left > right);
      heap.emplace(left + right, i, i + 2);
    }

    // Loop
    auto ans = 0;
    while (badCount > 0) {
      auto [sum, lo, hi] = heap.top();
      heap.pop();

      // Check merged
      if (merged[lo] || merged[hi] || next[lo] != prev[hi]) continue;
      ++ans;

      auto mid = next[lo], lo2 = prev[lo], hi2 = next[hi];
      auto left = vals[lo], right = vals[mid];
      auto before = lo2 >= 0 ? vals[lo2] : INT64_MIN;
      auto after = hi <= n ? vals[hi] : INT64_MAX;

      // Update count
      badCount -= (before > left) + (left > right) + (right > after);
      badCount += (before > sum) + (sum > after);

      // Merge
      merged[mid] = true;
      vals[lo] = sum;
      next[lo] = hi;
      prev[hi] = lo;

      // Insert
      if (lo2 >= 0) heap.emplace(before + sum, lo2, hi);
      if (hi2 <= n) heap.emplace(sum + after, lo, hi2);
    }

    return ans;
  }
};
