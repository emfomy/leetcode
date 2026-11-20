// Source: https://leetcode.com/problems/number-of-adjacent-elements-with-the-same-color
// Title: Number of Adjacent Elements With the Same Color
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n` representing an array `colors` of length `n` where all elements are set to 0's meaning **uncolored**. You are also given a 2D integer array `queries` where `queries[i] = [index_i, color_i]`. For the `i^th` **query**:
//
// - Set `colors[index_i]` to `color_i`.
// - Count the number of adjacent pairs in `colors` which have the same color (regardless of `color_i`).
//
// Return an array `answer` of the same length as `queries` where `answer[i]` is the answer to the `i^th` query.
//
// **Example 1:**
//
// ```
// Input: n = 4, queries = [[0,2],[1,2],[3,1],[1,1],[2,1]]
// Output: [0,1,1,0,2]
// Explanation:
// - Initially array colors = [0,0,0,0], where 0 denotes uncolored elements of the array.
// - After the 1^st query colors = [2,0,0,0]. The count of adjacent pairs with the same color is 0.
// - After the 2^nd query colors = [2,2,0,0]. The count of adjacent pairs with the same color is 1.
// - After the 3^rd query colors = [2,2,0,1]. The count of adjacent pairs with the same color is 1.
// - After the 4^th query colors = [2,1,0,1]. The count of adjacent pairs with the same color is 0.
// - After the 5^th query colors = [2,1,1,1]. The count of adjacent pairs with the same color is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1, queries = [[0,100000]]
// Output: [0]
// Explanation:
// After the 1^st query colors = [100000]. The count of adjacent pairs with the same color is 0.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^5`
// - `1 <= queries.length <= 10^5`
// - `queries[i].length== 2`
// - `0 <= index_i<= n - 1`
// - `1 <= color_i<= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Simulation
class Solution {
 public:
  vector<int> colorTheArray(const int n, const vector<vector<int>>& queries) {
    auto colors = vector<int>(n + 2);
    int count = 0;

    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (const auto& query : queries) {
      const int idx = query[0] + 1, color = query[1];

      // Reset to uncolored
      count -= (colors[idx] != 0) && (colors[idx] == colors[idx - 1]);
      count -= (colors[idx] != 0) && (colors[idx] == colors[idx + 1]);

      // Set color
      colors[idx] = color;
      count += (colors[idx] == colors[idx - 1]);
      count += (colors[idx] == colors[idx + 1]);

      ans.push_back(count);
    }

    return ans;
  }
};
