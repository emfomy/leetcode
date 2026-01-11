// Source: https://leetcode.com/problems/the-maze
// Title: The Maze
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a ball in a `maze` with empty spaces (represented as `0`) and walls (represented as `1`). The ball can go through the empty spaces by rolling **up, down, left or right**, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
//
// Given the `m x n` `maze`, the ball's `start` position and the `destination`, where `start = [start_row, start_col]` and `destination = [destination_row, destination_col]`, return `true` if the ball can stop at the destination, otherwise return `false`.
//
// You may assume that **the borders of the maze are all walls** (see examples).
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/31/maze1-1-grid.jpg
//
// ```
// Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [4,4]
// Output: true
// Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/31/maze1-2-grid.jpg
//
// ```
// Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [3,2]
// Output: false
// Explanation: There is no way for the ball to stop at the destination. Notice that you can pass through the destination but you cannot stop there.
// ```
//
// **Example 3:**
//
// ```
// Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], start = [4,3], destination = [0,1]
// Output: false
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

#include <queue>
#include <vector>

using namespace std;

// BFS
class Solution {
  using State = tuple<int, int, char>;  // row, col, direction (from) U/D/L/R

 public:
  bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    auto m = maze.size(), n = maze[0].size();
    auto visited = vector(m, vector(n, false));

    auto srcRow = start[0], srcCol = start[1];
    auto dstRow = destination[0], dstCol = destination[1];

    auto que = queue<State>();
    visited[srcRow][srcCol] = true;
    que.push({srcRow, srcCol, ' '});

    while (!que.empty()) {
      if (visited[dstRow][dstCol]) return true;
      auto [row0, col0, dir0] = que.front();
      que.pop();

      // Down
      if (dir0 != 'D') {
        auto row = row0;
        while (row < m && maze[row][col0] == 0) ++row;  // find wall
        --row;                                          // step back
        if (!visited[row][col0]) {
          visited[row][col0] = true;
          que.push({row, col0, 'D'});
        }
      }

      // Up
      if (dir0 != 'U') {
        auto row = row0;
        while (row >= 0 && maze[row][col0] == 0) --row;  // find wall
        ++row;                                           // step back
        if (!visited[row][col0]) {
          visited[row][col0] = true;
          que.push({row, col0, 'U'});
        }
      }

      // Right
      if (dir0 != 'R') {
        auto col = col0;
        while (col < n && maze[row0][col] == 0) ++col;  // find wall
        --col;                                          // step back
        if (!visited[row0][col]) {
          visited[row0][col] = true;
          que.push({row0, col, 'R'});
        }
      }

      // Left
      if (dir0 != 'L') {
        auto col = col0;
        while (col >= 0 && maze[row0][col] == 0) --col;  // find wall
        ++col;                                           // step back
        if (!visited[row0][col]) {
          visited[row0][col] = true;
          que.push({row0, col, 'L'});
        }
      }
    }

    return false;
  }
};
