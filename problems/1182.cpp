// Source: https://leetcode.com/problems/shortest-distance-to-target-color
// Title: Shortest Distance to Target Color
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `colors`, in which there are three colors: `1`, `2` and`3`.
//
// You are also given some queries. Each query consists of two integers `i`and `c`, return the shortest distance between the given index`i` and the target color `c`. If there is no solution return `-1`.
//
// **Example 1:**
//
// ```
// Input: colors = [1,1,2,1,3,2,2,3,3], queries = [[1,3],[2,2],[6,1]]
// Output: [3,0,3]
// Explanation:
// The nearest 3 from index 1 is at index 4 (3 steps away).
// The nearest 2 from index 2 is at index 2 itself (0 steps away).
// The nearest 1 from index 6 is at index 3 (3 steps away).
// ```
//
// **Example 2:**
//
// ```
// Input: colors = [1,2], queries = [[0,3]]
// Output: [-1]
// Explanation: There is no 3 in the array.
// ```
//
// **Constraints:**
//
// - `1 <= colors.length <= 5*10^4`
// - `1 <= colors[i] <= 3`
// - `1<= queries.length <= 5*10^4`
// - `queries[i].length == 2`
// - `0 <= queries[i][0] <colors.length`
// - `1 <= queries[i][1] <= 3`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <unordered_map>
#include <vector>

using namespace std;

// Use binary search
class Solution {
 public:
  vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
    int n = colors.size();

    // Create color map
    auto colorMap = unordered_map<int, vector<int>>();  // color -> indices
    for (auto i = 0; i < n; i++) {
      colorMap[colors[i]].push_back(i);
    }

    // Query
    auto ans = vector<int>();
    for (auto& query : queries) {
      auto idx = query[0];
      auto color = query[1];

      auto it = colorMap.find(color);
      if (it == colorMap.cend()) {
        ans.push_back(-1);
      } else {
        auto& idxs = it->second;
        auto it2 = lower_bound(idxs.cbegin(), idxs.cend(), idx);
        if (it2 == idxs.cbegin()) {
          ans.push_back(idxs.front() - idx);
        } else if (it2 == idxs.cend()) {
          ans.push_back(idx - idxs.back());
        } else {
          auto leftDist = idx - *(it2 - 1);
          auto rightDist = *it2 - idx;
          ans.push_back(min(leftDist, rightDist));
        }
      }
    }

    return ans;
  }
};

// Precompute
class Solution2 {
 public:
  vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
    int n = colors.size();
    auto lefts = vector<array<int, 4>>(n);
    auto rights = vector<array<int, 4>>(n);

    // Lefts
    {
      auto idxs = array<int, 4>();
      idxs.fill(-1);
      for (auto i = 0; i < n; i++) {
        auto color = colors[i];
        idxs[color] = i;
        lefts[i] = idxs;
      }
    }

    // Rights
    {
      auto idxs = array<int, 4>();
      idxs.fill(n);
      for (auto i = n - 1; i >= 0; i--) {
        auto color = colors[i];
        idxs[color] = i;
        rights[i] = idxs;
      }
    }

    // Query
    auto ans = vector<int>();
    for (auto& query : queries) {
      auto idx = query[0];
      auto color = query[1];

      auto left = lefts[idx][color];
      auto right = rights[idx][color];
      if (left == -1 && right == n) {
        ans.push_back(-1);
      } else if (left == -1) {
        ans.push_back(right - idx);
      } else if (right == n) {
        ans.push_back(idx - left);
      } else {
        ans.push_back(min(right - idx, idx - left));
      }
    }

    return ans;
  }
};
