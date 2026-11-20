// Source: https://leetcode.com/problems/rectangle-area-ii
// Title: Rectangle Area II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D array of axis-aligned `rectangles`. Each `rectangle[i] = [x_i1, y_i1, x_i2, y_i2]` denotes the `i^th` rectangle where `(x_i1, y_i1)` are the coordinates of the **bottom-left corner**, and `(x_i2, y_i2)` are the coordinates of the **top-right corner**.
//
// Calculate the **total area** covered by all `rectangles` in the plane. Any area covered by two or more rectangles should only be counted **once**.
//
// Return the **total area**. Since the answer may be too large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
// https://s3-lc-upload.s3.amazonaws.com/uploads/2018/06/06/rectangle_area_ii_pic.png
//
// ```
// Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
// Output: 6
// Explanation: A total area of 6 is covered by all three rectangles, as illustrated in the picture.
// From (1,1) to (2,2), the green and red rectangles overlap.
// From (1,0) to (2,3), all three rectangles overlap.
// ```
//
// **Example 2:**
//
// ```
// Input: rectangles = [[0,0,1000000000,1000000000]]
// Output: 49
// Explanation: The answer is 10^18 modulo (10^9 + 7), which is 49.
// ```
//
// **Constraints:**
//
// - `1 <= rectangles.length <= 200`
// - `rectanges[i].length == 4`
// - `0 <= x_i1, y_i1, x_i2, y_i2 <= 10^9`
// - `x_i1 <= x_i2`
// - `y_i1 <= y_i2`
// - All rectangles have non zero area.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <set>
#include <vector>

using namespace std;

// Line Sweep
// O(n^2)
// * nlogn for sort
// * n^2 for double loop
// * nlogn for set update
//
// List all starting and ending x coordinates of all rectangles.
// Sort and loop through these coordinates.
//
// For each step, add or remove the rectangle into current pool (sorted by y1),
// and loop through the rectangles in the pool to compute the area.
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

  enum State { start, end };

 public:
  int rectangleArea(vector<vector<int>> &rectangles) {
    int n = rectangles.size();

    // Sort by y1
    sort(rectangles.begin(), rectangles.end(), [](auto &a, auto &b) -> bool {  //
      return a[1] < b[1];
    });

    // Prepare
    auto xs = vector<tuple<int64_t, State, int>>();  // x, state, id
    xs.reserve(2 * n);

    for (auto i = 0; i < n; ++i) {
      auto x1 = rectangles[i][0], x2 = rectangles[i][2];
      xs.push_back({x1, start, i});
      xs.push_back({x2, end, i});
    }

    sort(xs.begin(), xs.end());

    // Loop
    auto activeIds = set<int>();
    int64_t ans = 0;
    int64_t prevX = 0;
    for (auto [newX, newState, newId] : xs) {
      int64_t height = 0;
      int64_t currY1 = 0, currY2 = 0;
      for (auto id : activeIds) {
        int64_t y1 = rectangles[id][1], y2 = rectangles[id][3];
        // We know that y1 >= currY1 since we sort the rectangles by y1
        if (y1 >= currY2) {  // no overlap
          height += currY2 - currY1;
          height %= modulo;
          currY1 = y1, currY2 = y2;
        } else {
          currY2 = max(y2, currY2);
        }
      }
      height += currY2 - currY1;
      height %= modulo;

      ans += (newX - prevX) * height;
      ans %= modulo;
      prevX = newX;

      if (newState == start) {
        activeIds.insert(newId);
      } else {
        activeIds.erase(newId);
      }
    }

    return ans;
  }
};

// Line Sweep + Segment Tree
// O(nlogn)
// * nlogn for sort
// * nlogn for loop binary search
// * nlogn for loop tree update
//
// Using the y coordinates of the rectangles, we split the y axis into several ranges.
// Each range is a node in the segment tree.
class Solution2 {
  constexpr static int64_t modulo = 1e9 + 7;

  struct SegmentTree {
    // Segment cuts
    int m;
    vector<int64_t> &ys;  // y coordinates

    // Tree, parent i -> child 2i & 2i+1
    vector<int> counts;       // the number of rectangle covering this node
    vector<int64_t> lengths;  // the total covered length of this node

    SegmentTree(vector<int64_t> &xs) : ys(xs) {
      m = xs.size() - 1;
      counts.resize(4 * m);
      lengths.resize(4 * m);
    }

    void pushUp(int node, int lo, int hi) {
      if (counts[node] > 0) {
        // full covered
        lengths[node] = ys[hi] - ys[lo];
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
  int rectangleArea(vector<vector<int>> &rectangles) {
    int n = rectangles.size();

    // Prepare
    auto xs = vector<tuple<int64_t, int, int>>();  // x, action, id
    auto ys = vector<int64_t>();
    xs.reserve(2 * n);
    ys.reserve(2 * n);
    for (auto i = 0; i < n; ++i) {
      auto x1 = rectangles[i][0], x2 = rectangles[i][2];
      auto y1 = rectangles[i][1], y2 = rectangles[i][3];
      xs.push_back({x1, +1, i});  // enter rectangle
      xs.push_back({x2, -1, i});  // leave rectangle
      ys.push_back(y1);
      ys.push_back(y2);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());  // remove duplication

    // Loop
    auto tree = SegmentTree(ys);
    int64_t ans = 0;
    int64_t prevX = 0;
    for (auto [currX, action, id] : xs) {
      // Compute area
      int64_t width = currX - prevX;
      if (width > 0) {
        int64_t height = tree.rootLength();
        ans += width * height;
        ans %= modulo;
      }

      // Update segment tree
      int64_t y1 = rectangles[id][1], y2 = rectangles[id][3];
      auto idx1 = lower_bound(ys.cbegin(), ys.cend(), y1) - ys.cbegin();
      auto idx2 = lower_bound(ys.cbegin(), ys.cend(), y2) - ys.cbegin();
      if (idx1 < idx2) {
        tree.update(idx1, idx2, action);
      }

      // Update
      prevX = currX;
    }

    return ans;
  }
};
