// Source: https://leetcode.com/problems/course-schedule-iii
// Title: Course Schedule III
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` different online courses numbered from `1` to `n`. You are given an array `courses` where `courses[i] = [duration_i, lastDay_i]` indicate that the `i^th` course should be taken **continuously** for `duration_i` days and must be finished before or on `lastDay_i`.
//
// You will start on the `1^st` day and you cannot take two or more courses simultaneously.
//
// Return the maximum number of courses that you can take.
//
// **Example 1:**
//
// ```
// Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
// Output: 3
// Explanation:
// There are totally 4 courses, but you can take 3 courses at most:
// First, take the 1^st course, it costs 100 days so you will finish it on the 100^th day, and ready to take the next course on the 101^st day.
// Second, take the 3^rd course, it costs 1000 days so you will finish it on the 1100^th day, and ready to take the next course on the 1101^st day.
// Third, take the 2^nd course, it costs 200 days so you will finish it on the 1300^th day.
// The 4^th course cannot be taken now, since you will finish it on the 3300^th day, which exceeds the closed date.
// ```
//
// **Example 2:**
//
// ```
// Input: courses = [[1,2]]
// Output: 1
// ```
//
// **Example 3:**
//
// ```
// Input: courses = [[3,2],[4,3]]
// Output: 0
// ```
//
// **Constraints:**
//
// - `1 <= courses.length <= 10^4`
// - `1 <= duration_i, lastDay_i <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// Greedy + Heap
//
// We discover below greedy property:
// For any two started courses, it is always better to take the shorter one.
//
// We sort the courses by "lastDay",
// and use a max-heap to store the picked courses.
//
// For each course, we pick it if possible.
// If we can't pick the course, we drop a longer picked course (by above greedy property).
// Since the dropped courses ends early, we don't need to consider it anymore.
class Solution {
 public:
  int scheduleCourse(vector<vector<int>>& courses) {
    // Sort by last day ASC, and by duration ASC
    const auto comp = [](const vector<int>& a, const vector<int>& b) -> bool {
      return a[1] != b[1] ? a[1] < b[1] : a[0] < b[0];
    };
    sort(courses.begin(), courses.end(), comp);

    // Loop
    int now = 0;
    auto heap = priority_queue<int>();  // taken courses
    for (const auto& course : courses) {
      const int duration = course[0], lastDay = course[1];

      // Take the course
      if (now + duration <= lastDay) {
        now += duration;
        heap.push(duration);
        continue;
      }

      // Swap the course
      if (!heap.empty() && duration < heap.top()) {
        now += duration - heap.top();
        heap.pop();
        heap.push(duration);
      }
    }

    return heap.size();
  }
};
