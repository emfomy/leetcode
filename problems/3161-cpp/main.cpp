// Source: https://leetcode.com/problems/block-placement-queries
// Title: Block Placement Queries
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There exists an infinite number line, with its origin at 0 and extending towards the **positive** x-axis.
//
// You are given a 2D array `queries`, which contains two types of queries:
//
// - For a query of type 1, `queries[i] = [1, x]`. Build an obstacle at distance `x` from the origin. It is guaranteed that there is **no** obstacle at distance `x` when the query is asked.
// - For a query of type 2, `queries[i] = [2, x, sz]`. Check if it is possible to place a block of size `sz` anywhere in the range `[0, x]` on the line, such that the block **entirely** lies in the range `[0, x]`. A block **cannot **be placed if it intersects with any obstacle, but it may touch it. Note that you do** not** actually place the block. Queries are separate.
//
// Return a boolean array `results`, where `results[i]` is `true` if you can place the block specified in the `i^th` query of type 2, and `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]
// Output: [false,true,true]
// Explanation:
// **https://assets.leetcode.com/uploads/2024/04/22/example0block.png**
// For query 0, place an obstacle at `x = 2`. A block of size at most 2 can be placed before `x = 3`.
// ```
//
// **Example 2:**
//
// ```
// Input: queries = [[1,7],[2,7,6],[1,2],[2,7,5],[2,7,6]]
// Output: [true,true,false]
// Explanation:
// **https://assets.leetcode.com/uploads/2024/04/22/example1block.png**
// - Place an obstacle at `x = 7` for query 0. A block of size at most 7 can be placed before `x = 7`.
// - Place an obstacle at `x = 2` for query 2. Now, a block of size at most 5 can be placed before `x = 7`, and a block of size at most 2 before `x = 2`.
// ```
//
// **Constraints:**
//
// - `1 <= queries.length <= 15 * 10^4`
// - `2 <= queries[i].length <= 3`
// - `1 <= queries[i][0] <= 2`
// - `1 <= x, sz <= min(5 * 10^4, 3 * queries.length)`
// - The input is generated such that for queries of type 1, no obstacle exists at distance `x` when the query is asked.
// - The input is generated such that there is at least one query of type 2.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <set>
#include <vector>

using namespace std;

// Segment Tree + Tree Set
//
// Let d[i] be the distance to the previous obstacle.
// Use segment tree to store the maximum d[x] of a range.
// Use a tree set to store the obstacles.
// We initialize these data structures with an obstacle at the end of the line.
//
// Say we have the new obstacle at x.
// We first insert x into the tree set.
// Let y be the next obstacle.
// We substract d by d[x] for (x, y] using the segment tree.
//
// Say we want to add a block with size sz into [0, x].
// We find the maximum d[i] in the range [0, x].
class Solution {
  class SegmentTree {
    // Lazy Tag
    struct Tag {
      int toAdd;  // 0 mean no need to update

      Tag() : toAdd(0) {}
      Tag(int toAdd) : toAdd(toAdd) {}

      // Check if is tagged
      bool isLazy() const {  //
        return toAdd != 0;
      }

      // Apply parent node's tag to current tag
      void apply(const Tag& t) {  //
        toAdd += t.toAdd;
      }

      // Reset tag
      void reset() {  //
        toAdd = 0;
      }
    };

    // Node info
    struct Info {
      int val;  // max value

      Info() : val(0) {}           // empty
      Info(int val) : val(val) {}  // leaf

      // Merge left & right child
      static Info merge(const Info& left, const Info& right) {  //
        return {max(left.val, right.val)};
      }

      // Apply lazy tag
      void apply(const Tag& t) {
        if (!t.isLazy()) return;
        val += t.toAdd;
      }
    };

    // Tree node
    struct Node {
      Info info;
      Tag tag;
    };

    int n;
    mutable vector<Node> tree;  // parent i -> child 2i & 2i+1

   public:
    SegmentTree(const vector<int>& nums) {
      n = nums.size();
      tree.resize(4 * n);
      build(nums, 1, 0, n);
    }

    // Update [l, r) by adding val
    void rangeUpdate(int l, int r, int val) {  //
      update(l, r, 1, 0, n, Tag(val));
    }

    // Query in [l, r)
    int query(int l, int r) {  //
      return query(l, r, 1, 0, n).val;
    }

   private:
    // Left/right son
    inline int leftChild(int p) const { return 2 * p; }
    inline int rightChild(int p) const { return 2 * p + 1; }

    // Apply tag
    void apply(int p, const Tag& t) const {
      tree[p].info.apply(t);
      tree[p].tag.apply(t);
    }

    // Push up from childs
    void pushUp(int p) {  //
      tree[p].info = Info::merge(tree[leftChild(p)].info, tree[rightChild(p)].info);
    }

    // Push down to childs
    void pushDown(int p) const {  //
      auto& node = tree[p];

      if (!node.tag.isLazy()) return;
      apply(leftChild(p), node.tag);
      apply(rightChild(p), node.tag);
      node.tag.reset();
    }

