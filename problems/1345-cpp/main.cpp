// Source: https://leetcode.com/problems/jump-game-iv
// Title: Jump Game IV
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `arr`, you are initially positioned at the first index of the array.
//
// In one step you can jump from index `i` to index:
//
// - `i + 1` where:`i + 1 < arr.length`.
// - `i - 1` where:`i - 1 >= 0`.
// - `j` where: `arr[i] == arr[j]` and `i != j`.
//
// Return the minimum number of steps to reach the **last index** of the array.
//
// Notice that you can not jump outside of the array at any time.
//
// **Example 1:**
//
// ```
// Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
// Output: 3
// Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [7]
// Output: 0
// Explanation: Start index is the last index. You do not need to jump.
// ```
//
// **Example 3:**
//
// ```
// Input: arr = [7,6,9,6,9,6,9,7]
// Output: 1
// Explanation: You can jump directly from index 0 to index 7 which is last index of the array.
// ```
//
// **Constraints:**
//
// - `1 <= arr.length <= 5 * 10^4`
// - `-10^8 <= arr[i] <= 10^8`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

// BFS
//
// First group all numbers by its value.
// After each step, remove the group of the number since we will never use it again.
class Solution {
  using Bool = unsigned char;

 public:
  int minJumps(const vector<int>& arr) {
    const int n = arr.size();

    // Trivial
    if (n == 1) return 0;

    // Group
    auto groups = unordered_map<int, vector<int>>();  // number -> idxs
    for (int i = 0; i < n; ++i) {
      groups[arr[i]].push_back(i);
    }

    // BFS
    auto visited = vector<Bool>(n);
    auto prev = vector<int>();
    auto curr = vector<int>();
    visited[0] = true;
    curr.push_back(0);

    for (int step = 1; !curr.empty(); ++step) {
      swap(curr, prev);
      curr.clear();

      for (int i : prev) {
        if (i + 1 < n) {
          int j = i + 1;
          if (!visited[j]) {
            if (j == n - 1) return step;
            visited[j] = true;
            curr.push_back(j);
          }
        }

        if (i - 1 >= 0) {
          int j = i - 1;
          if (!visited[j]) {
            if (j == n - 1) return step;
            visited[j] = true;
            curr.push_back(j);
          }
        }

        for (int j : groups[arr[i]]) {
          if (!visited[j]) {
            if (j == n - 1) return step;
            visited[j] = true;
            curr.push_back(j);
          }
        }
        groups.erase(arr[i]);
      }
    }

    return -1;  // unreachable
  }
};
