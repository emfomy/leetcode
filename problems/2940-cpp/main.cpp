// Source: https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet
// Title: Find Building Where Alice and Bob Can Meet
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** array `heights` of positive integers, where `heights[i]` represents the height of the `i^th` building.
//
// If a person is in building `i`, they can move to any other building `j` if and only if `i < j` and `heights[i] < heights[j]`.
//
// You are also given another array `queries` where `queries[i] = [a_i, b_i]`. On the `i^th` query, Alice is in building `a_i` while Bob is in building `b_i`.
//
// Return an array `ans` where `ans[i]` is **the index of the leftmost building** where Alice and Bob can meet on the `i^th` query. If Alice and Bob cannot move to a common building on query `i`, set `ans[i]` to `-1`.
//
// **Example 1:**
//
// ```
// Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
// Output: [2,5,-1,5,2]
// Explanation: In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] < heights[2].
// In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] < heights[5].
// In the third query, Alice cannot meet Bob since Alice cannot move to any other building.
// In the fourth query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5].
// In the fifth query, Alice and Bob are already in the same building.
// For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
// For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.
// ```
//
// **Example 2:**
//
// ```
// Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
// Output: [7,6,-1,4,6]
// Explanation: In the first query, Alice can directly move to Bob's building since heights[0] < heights[7].
// In the second query, Alice and Bob can move to building 6 since heights[3] < heights[6] and heights[5] < heights[6].
// In the third query, Alice cannot meet Bob since Bob cannot move to any other building.
// In the fourth query, Alice and Bob can move to building 4 since heights[3] < heights[4] and heights[0] < heights[4].
// In the fifth query, Alice can directly move to Bob's building since heights[1] < heights[6].
// For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
// For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.
//
// ```
//
// **Constraints:**
//
// - `1 <= heights.length <= 5 * 10^4`
// - `1 <= heights[i] <= 10^9`
// - `1 <= queries.length <= 5 * 10^4`
// - `queries[i] = [a_i, b_i]`
// - `0 <= a_i, b_i <= heights.length - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

// Heap
//
// For each query, we need to find the leftmost building `t`,
// where max(a, b) <= t and max(h[a], h[b]) <= h[t].
//
// We first normalize on the queries.
// Let C = max(a, b), and H = max(h[a], h[b]).
// we only keep the (C, H) value for each query.
//
// Next put the queries into a multi-hashmap, mapping C to the query indices.
//
// Now loop through the buildings.
// After each building, we put the query into a min-heap (sort by height).
// For each building, if it is higher than the top of the heap,
// then Alice and Bob can meet at this build for that query (heap top).
// We record the result and pop it.
// Repeat until the top is too large.
//
// After checking each building, we know that the queries in the heap have no answer.
class Solution {
  using Query = pair<int, int>;                                       // height, index
  using Heap = priority_queue<Query, vector<Query>, greater<Query>>;  // min-heap

 public:
  vector<int> leftmostBuildingQueries(const vector<int>& heights, const vector<vector<int>>& queries) {
    const int n = heights.size(), q = queries.size();

    auto ans = vector<int>(q, -1);

    // Prepare the queries
    auto queryMap = vector<vector<Query>>(n);
    for (int qIdx = 0; qIdx < q; ++qIdx) {
      int a = queries[qIdx][0], b = queries[qIdx][1];
      if (a > b) swap(a, b);  // WLOG
      int ha = heights[a], hb = heights[b];

      // Trivial cases
      if (a == b || ha < hb) {
        ans[qIdx] = b;
        continue;
      }

      queryMap[max(a, b)].push_back({max(ha, hb), qIdx});
    }

    // Loop through the buildings
    auto heap = Heap();
    for (int bIdx = 0; bIdx < n; ++bIdx) {
      const int height = heights[bIdx];

      while (!heap.empty() && heap.top().first < height) {
        auto [_, qIdx] = heap.top();
        heap.pop();
        ans[qIdx] = bIdx;
      }

      for (auto query : queryMap[bIdx]) {
        heap.push(query);
      }
    }

    return ans;
  }
};

// Monotonic Stack + Binary Search
//
// Instead of using heap on the queries, we use monotonic stack on the building instead.
// We scan from right to the left, and put the buildings into a monotonic stack.
// The monotonic stack is increasing (from right to left).
//
// For each building, for each query linked to that building,
// use binary search on the monotonic stack to find the result.
class Solution2 {
  struct Query {
    int height;
    int index;
  };

  struct Building {
    int height;
    int index;
  };

  using Stack = vector<Building>;

 public:
  vector<int> leftmostBuildingQueries(const vector<int>& heights, const vector<vector<int>>& queries) {
    const int n = heights.size(), q = queries.size();

    auto ans = vector<int>(q, -1);

    // Prepare the queries
    auto queryMap = vector<vector<Query>>(n);
    for (int qIdx = 0; qIdx < q; ++qIdx) {
      int a = queries[qIdx][0], b = queries[qIdx][1];
      if (a > b) swap(a, b);  // WLOG
      int ha = heights[a], hb = heights[b];

      // Trivial cases
      if (a == b || ha < hb) {
        ans[qIdx] = b;
        continue;
      }

      queryMap[max(a, b)].push_back({max(ha, hb), qIdx});
    }

    // Loop through the buildings
    auto st = vector<Building>();
    st.reserve(n);
    for (int bIdx = n - 1; bIdx >= 0; --bIdx) {
      const int bHeight = heights[bIdx];

      for (auto [qHeight, qIdx] : queryMap[bIdx]) {
        auto it = upper_bound(st.crbegin(), st.crend(), Building{qHeight, 0},
                              [](Building a, Building b) { return a.height < b.height; });
        if (it != st.crend()) {
          ans[qIdx] = it->index;
        }
      }

      while (!st.empty() && st.back().height <= bHeight) st.pop_back();
      st.push_back({bHeight, bIdx});
    }

    return ans;
  }
};
