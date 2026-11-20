// Source: https://leetcode.com/problems/separate-squares-ii
// Title: Separate Squares II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D integer array `squares`. Each `squares[i] = [x_i, y_i, l_i]` represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
//
// Find the **minimum** y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.
//
// Answers within `10^-5` of the actual answer will be accepted.
//
// **Note**: Squares **may** overlap. Overlapping areas should be counted **only once** in this version.
//
// **Example 1:**
//
// ```
// Input: squares = [[0,0,1],[2,2,1]]
// Output: 1.00000
// Explanation:
// https://assets.leetcode.com/uploads/2025/01/15/4065example1drawio.png
// Any horizontal line between `y = 1` and `y = 2` results in an equal split, with 1 square unit above and 1 square unit below. The minimum y-value is 1.
// ```
//
// **Example 2:**
//
// ```
// Input: squares = [[0,0,2],[1,1,1]]
// Output: 1.00000
// Explanation:
// https://assets.leetcode.com/uploads/2025/01/15/4065example2drawio.png
// Since the blue square overlaps with the red square, it will not be counted again. Thus, the line `y = 1` splits the squares into two equal parts.
// ```
//
// **Constraints:**
//
// - `1 <= squares.length <= 5 * 10^4`
// - `squares[i] = [x_i, y_i, l_i]`
// - `squares[i].length == 3`
// - `0 <= x_i, y_i <= 10^9`
// - `1 <= l_i <= 10^9`
// - The total area of all the squares will not exceed `10^15`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <set>
#include <vector>

using namespace std;

// Line Sweep + Prefix Sum + Binary Search (TLE)
//
// List all starting and ending x coordinates of all rectangles.
// Sort and loop through these coordinates.
//
// For each step, add or remove the rectangle into current pool (sorted by y2),
// and loop through the rectangles in the pool to compute the area.
// We use an array the store the prefix sum of the areas.
//
// Use binary search to search in the prefix sum array.
class Solution {
  enum State { start, end };

 public:
  double separateSquares(vector<vector<int>> &squares) {
    int n = squares.size();

    // Sort by x1
    sort(squares.begin(), squares.end(), [](auto &a, auto &b) -> bool {  //
      return a[0] < b[0];
    });

    // Prepare
    auto ys = vector<tuple<int64_t, State, int>>();  // y, state, id
    ys.reserve(2 * n);

    for (auto i = 0; i < n; ++i) {
      int64_t y1 = squares[i][1], y2 = y1 + squares[i][2];
      ys.push_back({y1, start, i});
      ys.push_back({y2, end, i});
    }

    sort(ys.begin(), ys.end());

    // Prefix sum, inclusive (since the first must be zero)
    auto preSums = vector<int64_t>();
    preSums.reserve(2 * n);

    auto activeIds = set<int64_t>();
    int64_t totalSum = 0;  // note that we store the double of the real value
    int64_t prevY = 0;
    for (auto [newY, newState, newId] : ys) {
      int64_t height = 0;
      int64_t currX1 = 0, currX2 = 0;
      for (auto id : activeIds) {
        int64_t x1 = squares[id][0], x2 = x1 + squares[id][2];
        // We know that x1 >= currX1 since we sort the rectangles by x1
        if (x1 >= currX2) {  // no overlap
          height += currX2 - currX1;
          currX1 = x1, currX2 = x2;
        } else {
          currX2 = max(x2, currX2);
        }
      }
      height += currX2 - currX1;

      totalSum += (newY - prevY) * height * 2;  // double it to avoid integer division issue
      preSums.push_back(totalSum);
      prevY = newY;

      if (newState == start) {
        activeIds.insert(newId);
      } else {
        activeIds.erase(newId);
      }
    }

    // Binary search, find first positive value
    int64_t halfSum = totalSum / 2;
    auto idx = lower_bound(preSums.cbegin(), preSums.cend(), halfSum) - preSums.cbegin();

    if (preSums[idx] == halfSum) ys[idx];  // exact match

    double left = halfSum - preSums[idx - 1], right = preSums[idx] - halfSum;  // left < half < right
    double leftX = get<0>(ys[idx - 1]), rightX = get<0>(ys[idx]);
    return (leftX * right + rightX * left) / (left + right);
  }
};

