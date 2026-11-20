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
#include <vector>

using namespace std;

// Topology Sort
class Solution {
 public:
  vector<int> findOrder(const int numCourses, const vector<vector<int>>& prerequisites) {
    // Prepare graph
    auto graph = vector<vector<int>>(numCourses);  // dependency -> dependent
    auto inDegree = vector<int>(numCourses);
    for (const auto& prerequisite : prerequisites) {
      int dependent = prerequisite[0], dependency = prerequisite[1];
      graph[dependency].push_back(dependent);
      ++inDegree[dependent];
    }

    // BFS
    auto que = queue<int>();
    auto order = vector<int>();
    order.reserve(numCourses);
    for (int course = 0; course < numCourses; ++course) {
      if (inDegree[course] == 0) {
        que.push(course);
        order.push_back(course);
      }
    }
    while (!que.empty() && order.size() < numCourses) {
      int course = que.front();
      que.pop();

      for (int dependent : graph[course]) {
        if (--inDegree[dependent] == 0) {
          que.push(dependent);
          order.push_back(dependent);
        }
      }
    }

    if (order.size() < numCourses) return {};
    return order;
  }
};

// Topology Sort
//
// Use output as queue.
class Solution2 {
 public:
  vector<int> findOrder(const int numCourses, const vector<vector<int>>& prerequisites) {
    // Prepare graph
    auto graph = vector<vector<int>>(numCourses);  // dependency -> dependent
    auto inDegree = vector<int>(numCourses);
    for (const auto& prerequisite : prerequisites) {
      int dependent = prerequisite[0], dependency = prerequisite[1];
      graph[dependency].push_back(dependent);
      ++inDegree[dependent];
    }

    // BFS
    auto order = vector<int>();
    order.reserve(numCourses);
    for (int course = 0; course < numCourses; ++course) {
      if (inDegree[course] == 0) {
        order.push_back(course);
      }
    }
    for (int i = 0; i < order.size(); ++i) {
      if (order.size() == numCourses) break;  // early stop
      int course = order[i];

      for (int dependent : graph[course]) {
        if (--inDegree[dependent] == 0) {
          order.push_back(dependent);
        }
      }
    }

    if (order.size() < numCourses) return {};
    return order;
  }
};
