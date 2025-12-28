// Source: https://leetcode.com/problems/course-schedule
// Title: Course Schedule
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [a_i, b_i]` indicates that you **must** take course `b_i` first if you want to take course `a_i`.
//
// - For example, the pair `[0, 1]`, indicates that to take course `0` you have to first take course `1`.
//
// Return `true` if you can finish all courses. Otherwise, return `false`.
//
// **Example 1:**
//
// ```
// Input: numCourses = 2, prerequisites = [[1,0]]
// Output: true
// Explanation: There are a total of 2 courses to take.
// To take course 1 you should have finished course 0. So it is possible.
// ```
//
// **Example 2:**
//
// ```
// Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
// Output: false
// Explanation: There are a total of 2 courses to take.
// To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
// ```
//
// **Constraints:**
//
// - `1 <= numCourses <= 2000`
// - `0 <= prerequisites.length <= 5000`
// - `prerequisites[i].length == 2`
// - `0 <= a_i, b_i < numCourses`
// - All the pairs prerequisites[i] are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Topology Sort
class Solution {
 public:
  bool canFinish(int n, vector<vector<int>>& prerequisites) {
    // Construct
    auto inDegrees = vector<int>(n);
    auto graph = unordered_map<int, vector<int>>();  // pre -> posts
    for (auto& pair : prerequisites) {
      auto post = pair[0], pre = pair[1];
      graph[pre].push_back(post);
      inDegrees[post]++;
    }

    // Prepare
    auto visited = 0;
    auto que = queue<int>();  // nodes with zero in-degree
    for (auto i = 0; i < n; ++i) {
      if (inDegrees[i] == 0) que.push(i);
    }

    // Loop
    while (!que.empty()) {
      auto node = que.front();
      que.pop();
      ++visited;

      for (auto post : graph[node]) {
        if (--inDegrees[post] == 0) que.push(post);
      }
    }

    return visited == n;
  }
};