// Line Sweep + Segment Tree + Prefix Sum + Binary Search
//
// Using the x coordinates of the rectangles, we split the x axis into several ranges.
// Each range is a node in the segment tree.
class Solution2 {
  struct SegmentTree {
    // Segment cuts
    int m;
    vector<int64_t> &xs;  // x coordinates

    // Tree, parent i -> child 2i & 2i+1
    vector<int> counts;       // the number of rectangle covering this node
    vector<int64_t> lengths;  // the total covered length of this node

    SegmentTree(vector<int64_t> &xs) : xs(xs) {
      m = xs.size() - 1;
      counts.resize(4 * m);
      lengths.resize(4 * m);
    }

    void pushUp(int node, int lo, int hi) {
      if (counts[node] > 0) {
        // full covered
        lengths[node] = xs[hi] - xs[lo];
      } else {
        // not full covered
        if (hi - lo == 1) {  // leaf
          lengths[node] = 0;
        } else {
          lengths[node] = lengths[2 * node] + lengths[2 * node + 1];
        }
      }
    }

    // Add val into range [rLo, rHi)
    void update(int rLo, int rHi, int val) {  //
      return update(rLo, rHi, val, 1, 0, m);
    }

    void update(int rLo, int rHi, int val, int node, int lo, int hi) {
      // out of range
      if (rHi <= lo || hi <= rLo) return;

      if (rLo <= lo && hi <= rHi) {
        // full covered
        counts[node] += val;
      } else {
        // partial covered
        auto mid = lo + (hi - lo) / 2;
        update(rLo, rHi, val, 2 * node, lo, mid);
        update(rLo, rHi, val, 2 * node + 1, mid, hi);
      }

      pushUp(node, lo, hi);
    }

    // Get root length
    auto rootLength() {  //
      return lengths[1];
    }
  };

 public:
  double separateSquares(vector<vector<int>> &squares) {
    int n = squares.size();

    // Prepare
    auto ys = vector<tuple<int64_t, int, int>>();  // y, action, id
    auto xs = vector<int64_t>();
    ys.reserve(2 * n);
    xs.reserve(2 * n);
    for (auto i = 0; i < n; ++i) {
      auto x1 = squares[i][0], y1 = squares[i][1], l = squares[i][2];
      auto x2 = x1 + l, y2 = y1 + l;
      ys.push_back({y1, +1, i});  // enter square
      ys.push_back({y2, -1, i});  // leave square
      xs.push_back(x1);
      xs.push_back(x2);
    }
    sort(ys.begin(), ys.end());
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());  // remove duplication

    // Prefix sum, inclusive (since the first must be zero)
    auto preSums = vector<int64_t>();
    preSums.reserve(2 * n);

    // Loop
    auto tree = SegmentTree(xs);
    int64_t totalSum = 0;  // note that we store the double of the real value
    int64_t prevY = 0;
    for (auto [currY, action, id] : ys) {
      // Compute area
      int64_t height = currY - prevY;
      if (height > 0) {
        int64_t width = tree.rootLength();
        totalSum += height * width * 2;
      }
      preSums.push_back(totalSum);

      // Update segment tree
      int64_t x1 = squares[id][0], x2 = x1 + squares[id][2];
      auto idx1 = lower_bound(xs.cbegin(), xs.cend(), x1) - xs.cbegin();
      auto idx2 = lower_bound(xs.cbegin(), xs.cend(), x2) - xs.cbegin();
      if (idx2 > idx1) {
        tree.update(idx1, idx2, action);
      }

      // Update
      prevY = currY;
    }

    // Binary search, find first positive value
    int64_t halfSum = totalSum / 2;
    auto idx = lower_bound(preSums.cbegin(), preSums.cend(), halfSum) - preSums.cbegin();

    if (preSums[idx] == halfSum) ys[idx];  // exact match

    double left = halfSum - preSums[idx - 1], right = preSums[idx] - halfSum;  // left < half < right
    double leftX = get<0>(ys[idx - 1]), rightX = get<0>(ys[idx]);
    return (leftX * right + rightX * left) / (left + right);
  }
};
