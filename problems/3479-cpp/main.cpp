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

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

// Use Square Root Decomposition
//
// Split baskets into sqrt(n) blocks, and track the maximum size of each block.
class Solution {
 public:
  int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
    int n = baskets.size();
    int m = int(sqrt(n));     // block size
    int M = (n - 1) / m + 1;  // number of blocks

    vector<int> blocks(M);  // max of each block
    for (auto i = 0; i < n; i++) {
      blocks[i / m] = max(blocks[i / m], baskets[i]);
    }

    auto ans = 0;
    for (auto fruit : fruits) {
      auto placed = false;
      for (auto i = 0; i < M; i++) {
        if (fruit <= blocks[i]) {
          for (auto j = i * m; j < min(i * m + m, n); j++) {
            if (fruit <= baskets[j]) {
              baskets[j] = 0;
              break;
            }
          }

          blocks[i] = 0;
          for (auto j = i * m; j < min(i * m + m, n); j++) {
            blocks[i] = max(blocks[i], baskets[j]);
          }

          placed = true;
          break;
        }
      }
      if (!placed) ans++;
    }

    return ans;
  }
};

// Use Segment Tree
//
// Split baskets into 2 blocks, and track the maximum size of each block.
// For each block, split into 2 subblocks.
// Do it recursively untail block size is 1.
//
// We use 0 as root block.
// Each block i has sublocks 2i+1 & 2i+2.
// We will need an array of length 4n.
class Solution2 {
  int n;
  vector<int> tree;

  void build(vector<int>& nums, int id, int lo, int hi) {
    if (lo >= hi - 1) {  // leaf
      tree[id] = nums[lo];
      return;
    }

    auto mid = (lo + hi) / 2;
    auto leftID = id * 2 + 1;
    auto rightID = id * 2 + 2;
    build(nums, leftID, lo, mid);
    build(nums, rightID, mid, hi);
    tree[id] = max(tree[leftID], tree[rightID]);
  }

  bool find(int value) {
    if (value > tree[0]) return false;
    update(value, 0, 0, n);
    return true;
  }

  void update(int value, int id, int lo, int hi) {
    if (lo >= hi - 1) {  // leaf
      tree[id] = 0;
      return;
    }

    auto mid = (lo + hi) / 2;
    auto leftID = id * 2 + 1;
    auto rightID = id * 2 + 2;

    if (value <= tree[leftID]) {
      update(value, leftID, lo, mid);
    } else {
      update(value, rightID, mid, hi);
    }

    tree[id] = max(tree[leftID], tree[rightID]);
  }

 public:
  int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
    // Build segment tree
    n = baskets.size();
    tree.resize(4 * n);
    build(baskets, 0, 0, n);

    // Loop
    auto ans = 0;
    for (auto fruit : fruits) {
      auto placed = find(fruit);
      if (!placed) ans++;
    }

    return ans;
  }
};
