// Source: https://leetcode.com/problems/find-x-value-of-array-ii
// Title: Find X Value of Array II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of **positive** integers `nums` and a **positive** integer `k`. You are also given a 2D array `queries`, where `queries[i] = [index_i, value_i, start_i, x_i]`.
//
// You are allowed to perform an operation **once** on `nums`, where you can remove any **suffix** from `nums` such that `nums` remains **non-empty**.
//
// The **x-value** of `nums` **for a given** `x` is defined as the number of ways to perform this operation so that the **product** of the remaining elements leaves a remainder of `x` **modulo** `k`.
//
// For each query in `queries` you need to determine the **x-value** of `nums` for `x_i` after performing the following actions:
//
// - Update `nums[index_i]` to `value_i`. Only this step persists for the rest of the queries.
// - **Remove** the prefix `nums[0..(start_i - 1)]` (where `nums[0..(-1)]` will be used to represent the **empty** prefix).
//
// Return an array `result` of size `queries.length` where `result[i]` is the answer for the `i^th` query.
//
// A **prefix** of an array is a <button>subarray</button> that starts from the beginning of the array and extends to any point within it.
//
// A **suffix** of an array is a <button>subarray</button> that starts at any point within the array and extends to the end of the array.
//
// **Note** that the prefix and suffix to be chosen for the operation can be **empty**.
//
// **Note** that x-value has a different definition in this version.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,4,5], k = 3, queries = [[2,2,0,2],[3,3,3,0],[0,1,0,1]]
// Output: [2,2,2]
// Explanation:
// - For query 0, `nums` becomes `[1, 2, 2, 4, 5]`, and the empty prefix **must** be removed. The possible operations are:
//   - Remove the suffix `[2, 4, 5]`. `nums` becomes `[1, 2]`.
//   - Remove the empty suffix. `nums` becomes `[1, 2, 2, 4, 5]` with a product 80, which gives remainder 2 when divided by 3.
// - For query 1, `nums` becomes `[1, 2, 2, 3, 5]`, and the prefix `[1, 2, 2]` **must** be removed. The possible operations are:
//   - Remove the empty suffix. `nums` becomes `[3, 5]`.
//   - Remove the suffix `[5]`. `nums` becomes `[3]`.
// - For query 2, `nums` becomes `[1, 2, 2, 3, 5]`, and the empty prefix **must** be removed. The possible operations are:
//   - Remove the suffix `[2, 2, 3, 5]`. `nums` becomes `[1]`.
//   - Remove the suffix `[3, 5]`. `nums` becomes `[1, 2, 2]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,4,8,16,32], k = 4, queries = [[0,2,0,2],[0,2,0,1]]
// Output: [1,0]
// Explanation:
// - For query 0, `nums` becomes `[2, 2, 4, 8, 16, 32]`. The only possible operation is:
//   - Remove the suffix `[2, 4, 8, 16, 32]`.
// - For query 1, `nums` becomes `[2, 2, 4, 8, 16, 32]`. There is no possible way to perform the operation.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,1,2,1,1], k = 2, queries = [[2,1,0,1]]
// Output: [5]
// ```
//
// **Constraints:**
//
// - `1 <= nums[i] <= 10^9`
// - `1 <= nums.length <= 10^5`
// - `1 <= k <= 5`
// - `1 <= queries.length <= 2 * 10^4`
// - `queries[i] == [index_i, value_i, start_i, x_i]`
// - `0 <= index_i <= nums.length - 1`
// - `1 <= value_i <= 10^9`
// - `0 <= start_i <= nums.length - 1`
// - `0 <= x_i <= k - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>

#include <cstddef>
#include <vector>

using namespace std;

// Segment Tree
//
// In the tree node, we store the number of prefix subarrays for each product (modulo k).
class Solution {
  // ZKW
  class SegmentTree {
    static constexpr int K = 5;

    // First k items are the number of prefix subarrays with product r.
    // Last item is the product of this node
    using Node = array<int, K + 1>;

    int k, n;
    vector<Node> tree;  // parent i -> child 2i & 2i+1

   public:
    SegmentTree(const vector<int>& nums, int k) : k(k) {
      n = nums.size();
      tree.resize(4 * n);
      build(nums, 1, 0, n);
    }

    void update(int idx, int val) { update(idx, val, 1, 0, n); }
    Node query(int l, int r) { return query(l, r, 1, 0, n); }

   private:
    // Left/right son
    inline int leftChild(int node) const { return 2 * node; }
    inline int rightChild(int i) const { return 2 * i + 1; }

    // Init a leaf
    void makeLeaf(int node, int val) {
      int x = val % k;
      tree[node].fill(0);
      tree[node][x] = 1;  // count
      tree[node][K] = x;  // product
    }

    // Merge children for parent
    void merge(Node& parent, Node& left, Node& right) const {
      int prodL = left[K], prodR = right[K];

      parent[K] = (prodL * prodR) % k;

      // Case 1: Entirely within the left node
      for (int x = 0; x < k; ++x) {
        parent[x] = left[x];
      }

      // Case 2: Contains the entire left interval
      for (int x = 0; x < k; ++x) {
        parent[(prodL * x) % k] += right[x];
      }
    }

    // Push Up
    void pushUp(int node) {  //
      merge(tree[node], tree[leftChild(node)], tree[rightChild(node)]);
    }

    // Build: O(n)
    void build(const vector<int>& nums, int node, int lo, int hi) {
      // leaf node
      if (lo == hi - 1) {
        makeLeaf(node, nums[lo]);
        return;
      }

      int mid = lo + (hi - lo) / 2;
      build(nums, leftChild(node), lo, mid);
      build(nums, rightChild(node), mid, hi);
      pushUp(node);
    }

    // Update: O(logN)
    void update(int idx, int val, int node, int lo, int hi) {
      // Leaf node
      if (lo == hi - 1) {
        makeLeaf(node, val);
        return;
      }

      int mid = lo + (hi - lo) / 2;
      if (idx < mid) {
        update(idx, val, leftChild(node), lo, mid);
      } else {
        update(idx, val, rightChild(node), mid, hi);
      }
      pushUp(node);
    }

    // Query: O(logN); Count in [l, r)
    Node query(int l, int r, int node, int lo, int hi) const {
      int mid = lo + (hi - lo) / 2;

      // Full overlap
      if (l <= lo && hi <= r) return tree[node];

      // Only left
      if (r <= mid) return query(l, r, leftChild(node), lo, mid);

      // Only right
      if (mid <= l) return query(l, r, rightChild(node), mid, hi);

      // Partial overlap
      Node left = query(l, r, leftChild(node), lo, mid);
      Node right = query(l, r, rightChild(node), mid, hi);
      Node parent;
      merge(parent, left, right);
      return parent;
    }
  };

 public:
  vector<int> resultArray(const vector<int>& nums, int k, const vector<vector<int>>& queries) {
    const int n = nums.size();
    const int q = queries.size();

    // Init
    auto tree = SegmentTree(nums, k);

    // Query
    auto ans = vector<int>();
    ans.reserve(q);
    for (const auto& query : queries) {
      int index = query[0], value = query[1], start = query[2], x = query[3];
      tree.update(index, value);
      ans.push_back(tree.query(start, n)[x]);
    }

    return ans;
  }
};
