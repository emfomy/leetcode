// Source: https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals
// Title: Maximum Score of Non-overlapping Intervals
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D integer array `intervals`, where `intervals[i] = [l_i, r_i, weight_i]`. Interval `i` starts at position `l_i` and ends at `r_i`, and has a weight of `weight_i`. You can choose up to 4 **non-overlapping** intervals. The **score** of the chosen intervals is defined as the total sum of their weights.
//
// Return the **lexicographically smallest** array of at most 4 indices from `intervals` with **maximum** score, representing your choice of non-overlapping intervals.
//
// Two intervals are said to be **non-overlapping** if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.
//
// **Example 1:**
//
// ```
// Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
// Output: [2,3]
// Explanation:
// You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.
// ```
//
// **Example 2:**
//
// ```
// Input: intervals = [[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]
// Output: [1,3,5,6]
// Explanation:
// You can choose the intervals with indices 1, 3, 5, and 6 with respective weights of 7, 6, 3, and 5.
// ```
//
// **Constraints:**
//
// - `1 <= intevals.length <= 5 * 10^4`
// - `intervals[i].length == 3`
// - `intervals[i] = [l_i, r_i, weight_i]`
// - `1 <= l_i <= r_i <= 10^9`
// - `1 <= weight_i <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// DP + Binary Search
//
// See Problem 1751 with k = 4.
class Solution {
  static constexpr int k = 4;

  struct Item {
    int l;
    int r;
    int w;  // weight
    int i;  // original index
  };

 public:
  vector<int> maximumWeight(const vector<vector<int>>& intervals) {
    const int n = intervals.size();

    // Prepare
    auto items = vector<Item>();
    items.reserve(n);
    for (int i = 0; i < n; ++i) {
      int l = intervals[i][0];
      int r = intervals[i][1];
      int w = intervals[i][2];
      items.emplace_back(l, r, w, i);
    }

    // Sort
    const auto comp = [](const Item& a, const Item& b) -> bool {  //
      return a.l < b.l;
    };
    sort(items.begin(), items.end(), comp);

    // DP
    auto memo = vector(k + 1, vector<long long>(n + 1, 0));
    auto idxs = vector(k + 1, vector<vector<int>>(n + 1));
    for (int i = n - 1; i >= 0; --i) {
      // Find next item
      const auto cond = [end = items[i].r](const Item& x) -> bool {  //
        return !(x.l > end);
      };
      int nextIdx = partition_point(items.cbegin() + i, items.cend(), cond) - items.cbegin();

      for (int t = k - 1; t >= 0; --t) {
        long long dp1 = memo[t][i + 1];
        long long dp2 = memo[t + 1][nextIdx] + items[i].w;

        // skip current item
        if (dp1 > dp2) {
          memo[t][i] = dp1;
          idxs[t][i] = idxs[t][i + 1];
          continue;
        }

        // use current item
        memo[t][i] = dp2;

        auto& newIdx = idxs[t][i];
        newIdx = idxs[t + 1][nextIdx];
        newIdx.push_back(items[i].i);
        sort(newIdx.begin(), newIdx.end());

        // skip if new set is lexicographically larger
        if (dp1 == dp2 && newIdx > idxs[t][i + 1]) {
          newIdx = idxs[t][i + 1];
        }
      }
    }

    return idxs[0][0];
  }
};
