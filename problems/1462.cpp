// Source: https://leetcode.com/problems/course-schedule-iv
// Title: Course Schedule IV
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [a_i, b_i]` indicates that you **must** take course `a_i` first if you want to take course `b_i`.
//
// - For example, the pair `[0, 1]` indicates that you have to take course `0` before you can take course `1`.
//
// Prerequisites can also be **indirect**. If course `a` is a prerequisite of course `b`, and course `b` is a prerequisite of course `c`, then course `a` is a prerequisite of course `c`.
//
// You are also given an array `queries` where `queries[j] = [u_j, v_j]`. For the `j^th` query, you should answer whether course `u_j` is a prerequisite of course `v_j` or not.
//
// Return **a boolean array `answer`, where `answer[j]` is the answer to the `j^th` query.**
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/05/01/courses4-1-graph.jpg
//
// ```
// Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
// Output: [false,true]
// Explanation: The pair [1, 0] indicates that you have to take course 1 before you can take course 0.
// Course 0 is not a prerequisite of course 1, but the opposite is true.
// ```
//
// **Example 2:**
//
// ```
// Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
// Output: [false,false]
// Explanation: There are no prerequisites, and each course is independent.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/05/01/courses4-3-graph.jpg
//
// ```
// Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
// Output: [true,true]
// ```
//
// **Constraints:**
//
// - `2 <= numCourses <= 100`
// - `0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)`
// - `prerequisites[i].length == 2`
// - `0 <= a_i, b_i <= numCourses - 1`
// - `a_i != b_i`
// - All the pairs `[a_i, b_i]` are **unique**.
// - The prerequisites graph has no cycles.
// - `1 <= queries.length <= 10^4`
// - `0 <= u_i, v_i <= numCourses - 1`
// - `u_i != v_i`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bitset>
#include <cstdint>
#include <queue>
#include <vector>

using namespace std;

// Dijkstra
class Solution {
  using Bool = uint8_t;

 public:
  vector<bool> checkIfPrerequisite(              //
      const int numCourses,                      //
      const vector<vector<int>>& prerequisites,  //
      const vector<vector<int>>& queries         //
  ) {
    // Init graph
    auto graph = vector<vector<int>>(numCourses);  // dependency -> dependent
    for (const auto& prerequisite : prerequisites) {
      int dependency = prerequisite[0], dependent = prerequisite[1];
      graph[dependency].push_back(dependent);
    }

    // Helper
    auto visited = vector<Bool>(numCourses);
    const auto bfs = [&graph, &visited](int from, int to) -> bool {
      fill(visited.begin(), visited.end(), 0);
      auto que = queue<int>();
      que.push(from);

      while (!que.empty()) {
        int node = que.front();
        que.pop();

        for (int next : graph[node]) {
          if (next == to) return true;
          if (visited[next]) continue;
          visited[next] = true;
          que.push(next);
        }
      }

      return false;
    };

    // Loop
    auto ans = vector<bool>();
    ans.reserve(queries.size());
    for (const auto& query : queries) {
      const int from = query[0], to = query[1];
      ans.push_back(bfs(from, to));
    }

    return ans;
  }
};

// Floyd-Warshall
class Solution2 {
  using Bool = uint8_t;

 public:
  vector<bool> checkIfPrerequisite(              //
      const int numCourses,                      //
      const vector<vector<int>>& prerequisites,  //
      const vector<vector<int>>& queries         //
  ) {
    // Init graph
    auto graph = vector<vector<Bool>>(numCourses, vector<Bool>(numCourses));  // dependency -> dependent
    for (const auto& prerequisite : prerequisites) {
      int dependency = prerequisite[0], dependent = prerequisite[1];
      graph[dependency][dependent] = true;
    }

    // Floyd-Warshall
    for (int k = 0; k < numCourses; ++k) {
      for (int i = 0; i < numCourses; ++i) {
        for (int j = 0; j < numCourses; ++j) {
          graph[i][j] = graph[i][j] || (graph[i][k] && graph[k][j]);
        }
      }
    }

    // Loop query
    auto ans = vector<bool>();
    ans.reserve(queries.size());
    for (const auto& query : queries) {
      const int from = query[0], to = query[1];
      ans.push_back(graph[from][to]);
    }

    return ans;
  }
};

// Floyd-Warshall, Bit Set
//
// Use bit set to speed up the algorithm.
class Solution3 {
  constexpr static int kMaxCourses = 100;

  using Row = bitset<kMaxCourses>;

 public:
  vector<bool> checkIfPrerequisite(              //
      const int numCourses,                      //
      const vector<vector<int>>& prerequisites,  //
      const vector<vector<int>>& queries         //
  ) {
    // Guard
    if (numCourses < 0 || numCourses > kMaxCourses) return {};

    // Init graph
    auto graph = vector<Row>(numCourses);  // dependency -> dependent
    for (const auto& prerequisite : prerequisites) {
      int dependency = prerequisite[0], dependent = prerequisite[1];
      graph[dependency][dependent] = true;
    }

    // Floyd-Warshall
    for (int k = 0; k < numCourses; ++k) {
      for (int i = 0; i < numCourses; ++i) {
        if (graph[i][k]) graph[i] |= graph[k];
      }
    }

    // Loop query
    auto ans = vector<bool>();
    ans.reserve(queries.size());
    for (const auto& query : queries) {
      const int from = query[0], to = query[1];
      ans.push_back(graph[from][to]);
    }

    return ans;
  }
};
