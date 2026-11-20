// Source: https://leetcode.com/problems/fruits-into-baskets-iii
// Title: Fruits Into Baskets III
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two arrays of integers, `fruits` and `baskets`, each of length `n`, where `fruits[i]` represents the **quantity** of the `i^th` type of fruit, and `baskets[j]` represents the **capacity** of the `j^th` basket.
//
// From left to right, place the fruits according to these rules:
//
// - Each fruit type must be placed in the **leftmost available basket** with a capacity **greater than or equal** to the quantity of that fruit type.
// - Each basket can hold **only one** type of fruit.
// - If a fruit type **cannot be placed** in any basket, it remains **unplaced**.
//
// Return the number of fruit types that remain unplaced after all possible allocations are made.
//
// **Example 1:**
//
// ```
// Input: fruits = [4,2,5], baskets = [3,5,4]
// Output: 1
// Explanation:
// - `fruits[0] = 4` is placed in `baskets[1] = 5`.
// - `fruits[1] = 2` is placed in `baskets[0] = 3`.
// - `fruits[2] = 5` cannot be placed in `baskets[2] = 4`.
// Since one fruit type remains unplaced, we return 1.
// ```
//
// **Example 2:**
//
// ```
// Input: fruits = [3,6,1], baskets = [6,4,7]
// Output: 0
// Explanation:
// - `fruits[0] = 3` is placed in `baskets[0] = 6`.
// - `fruits[1] = 6` cannot be placed in `baskets[1] = 4` (insufficient capacity) but can be placed in the next available basket, `baskets[2] = 7`.
// - `fruits[2] = 1` is placed in `baskets[1] = 4`.
// Since all fruits are successfully placed, we return 0.
// ```
//
// **Constraints:**
//
// - `n == fruits.length == baskets.length`
// - `1 <= n <= 10^5`
// - `1 <= fruits[i], baskets[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <cstddef>
#include <vector>

using namespace std;

// Segment Tree
//
// Use segment tree to track the maximum value of baskets.
class Solution {
  struct SegmentTree {
    int m;
    vector<int> tree;  // parent i -> child 2i & 2i+1

    // Requires: all nums >= 0
    // Padding [n, m) to zero and will never be matched.
    SegmentTree(const vector<int>& nums) {
      int n = nums.size();
      m = 1u << bit_width(static_cast<unsigned>(n));  // pad to power of 2
      tree.resize(2 * m);

      // Build O(N)
      for (int i = 0; i < n; ++i) tree[i + m] = nums[i];
      for (int i = m - 1; i >= 1; --i) tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }

    // Update O(logN); nums[i] = val
    void update(int i, int val) {
      // Update leaf
      i += m;
      tree[i] = val;

      // Update parents
      for (i /= 2; i >= 1; i /= 2) {
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
      }
    }

    // Top Down Query O(logN); find leftmost i with nums[i] >= limit
    int query(int limit) {
      // Root
      int i = 1;
      if (tree[i] < limit) return m;  // no answer

      // Parents
      for (i *= 2; i < m; i *= 2) {
        i += (tree[i] < limit);  // go to sibling
      }

      // Leaf
      i += (tree[i] < limit);  // go to sibling

      return i - m;
    }
  };

 public:
  int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
    const int n = baskets.size();

    int remains = 0;
    auto tree = SegmentTree(baskets);
    for (const int fruit : fruits) {
      int i = tree.query(fruit);
      if (i < n) {
        tree.update(i, 0);
      } else {
        ++remains;
      }
    }

    return remains;
  }
};
