// Source: https://leetcode.com/problems/range-addition
// Title: Range Addition
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `length` and an array `updates` where `updates[i] = [startIdx_i, endIdx_i, inc_i]`.
//
// You have an array `arr` of length `length` with all zeros, and you have some operation to apply on `arr`. In the `i^th` operation, you should increment all the elements `arr[startIdx_i], arr[startIdx_i + 1], ..., arr[endIdx_i]` by `inc_i`.
//
// Return `arr` after applying all the `updates`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/27/rangeadd-grid.jpg
//
// ```
// Input: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
// Output: [-2,0,3,5,3]
// ```
//
// **Example 2:**
//
// ```
// Input: length = 10, updates = [[2,4,6],[5,6,8],[1,9,-4]]
// Output: [0,-4,2,2,2,4,4,-4,-4,-4]
// ```
//
// **Constraints:**
//
// - `1 <= length <= 10^5`
// - `0 <= updates.length <= 10^4`
// - `0 <= startIdx_i <= endIdx_i < length`
// - `-1000 <= inc_i <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Use difference array
//
// Let V be the array.
// D[i] = V[i]-V[i-1] is the difference array. (V[-1] and V[n] are always 0).
class Solution {
 public:
  vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    auto n = length;
    auto diff = vector<int>(n + 1);

    for (auto& update : updates) {
      auto start = update[0], end = update[1] + 1, inc = update[2];
      diff[start] += inc;
      diff[end] -= inc;
    }

    auto ans = vector<int>(n);
    auto val = 0;
    for (auto i = 0; i < n; ++i) {
      val += diff[i];
      ans[i] = val;
    }

    return ans;
  }
};
