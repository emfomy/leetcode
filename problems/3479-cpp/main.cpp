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

#include <vector>

using namespace std;

// Use Segment Tree
//
// Use the segment tree to store the maximum bucket of any range.
class Solution {
  class SegmentTree {
    int n;
    vector<int> tree;  // parent i -> child 2i & 2i+1

   public:
    SegmentTree(vector<int>& nums) {
      n = nums.size();
      tree.resize(4 * n);
      build(nums, 1, 0, n);
    }

    void build(vector<int>& nums, int node, int lo, int hi) {
      // leaf node
      if (lo == hi - 1) {
        tree[node] = nums[lo];
        return;
      }

      auto mid = lo + (hi - lo) / 2;
      build(nums, 2 * node, lo, mid);
      build(nums, 2 * node + 1, mid, hi);
      tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    // Update: O(logN)
    void update(int idx, int val) { update(idx, val, 1, 0, n); }
    void update(int idx, int val, int node, int lo, int hi) {
      // Leaf node
      if (lo == hi - 1) {
        tree[node] = val;
        return;
      }

      auto mid = lo + (hi - lo) / 2;
      if (idx < mid) {
        update(idx, val, 2 * node, lo, mid);
      } else {
        update(idx, val, 2 * node + 1, mid, hi);
      }
      tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    // QueryFirst: O(logN); Find first such that val >= k
    int queryFirst(int k) { return queryFirst(k, 1, 0, n); }
    int queryFirst(int k, int node, int lo, int hi) {
      // Not found
      if (tree[node] < k) return -1;

      // Leaf
      if (lo == hi - 1) return lo;

      // Recursion
      auto mid = lo + (hi - lo) / 2;
      auto res = queryFirst(k, 2 * node, lo, mid);
      if (res != -1) return res;
      return queryFirst(k, 2 * node + 1, mid, hi);
    }
  };

 public:
  int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
    auto tree = SegmentTree(baskets);

    // Loop
    auto ans = 0;
    for (auto fruit : fruits) {
      auto idx = tree.queryFirst(fruit);
      if (idx >= 0) {
        tree.update(idx, 0);
      } else {
        ++ans;
      }
    }

    return ans;
  }
};
