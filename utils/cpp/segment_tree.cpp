#include <vector>
using namespace std;

// Index: 0    1    2    3    4    5    6    7    8    9    10   11   12
//                      [1----------------------------------------------]
//       [1-----------] [2------------------------------------] [3------]
//       [3-----------] [4----------------] [5----------------] [6------]
//       [6-] [7------] [8------] [9------] [10-----] [11-----] [12-----]
//       [13] [14] [15] [16] [17] [18] [19] [20] [21] [22] [23] [24] [25]
//
// Index: 3    4    5    6    7    8    9    10   11   12   0    1    2
//       [1-------------------------------------------------------------]
//       [2------------------------------------] [3---------------------]
//       [4----------------] [5----------------] [6-----------] [7------]
//       [8------] [9------] [10-----] [11-----] [12-----] [13] [14] [15]
//       [16] [17] [18] [19] [20] [21] [22] [23] [24] [25]
//
// Note that the tree is unbalanced. Some node is not contiguous.
// For example, node 3 contains [0, 1, 2, 11, 12],
// where [11~12] is left child and [0~2] is right child.
//
// ---
//
// To query [l, r), we traverse from leave to parent. (Here l, r are node IDs)
// If l >= r, then the range is empty and we can end the loop.
//
// If l is odd, then it is the right child of its parent, which means its parent is not is [l, r).
// Now we must add tree[l] to the result and increase l (exclude current node).
//
// If r is odd, then (r-1) it is the left child of its parent, which means its parent is not is [l, r).
// Now we must add tree[r-1] to the result and decrease r (exclude current node).

// Iteration Version (ZKW)
class SegmentTree {
  int n;
  vector<int> tree;  // parent i -> child 2i & 2i+1

 public:
  SegmentTree(int n) : n(n), tree(2 * n, 0) {}

  SegmentTree(vector<int>& nums) {
    n = nums.size();
    tree.resize(2 * n);  // only need 2n for iteration version

    // build: O(N)
    for (auto i = 0; i < n; ++i) tree[n + i] = nums[i];  // leaves
    for (auto i = n - 1; i > 0; --i) tree[i] = tree[2 * i] + tree[2 * i + 1];
  }

  // Update: O(logN)
  void update(int i, int value) {
    // Update leaf
    i += n;
    tree[i] = value;

    // Update parents
    for (i /= 2; i >= 1; i /= 2) {
      tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
  }

  // Query: O(logN); Sum in [l, r)
  int query(int l, int r) {
    int sum = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) sum += tree[l++];  // l is odd, should add tree[l]; then move l
      if (r & 1) sum += tree[--r];  // r is odd, should add tree[r-1]; then move r
    }
    return sum;
  }
};
