#include <cstdint>
#include <vector>

using namespace std;

// Recursion Version, Lazy Update
//
// [l, r) query/update range
// [lo, hi) segment of node p
class SegmentTree {
  // Lazy Tag
  struct Tag {
    int64_t toAdd;  // 0 mean no need to update

    Tag() : toAdd(0) {}
    Tag(int64_t toAdd) : toAdd(toAdd) {}

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

  // Node info, support max, min, sum
  struct Info {
    int64_t sum;
    int64_t maxVal;
    int64_t minVal;
    int len;  // used to lazy update sum

    Info() : sum(0), maxVal(INT_MIN), minVal(INT_MAX), len(0) {}       // empty
    Info(int64_t val) : sum(val), maxVal(val), minVal(val), len(1) {}  // leaf

    // Merge left & right child
    static Info merge(const Info& left, const Info& right) {
      Info res;
      res.sum = left.sum + right.sum;
      res.maxVal = max(left.maxVal, right.maxVal);
      res.minVal = min(left.minVal, right.minVal);
      res.len = left.len + right.len;
      return res;
    }

    // Apply lazy tag
    void apply(const Tag& t) {
      if (!t.isLazy()) return;

      sum += t.toAdd * len;
      maxVal += t.toAdd;
      minVal += t.toAdd;
    }
  };

  // Tree node
  struct Node {
    Info info;
    Tag tag;
  };

  int n;
  vector<Node> tree;  // parent i -> child 2i & 2i+1

 public:
  SegmentTree(int n) : n(n), tree(4 * n) {}

  SegmentTree(const vector<int>& nums) {
    n = nums.size();
    tree.resize(4 * n);
    build(nums, 1, 0, n);
  }

  // Update [l, r) by adding val
  void rangeUpdate(int l, int r, int64_t val) {  //
    update(l, r, 1, 0, n, Tag(val));
  }

  // Query in [l, r)
  Info query(int l, int r) {  //
    return query(l, r, 1, 0, n);
  }

 private:
  // Left/right son
  int leftChild(int p) { return 2 * p; }
  int rightChild(int node) { return 2 * node + 1; }

  // Apply tag
  void apply(int p, const Tag& t) {
    tree[p].info.apply(t);
    tree[p].tag.apply(t);
  }

  // Push up from childs
  void pushUp(int p) {  //
    tree[p].info = Info::merge(tree[leftChild(p)].info, tree[rightChild(p)].info);
  }

  // Push down to childs
  void pushDown(int p) {  //
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

    auto mid = lo + (hi - lo) / 2;
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
    auto mid = lo + (hi - lo) / 2;
    update(l, r, leftChild(p), lo, mid, t);
    update(l, r, rightChild(p), lo, mid, t);
    pushUp(p);
  }

  // Query: O(logN); query info in [l, r)
  Info query(int l, int r, int node, int lo, int hi) {
    // Out of range
    if (r <= lo || hi <= l) return {};

    // Full overlap
    if (l <= lo && hi <= r) return tree[node].info;

    // Partial overlap
    pushDown(node);
    auto mid = lo + (hi - lo) / 2;
    auto leftInfo = query(l, r, leftChild(node), lo, mid);
    auto rightInfo = query(l, r, rightChild(node), mid, hi);
    return Info::merge(leftInfo, rightInfo);
  }
};
