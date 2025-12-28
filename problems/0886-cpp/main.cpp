// Source: https://leetcode.com/problems/possible-bipartition
// Title: Possible Bipartition
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// We want to split a group of `n` people (labeled from `1` to `n`) into two groups of **any size**. Each person may dislike some other people, and they should not go into the same group.
//
// Given the integer `n` and the array `dislikes` where `dislikes[i] = [a_i, b_i]` indicates that the person labeled `a_i` does not like the person labeled `b_i`, return `true` if it is possible to split everyone into two groups in this way.
//
// **Example 1:**
//
// ```
// Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
// Output: true
// Explanation: The first group has [1,4], and the second group has [2,3].
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, dislikes = [[1,2],[1,3],[2,3]]
// Output: false
// Explanation: We need at least 3 groups to divide them. We cannot put them in two groups.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 2000`
// - `0 <= dislikes.length <= 10^4`
// - `dislikes[i].length == 2`
// - `1 <= a_i < b_i <= n`
// - All the pairs of `dislikes` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// BFS
class Solution {
 public:
  bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
    // Construct graph
    auto graph = vector<vector<int>>(n);
    for (auto& dislike : dislikes) {
      auto a = dislike[0] - 1, b = dislike[1] - 1;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }

    // Prepare
    auto que = queue<int>();
    auto colors = vector<int>(n, 0);  // 0: unknown, +-1: color

    // Loop
    for (auto start = 0; start < n; ++start) {
      if (colors[start] != 0) continue;  // visited
      que.push(start);
      colors[start] = 1;

      while (!que.empty()) {
        auto node = que.front();
        auto color = colors[node];
        que.pop();

        for (auto next : graph[node]) {
          if (colors[next] != 0) {  // visited
            if (colors[next] == color) return false;
          } else {  // not visited
            colors[next] = -color;
            que.push(next);
          }
        }
      }
    }

    return true;
  }
};
