// Source: https://leetcode.com/problems/evaluate-division
// Title: Evaluate Division
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of variable pairs `equations` and an array of real numbers `values`, where `equations[i] = [A_i, B_i]` and `values[i]` represent the equation `A_i / B_i = values[i]`. Each `A_i` or `B_i` is a string that represents a single variable.
//
// You are also given some `queries`, where `queries[j] = [C_j, D_j]` represents the `j^th` query where you must find the answer for `C_j / D_j = ?`.
//
// Return the answers to all queries. If a single answer cannot be determined, return `-1.0`.
//
// **Note:** The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.
//
// **Note:**The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.
//
// **Example 1:**
//
// ```
// Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
// Explanation:
// Given: a / b = 2.0, b / c = 3.0
// queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
// return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
// note: x is undefined => -1.0```
//
// **Example 2:**
//
// ```
// Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
// Output: [3.75000,0.40000,5.00000,0.20000]
// ```
//
// **Example 3:**
//
// ```
// Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
// Output: [0.50000,2.00000,-1.00000,-1.00000]
// ```
//
// **Constraints:**
//
// - `1 <= equations.length <= 20`
// - `equations[i].length == 2`
// - `1 <= A_i.length, B_i.length <= 5`
// - `values.length == equations.length`
// - `0.0 < values[i] <= 20.0`
// - `1 <= queries.length <= 20`
// - `queries[i].length == 2`
// - `1 <= C_j.length, D_j.length <= 5`
// - `A_i, B_i, C_j, D_j` consist of lower case English letters and digits.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <deque>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Use Graph + BFS
class Solution {
 public:
  vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    int n = equations.size();

    // Create graph
    auto graph = unordered_map<string, vector<pair<string, double>>>();  // node -> (mode, ratio)

    for (auto i = 0; i < n; i++) {
      auto x = equations[i][0];
      auto y = equations[i][1];
      auto r = values[i];
      graph[x].push_back({y, r});
      graph[y].push_back({x, 1.0 / r});
    }

    // BFS
    auto bfs = [&](string start, string end) -> double {
      if (!graph.contains(start) || !graph.contains(end)) return -1.0;  // invalid

      auto queue = deque<pair<string, double>>();  // node, product
      auto visited = unordered_map<string, bool>();

      queue.push_back({start, 1.0});
      while (!queue.empty()) {
        auto [curr, prod] = queue.front();
        queue.pop_front();

        if (visited[curr]) continue;
        visited[curr] = true;

        if (curr == end) return prod;

        for (auto [next, ratio] : graph[curr]) {
          queue.push_back({next, ratio * prod});
        }
      }

      return -1.0;
    };

    auto ans = vector<double>();
    ans.reserve(queries.size());
    for (auto& query : queries) {
      ans.push_back(bfs(query[0], query[1]));
    }

    return ans;
  }
};

// Union-Find
class Solution2 {
  struct UnionFind {
    unordered_map<string, string> parents;
    unordered_map<string, int> ranks;
    unordered_map<string, double> ratios;  // parent / self

    void insert(string x) {
      parents[x] = x;
      ranks[x] = 0;
      ratios[x] = 1.0;
    }

    pair<string, double> find(string x) {  // return parent and parent / self
      if (!parents.contains(x)) return {"", -1.0};

      if (parents[x] != x) {
        auto [p, r] = find(parents[x]);
        parents[x] = p;
        ratios[x] *= r;
      }
      return {parents[x], ratios[x]};
    }

    void unite(string x, string y, double r) {  // r = x / y
      auto [px, rx] = find(x);                  // rx = px / x
      auto [py, ry] = find(y);                  // ry = py / y
      if (px == py) return;

      // Ensure rank(px) >= rank(py)
      if (ranks[px] < ranks[py]) {
        swap(x, y);
        swap(px, py);
        swap(rx, ry);
        r = 1.0 / r;
      }

      // Merge py into px
      if (ranks[px] == ranks[py]) ++ranks[px];
      parents[py] = px;
      ratios[py] *= rx * r / ry;  // px / py = px/x * x/y * y/py
    }
  };

 public:
  vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    int n = equations.size();

    // Init
    auto uf = UnionFind();
    for (auto i = 0; i < n; ++i) {
      auto x = equations[i][0], y = equations[i][1];
      uf.insert(x);
      uf.insert(y);
    }

    // Union
    for (auto i = 0; i < n; ++i) {
      auto x = equations[i][0], y = equations[i][1];
      auto r = values[i];
      uf.unite(x, y, r);
    }

    // Query
    auto ans = vector<double>();
    for (auto& query : queries) {
      auto x = query[0], y = query[1];
      auto [px, rx] = uf.find(x);
      auto [py, ry] = uf.find(y);

      if (px == "" || py == "" || px != py) {
        ans.push_back(-1);
      } else {
        ans.push_back(ry / rx);  // x/y = x/p * p/y
      }
    }

    return ans;
  }
};