    // Build: O(n)
    void build(const vector<int>& nums, int node, int lo, int hi) {
      // leaf node
      if (lo == hi - 1) {
        tree[node].info = Info(nums[lo]);
        return;
      }

      int mid = lo + (hi - lo) / 2;
      build(nums, leftChild(node), lo, mid);
      build(nums, rightChild(node), mid, hi);
      pushUp(node);
    }

    // Update: O(logN); update range [l, r)
    void update(int l, int r, int p, int lo, int hi, const Tag& t) {
      // Out of range
      if (r <= lo || hi <= l) return;

      // Full overlap
      if (l <= lo && hi <= r) {
        apply(p, t);
        return;
      }

      // Partial overlap
      pushDown(p);
      int mid = lo + (hi - lo) / 2;
      update(l, r, leftChild(p), lo, mid, t);
      update(l, r, rightChild(p), mid, hi, t);
      pushUp(p);
    }

    // Query: O(logN); query info in [l, r)
    Info query(int l, int r, int node, int lo, int hi) const {
      // Out of range
      if (r <= lo || hi <= l) return {};

      // Full overlap
      if (l <= lo && hi <= r) return tree[node].info;

      // Partial overlap
      pushDown(node);
      int mid = lo + (hi - lo) / 2;
      auto leftInfo = query(l, r, leftChild(node), lo, mid);
      auto rightInfo = query(l, r, rightChild(node), mid, hi);
      return Info::merge(leftInfo, rightInfo);
    }
  };

 public:
  vector<bool> getResults(const vector<vector<int>>& queries) {
    const int n = queries.size();
    const int m = 3 * n;  // max range

    // Build tree
    auto d = vector<int>(m + 1);
    iota(d.begin(), d.end(), 0);
    auto tree = SegmentTree(d);

    // Obstacles
    auto obstacles = set<int>();
    obstacles.insert(m);

    // Query
    auto res = vector<bool>();
    for (const auto& query : queries) {
      if (query[0] == 1) {  // type 1
        const int x = query[1];

        // Find previous obstacle
        const auto [it, _] = obstacles.emplace(x);
        const int y = *(next(it));

        const int dx = tree.query(x, x + 1);
        tree.rangeUpdate(x + 1, y + 1, -dx);
      } else {  // type 2
        const int x = query[1], sz = query[2];
        int maxGap = tree.query(0, x + 1);
        res.push_back(maxGap >= sz);
      }
    }

    return res;
  }
};

// Segment Tree + Tree Set
//
// Let g[i] be the gap size to the left for obstacle i.
// Note that g[i] = 0 is i is not an obstacle.
//
// Use segment tree to store the maximum g[x].
// Use a tree set to store the obstacles.
// We initialize these data structures with obstacles at the front and the  end of the line.
//
// Say we have the new obstacle at x.
// We first insert x into the tree set.
// Let y be the previous obstacle, and z be the next obstacle.
// We update g[x] = x-y and g[z] = z-x using the segment tree.
//
// Say we want to add a block with size sz into [0, x].
// Let y be the previous obstacle.
// If x-y >= sz, then we the block can be placed.
// Otherwise, find the maximum g[i] in [0, y].
class Solution2 {
  class SegmentTree {
    int n;
    vector<int> tree;  // parent i -> child 2i & 2i+1

   public:
    SegmentTree(int n) : n(n), tree(2 * n, 0) {}

    // Update: O(logN); nums[i] = val
    void update(int i, int val) {
      // Update leaf
      i += n;
      tree[i] = val;

      // Update parents
      for (i /= 2; i >= 1; i /= 2) {
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
      }
    }

    // Query: O(logN); Max in [l, r)
    int query(int l, int r) const {
      int res = 0;
      for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l & 1) res = max(res, tree[l++]);  // l is odd, should add tree[l]; then move l
        if (r & 1) res = max(res, tree[--r]);  // r is odd, should add tree[r-1]; then move r
      }
      return res;
    }
  };

 public:
  vector<bool> getResults(const vector<vector<int>>& queries) {
    const int n = queries.size();
    const int m = 3 * n;  // max range

    // Build tree and set
    auto tree = SegmentTree(m + 1);
    auto obstacles = set<int>({0, m});
    tree.update(m, m);

    // Query
    auto res = vector<bool>();
    for (const auto& query : queries) {
      if (query[0] == 1) {  // type 1
        const int x = query[1];

        const auto [it, _] = obstacles.emplace(x);
        const int y = *(prev(it));  // prev obstacle
        const int z = *(next(it));  // next obstacle

        tree.update(x, x - y);
        tree.update(z, z - x);
      } else {  // type 2
        const int x = query[1], sz = query[2];
        const int y = *(prev(obstacles.lower_bound(x)));  // prev obstacle

        const bool valid = (x - y >= sz) || (tree.query(0, y + 1) >= sz);
        res.push_back(valid);
      }
    }

    return res;
  }
};
