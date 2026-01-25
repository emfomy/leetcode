// Source: https://leetcode.com/problems/the-maze-iii
// Title: The Maze III
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a ball in a `maze` with empty spaces (represented as `0`) and walls (represented as `1`). The ball can go through the empty spaces by rolling **up, down, left or right**, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction (must be different from last chosen direction). There is also a hole in this maze. The ball will drop into the hole if it rolls onto the hole.
//
// Given the `m x n` `maze`, the ball's position `ball` and the hole's position `hole`, where `ball = [ball_row, ball_col]` and `hole = [hole_row, hole_col]`, return a string `instructions` of all the instructions that the ball should follow to drop in the hole with the **shortest distance** possible. If there are multiple valid instructions, return the **lexicographically minimum** one. If the ball can't drop in the hole, return `"impossible"`.
//
// If there is a way for the ball to drop in the hole, the answer `instructions` should contain the characters `'u'` (i.e., up), `'d'` (i.e., down), `'l'` (i.e., left), and `'r'` (i.e., right).
//
// The **distance** is the number of **empty spaces** traveled by the ball from the start position (excluded) to the destination (included).
//
// You may assume that **the borders of the maze are all walls** (see examples).
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/31/maze3-1-grid.jpg
//
// ```
// Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], ball = [4,3], hole = [0,1]
// Output: "lul"
// Explanation: There are two shortest ways for the ball to drop into the hole.
// The first way is left -> up -> left, represented by "lul".
// The second way is up -> left, represented by 'ul'.
// Both ways have shortest distance 6, but the first way is lexicographically smaller because 'l' < 'u'. So the output is "lul".
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/31/maze3-2-grid.jpg
//
// ```
// Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], ball = [4,3], hole = [3,0]
// Output: "impossible"
// Explanation: The ball cannot reach the hole.
// ```
//
// **Example 3:**
//
// ```
// Input: maze = [[0,0,0,0,0,0,0],[0,0,1,0,0,1,0],[0,0,0,0,1,0,0],[0,0,0,0,0,0,1]], ball = [0,4], hole = [3,5]
// Output: "dldr"
// ```
//
// **Constraints:**
//
// - `m == maze.length`
// - `n == maze[i].length`
// - `1 <= m, n <= 100`
// - `maze[i][j]` is `0` or `1`.
// - `ball.length == 2`
// - `hole.length == 2`
// - `0 <= ball_row, hole_row <= m`
// - `0 <= ball_col, hole_col <= n`
// - Both the ball and the hole exist in an empty space, and they will not be in the same position initially.
// - The maze contains **at least 2 empty spaces**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <cstdio>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

// BFS
//
// If the previous move the vertical, the next move must be horizontal (and vise versa).
class Solution {
  using State = tuple<int, string, int, int, char>;  // distance, way, row, col, V/H (vertical & horizontal)

 public:
  string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
    auto m = maze.size(), n = maze[0].size();
    auto dists = vector(m, vector(n, INT_MAX));

    auto srcRow = ball[0], srcCol = ball[1];
    auto dstRow = hole[0], dstCol = hole[1];

    auto que = priority_queue(greater(), std::move(vector<State>()));  // min-heap
    que.push({0, "", srcRow, srcCol, ' '});

    while (!que.empty()) {
      auto [dist0, way0, row0, col0, dir0] = que.top();
      que.pop();
      if (row0 == dstRow && col0 == dstCol) return way0;
      if (dist0 > dists[row0][col0]) continue;

      // Down
      if (dir0 != 'V') {
        auto row = row0, col = col0;
        while (row < m) {
          if (row == m - 1) break;                    // found boarder
          if (row == dstRow && col == dstCol) break;  // found ball
          if (maze[row + 1][col] == 1) break;         // found wall
          ++row;
        }
        if (row != row0) {
          auto dist = dist0 + (row - row0);
          if (dist <= dists[row][col]) {
            dists[row][col] = dist;
            que.push({dist, way0 + 'd', row, col, 'V'});
          }
        }
      }

      // Up
      if (dir0 != 'V') {
        auto row = row0, col = col0;
        while (row >= 0) {
          if (row == 0) break;                        // found boarder
          if (row == dstRow && col == dstCol) break;  // found ball
          if (maze[row - 1][col] == 1) break;         // found wall
          --row;
        }
        if (row != row0) {
          auto dist = dist0 + (row0 - row);
          if (dist <= dists[row][col]) {
            dists[row][col] = dist;
            que.push({dist, way0 + 'u', row, col, 'V'});
          }
        }
      }

      // Right
      if (dir0 != 'H') {
        auto row = row0, col = col0;
        while (col < n) {
          if (col == n - 1) break;                    // found boarder
          if (row == dstRow && col == dstCol) break;  // found ball
          if (maze[row][col + 1] == 1) break;         // found wall
          ++col;
        }
        if (col != col0) {
          auto dist = dist0 + (col - col0);
          if (dist <= dists[row][col]) {
            dists[row][col] = dist;
            que.push({dist, way0 + 'r', row0, col, 'H'});
          }
        }
      }

      // Left
      if (dir0 != 'H') {
        auto row = row0, col = col0;
        while (col >= 0) {
          if (col == 0) break;                        // found boarder
          if (row == dstRow && col == dstCol) break;  // found ball
          if (maze[row][col - 1] == 1) break;         // found wall
          --col;
        }
        if (col != col0) {
          auto dist = dist0 + (col0 - col);
          if (dist <= dists[row][col]) {
            dists[row][col] = dist;
            que.push({dist, way0 + 'l', row, col, 'H'});
          }
        }
      }
    }

    return "impossible";
  }
};
