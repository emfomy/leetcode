// Source: https://leetcode.com/problems/the-maze-ii
// Title: The Maze II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a ball in a `maze` with empty spaces (represented as `0`) and walls (represented as `1`). The ball can go through the empty spaces by rolling **up, down, left or right**, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
//
// Given the `m x n` `maze`, the ball's `start` position and the `destination`, where `start = [start_row, start_col]` and `destination = [destination_row, destination_col]`, return the shortest **distance** for the ball to stop at the destination. If the ball cannot stop at `destination`, return `-1`.
//
// The **distance** is the number of **empty spaces** traveled by the ball from the start position (excluded) to the destination (included).
//
// You may assume that **the borders of the maze are all walls** (see examples).
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/31/maze1-1-grid.jpg
//
// ```
// Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [4,4]
// Output: 12
// Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.
// The length of the path is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/31/maze1-2-grid.jpg
//
// ```
// Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [3,2]
// Output: -1
// Explanation: There is no way for the ball to stop at the destination. Notice that you can pass through the destination but you cannot stop there.
// ```
//
// **Example 3:**
//
// ```
// Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], start = [4,3], destination = [0,1]
// Output: -1
// ```
//
// **Constraints:**
//
// - `m == maze.length`
// - `n == maze[i].length`
// - `1 <= m, n <= 100`
// - `maze[i][j]` is `0` or `1`.
// - `start.length == 2`
// - `destination.length == 2`
// - `0 <= start_row, destination_row < m`
// - `0 <= start_col, destination_col < n`
// - Both the ball and the destination exist in an empty space, and they will not be in the same position initially.
// - The maze contains **at least 2 empty spaces**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

// BFS
//
// If the previous move the vertical, the next move must be horizontal (and vise versa).
class Solution {
  using State = tuple<int, int, int, char>;  // distance, row, col, V/H (vertical & horizontal)

 public:
  int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    auto m = maze.size(), n = maze[0].size();
    auto dists = vector(m, vector(n, INT_MAX));

    auto srcRow = start[0], srcCol = start[1];
    auto dstRow = destination[0], dstCol = destination[1];

    auto que = priority_queue(greater(), std::move(vector<State>()));  // min-heap
    que.push({0, srcRow, srcCol, ' '});

    while (!que.empty()) {
      auto [dist0, row0, col0, dir0] = que.top();
      que.pop();
      if (row0 == dstRow && col0 == dstCol) return dists[dstRow][dstCol];
      if (dist0 > dists[row0][col0]) continue;

      // Down
      if (dir0 != 'V') {
        auto row = row0;
        while (row < m && maze[row][col0] == 0) ++row;  // find wall
        --row;                                          // step back
        auto dist = dist0 + (row - row0);
        if (dist < dists[row][col0]) {
          dists[row][col0] = dist;
          que.push({dist, row, col0, 'V'});
        }
      }

      // Up
      if (dir0 != 'V') {
        auto row = row0;
        while (row >= 0 && maze[row][col0] == 0) --row;  // find wall
        ++row;                                           // step back
        auto dist = dist0 + (row0 - row);
        if (dist < dists[row][col0]) {
          dists[row][col0] = dist;
          que.push({dist, row, col0, 'V'});
        }
      }

      // Right
      if (dir0 != 'H') {
        auto col = col0;
        while (col < n && maze[row0][col] == 0) ++col;  // find wall
        --col;                                          // step back
        auto dist = dist0 + (col - col0);
        if (dist < dists[row0][col]) {
          dists[row0][col] = dist;
          que.push({dist, row0, col, 'H'});
        }
      }

      // Left
      if (dir0 != 'H') {
        auto col = col0;
        while (col >= 0 && maze[row0][col] == 0) --col;  // find wall
        ++col;                                           // step back
        auto dist = dist0 + (col0 - col);
        if (dist < dists[row0][col]) {
          dists[row0][col] = dist;
          que.push({dist, row0, col, 'H'});
        }
      }
    }

    return -1;
  }
};
