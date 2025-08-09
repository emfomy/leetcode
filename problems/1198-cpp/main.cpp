// Source: https://leetcode.com/problems/find-smallest-common-element-in-all-rows
// Title: Find Smallest Common Element in All Rows
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` matrix `mat` where every row is sorted in **strictly** **increasing** order, return the **smallest common element** in all rows.
//
// If there is no common element, return `-1`.
//
// **Example 1:**
//
// ```
// Input: mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]
// Output: 5
// ```
//
// **Example 2:**
//
// ```
// Input: mat = [[1,2,3],[2,3,4],[2,3,5]]
// Output: 2
// ```
//
// **Constraints:**
//
// - `m == mat.length`
// - `n == mat[i].length`
// - `1 <= m, n <= 500`
// - `1 <= mat[i][j] <= 10^4`
// - `mat[i]` is sorted in strictly increasing order.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <vector>

#include "../../utils/print.hpp"

using namespace std;

// Use Sort, O(mn log(mn))
//
// Sort all indices
class Solution {
 public:
  int smallestCommonElement(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();

    auto idxs = vector<pair<int, int>>();  // indexs of each row
    for (auto i = 0; i < m; i++) {
      for (auto j = 0; j < n; j++) {
        idxs.push_back({i, j});
      }
    }

    // Comp, a, b are valid indices
    auto comp = [&](pair<int, int> a, pair<int, int> b) -> bool {  //
      return mat[a.first][a.second] < mat[b.first][b.second];
    };
    sort(idxs.begin(), idxs.end(), comp);

    auto ans = 0;
    auto count = 0;
    for (auto [i, j] : idxs) {
      auto val = mat[i][j];
      if (val == ans) {
        count++;
      } else {
        ans = val;
        count = 1;
      }
      if (count == m) return ans;
    }

    return -1;
  }
};

// Use Priority Queue, O(mn log(m))
class Solution2 {
 public:
  int smallestCommonElement(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();

    auto idxs = vector<pair<int, int>>();  // indexs of each row
    for (auto i = 0; i < m; i++) {
      idxs.push_back({i, 0});
    }

    // Comp, a, b are valid indices
    auto comp = [&](pair<int, int> a, pair<int, int> b) -> bool {  //
      return mat[a.first][a.second] > mat[b.first][b.second];
    };

    auto heap = priority_queue(comp, std::move(idxs));

    auto ans = 0;
    auto count = 0;
    while (heap.size() > 0) {
      for (auto p : idxs) {
        print_vector(mat[p.first], p.second);
      }

      auto item = heap.top();
      heap.pop();

      // Count
      auto val = mat[item.first][item.second];
      if (val == ans) {
        count++;
      } else {
        ans = val;
        count = 1;
      }
      if (count == m) return ans;

      // Push back
      item.second++;
      if (item.second < n) {
        heap.push(item);
      }
    }

    return -1;
  }
};

// Use counter, O(mn)
class Solution3 {
 public:
  int smallestCommonElement(vector<vector<int>>& mat) {
    int m = mat.size();

    // Count
    auto counter = unordered_map<int, int>();
    for (auto& vec : mat) {
      for (auto val : vec) {
        counter[val]++;
      }
    }
    print_unordered_map(counter);

    auto ans = -1;
    for (auto [val, count] : counter) {
      if (count == m) ans = val;
    }

    return ans;
  }
};

// Use binary search, O(m log n)
//
// Find number of first row in other rows using binary search.
class Solution4 {
 public:
  int smallestCommonElement(vector<vector<int>>& mat) {
    int m = mat.size();

    for (auto val : mat[0]) {
      auto ok = true;
      for (auto j = 1; j < m; j++) {
        if (!binary_search(mat[j].cbegin(), mat[j].cend(), val)) {
          ok = false;
          break;
        }
      }
      if (ok) return val;
    }

    return -1;
  }
};

// Use binary search, O(m log n)
//
// Use functional programming
class Solution5 {
 public:
  int smallestCommonElement(vector<vector<int>>& mat) {
    int m = mat.size();

    auto it = find_if(mat[0].cbegin(), mat[0].cend(), [&](const int val) -> bool {
      auto find_val = [=](const vector<int>& vec) -> bool {  //
        return binary_search(vec.cbegin(), vec.cend(), val);
      };
      return all_of(mat.cbegin() + 1, mat.cend(), find_val);
    });
    return it != mat[0].cend() ? *it : -1;
  }
};
