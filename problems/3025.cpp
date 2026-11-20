// Source: https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i
// Title: Find the Number of Ways to Place People I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D array `points` of size `n x 2` representing integer coordinates of some points on a 2D plane, where `points[i] = [x_i, y_i]`.
//
// Count the number of pairs of points `(A, B)`, where
//
// - `A` is on the **upper left** side of `B`, and
// - there are no other points in the rectangle (or line) they make (**including the border**).
//
// Return the count.
//
// **Example 1:**
//
// ```
// Input: points = [[1,1],[2,2],[3,3]]
// Output: 0
// Explanation:
// https://assets.leetcode.com/uploads/2024/01/04/example1alicebob.png
// There is no way to choose `A` and `B` so `A` is on the upper left side of `B`.
// ```
//
// **Example 2:**
//
// ```
// Input: points = [[6,2],[4,4],[2,6]]
// Output: 2
// Explanation:
// https://assets.leetcode.com/uploads/2024/06/25/t2.jpg
// - The left one is the pair `(points[1], points[0])`, where `points[1]` is on the upper left side of `points[0]` and the rectangle is empty.
// - The middle one is the pair `(points[2], points[1])`, same as the left one it is a valid pair.
// - The right one is the pair `(points[2], points[0])`, where `points[2]` is on the upper left side of `points[0]`, but `points[1]` is inside the rectangle so it's not a valid pair.
// ```
//
// **Example 3:**
//
// ```
// Input: points = [[3,1],[1,3],[1,1]]
// Output: 2
// Explanation:
// https://assets.leetcode.com/uploads/2024/06/25/t3.jpg
// - The left one is the pair `(points[2], points[0])`, where `points[2]` is on the upper left side of `points[0]` and there are no other points on the line they form. Note that it is a valid state when the two points form a line.
// - The middle one is the pair `(points[1], points[2])`, it is a valid pair same as the left one.
// - The right one is the pair `(points[1], points[0])`, it is not a valid pair as `points[2]` is on the border of the rectangle.
// ``
//
// **Constraints:**
//
// - `2 <= n <= 50`
// - `points[i].length == 2`
// - `0 <= points[i][0], points[i][1] <= 50`
// - All `points[i]` are distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>
using namespace std;

// Use Sort, O(n^2)
//
// First sort by x coordinate.
//
// For each point A, check all point at its right.
// If the right point is lower, it is an candidate.
//
// To check if there is any point in the rectangle,
// we track the largest y coordinate below A.
// If the right point is lower that number, it is invalid.
class Solution {
 public:
  int numberOfPairs(vector<vector<int>>& points) {
    int n = points.size();

    // Sort
    sort(points.begin(), points.end(), [](const auto& a, const auto& b) -> bool {
      return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
    });  // sort by x asc and y desc

    // Loop
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      auto yi = points[i][1];
      auto ymax = -1;
      for (auto j = i + 1; j < n; ++j) {
        auto yj = points[j][1];
        if (yj > yi || yj <= ymax) continue;
        ++ans;
        ymax = yj;
      }
    }

    return ans;
  }
};
