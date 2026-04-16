// Source: https://leetcode.com/problems/closest-equal-element-queries
// Title: Closest Equal Element Queries
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **circular** array `nums` and an array `queries`.
//
// For each query `i`, you have to find the following:
//
// - The **minimum** distance between the element at index `queries[i]` and **any** other index `j` in the **circular** array, where `nums[j] == nums[queries[i]]`. If no such index exists, the answer for that query should be -1.
//
// Return an array `answer` of the **same** size as `queries`, where `answer[i]` represents the result for query `i`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
// Output: [2,-1,3]
// Explanation:
// - Query 0: The element at `queries[0] = 0` is `nums[0] = 1`. The nearest index with the same value is 2, and the distance between them is 2.
// - Query 1: The element at `queries[1] = 3` is `nums[3] = 4`. No other index contains 4, so the result is -1.
// - Query 2: The element at `queries[2] = 5` is `nums[5] = 3`. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: `5 -> 6 -> 0 -> 1`).
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4], queries = [0,1,2,3]
// Output: [-1,-1,-1,-1]
// Explanation:
// Each value in `nums` is unique, so no index shares the same value as the queried element. This results in -1 for all queries.
// ```
//
// **Constraints:**
//
// - `1 <= queries.length <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^6`
// - `0 <= queries[i] < nums.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>

using namespace std;

// Hash Map
//
// Group the number indices by its value.
// For each unique value, compare to the previous and next indices (circularly).
class Solution {
 public:
  vector<int> solveQueries(const vector<int>& nums, const vector<int>& queries) {
    const int n = nums.size();

    // Group numbers
    auto numMap = unordered_map<int, vector<int>>();  // value -> indices
    for (int i = 0; i < n; ++i) {
      numMap[nums[i]].push_back(i);
    }

    // Find min distance for all numbers
    auto minDists = vector<int>(n, -1);
    for (const auto& [num, idxs] : numMap) {
      const int m = idxs.size();
      if (m <= 1) continue;

      minDists[idxs[0]] = min(idxs[1] - idxs[0], n - (idxs[m - 1] - idxs[0]));
      for (int i = 1; i < m - 1; ++i) {
        minDists[idxs[i]] = min(idxs[i + 1] - idxs[i], idxs[i] - idxs[i - 1]);
      }
      minDists[idxs[m - 1]] = min(n - (idxs[m - 1] - idxs[0]), idxs[m - 1] - idxs[m - 2]);
    }

    // Loop queries
    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (const int query : queries) {
      ans.push_back(minDists[query]);
    }

    return ans;
  }
};

// Hash Map (faster when Q << N)
//
// Instead of compute all min-dist,
// we prepare the index mapping and compute queries only.
class Solution2 {
 public:
  vector<int> solveQueries(const vector<int>& nums, const vector<int>& queries) {
    const int n = nums.size();

    // Group numbers
    auto numMap = unordered_map<int, vector<int>>();  // value -> indices
    auto idxMap = vector<int>(n);                     // index in numMap
    for (int i = 0; i < n; ++i) {
      auto& idxs = numMap[nums[i]];
      idxMap[i] = idxs.size();
      idxs.push_back(i);
    }

    // Loop queries
    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (const int q : queries) {
      const auto& idxs = numMap[nums[q]];
      const int m = idxs.size();
      if (m <= 1) {
        ans.push_back(-1);
        continue;
      }

      int i = idxMap[q];
      int idx = idxs[i];
      int prevIdx = (i > 0) ? idxs[i - 1] : idxs[m - 1] - n;
      int nextIdx = (i < m - 1) ? idxs[i + 1] : idxs[0] + n;

      int minDist = min(nextIdx - idx, idx - prevIdx);
      ans.push_back(minDist);
    }

    return ans;
  }
};
