// Source: https://leetcode.com/problems/course-schedule-ii
// Title: Course Schedule II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [a_i, b_i]` indicates that you **must** take course `b_i` first if you want to take course `a_i`.
//
// - For example, the pair `[0, 1]`, indicates that to take course `0` you have to first take course `1`.
//
// Return the ordering of courses you should take to finish all courses. If there are many valid answers, return **any** of them. If it is impossible to finish all courses, return **an empty array**.
//
// **Example 1:**
//
// ```
// Input: numCourses = 2, prerequisites = [[1,0]]
// Output: [0,1]
// Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
// ```
//
// **Example 2:**
//
// ```
// Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
// Output: [0,2,1,3]
// Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
// So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
// ```
//
// **Example 3:**
//
// ```
// Input: numCourses = 1, prerequisites = []
// Output: [0]
// ```
//
// **Constraints:**
//
// - `1 <= numCourses <= 2000`
// - `0 <= prerequisites.length <= numCourses * (numCourses - 1)`
// - `prerequisites[i].length == 2`
// - `0 <= a_i, b_i < numCourses`
// - `a_i != b_i`
// - All the pairs `[a_i, b_i]` are **distinct**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Topology Sort
class Solution {
 public:
  vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
    // Construct
    auto inDegrees = vector<int>(n);
    auto graph = unordered_map<int, vector<int>>();  // pre -> posts
    for (auto& pair : prerequisites) {
      auto post = pair[0], pre = pair[1];
      graph[pre].push_back(post);
      inDegrees[post]++;
    }

    // Prepare
    auto ans = vector<int>();
    auto que = queue<int>();  // nodes with zero in-degree
    for (auto i = 0; i < n; ++i) {
      if (inDegrees[i] == 0) que.push(i);
    }

    // Loop
    while (!que.empty()) {
      auto node = que.front();
      que.pop();
      ans.push_back(node);

      for (auto post : graph[node]) {
        if (--inDegrees[post] == 0) que.push(post);
      }
    }

    return (ans.size() == n) ? ans : vector<int>();
  }
};
