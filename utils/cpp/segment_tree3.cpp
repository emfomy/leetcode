#include <vector>

using namespace std;

// Recursion Version
class SegmentTree2D {
  int n;
  vector<int> tree;  // parent i -> child 2i & 2i+1

 public:
  SegmentTree2D(int n) : n(n), tree(4 * n, 0) {}

  SegmentTree2D(const vector<int>& nums) {
    n = nums.size();
    tree.resize(4 * n);
    build(nums, 1, 0, n);
  }

  void update(int idx, int val) { update(idx, val, 1, 0, n); }
  int query(int l, int r) { return query(l, r, 1, 0, n); }
  int queryFirst(int l, int r, int k) { return queryFirst(l, r, k, 1, 0, n); }

 private:
  // Left/right son
  inline int leftChild(int node) const { return 2 * node; }
  inline int rightChild(int node) const { return 2 * node + 1; }

  // Push Up
  void pushUp(int node) {  //
    tree[node] = max(tree[leftChild(node)], tree[rightChild(node)]);
  }

  // Build: O(n)
  void build(const vector<int>& nums, int node, int lo, int hi) {
    // leaf node
    if (lo == hi - 1) {
      tree[node] = nums[lo];
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
      tree[node] = val;
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

  // Query: O(logN); Max in [l, r)
  int query(int l, int r, int node, int lo, int hi) const {
    // Out of range
    if (r <= lo || hi <= l) return INT_MIN;

    // Full overlap
    if (l <= lo && hi <= r) return tree[node];

    // Partial overlap
    int mid = lo + (hi - lo) / 2;
    int leftVal = query(l, r, leftChild(node), lo, mid);
    int rightVal = query(l, r, rightChild(node), mid, hi);
    return max(leftVal, rightVal);
  }

  // QueryFirst: O(logN); Find first in [l, r) such that val >= k
  int queryFirst(int l, int r, int k, int node, int lo, int hi) const {
    // Out of range
    if (r <= lo || hi <= l) return -1;

    // Not found
    if (tree[node] < k) return -1;

    // Leaf
    if (lo == hi - 1) return lo;

    // Recursion
    int mid = lo + (hi - lo) / 2;
    int res = queryFirst(l, r, k, leftChild(node), lo, mid);
    if (res != -1) return res;
    return queryFirst(l, r, k, rightChild(node), mid, hi);
  }
};
