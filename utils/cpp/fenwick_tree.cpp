#include <vector>
using namespace std;

// Index:  1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17
// Len 1: [-]     [-]     [5]     [-]     [-]     [-]     [-]     [-]     [-]
// Len 2: [-----]         [5----]         [-----]         [-----]         [--..
// Len 4: [-------------]                 [-------------]                 [--..
// Len 8: [----------------5------------]                                 [--..
//
// To update 5, we need to update [5, 5] [5, 6], [5, 8], ... (1-indexed)
// Note that we skip the len 4 node.

class FenwickTree {
  int n;
  vector<int> tree;  // tree[i] = sum of range [i-lowbit(i), i); length is lowbit(i)

 public:
  FenwickTree(int n) : n(n), tree(n + 1, 0) {}

  FenwickTree(vector<int>& nums) {
    n = nums.size();
    tree.assign(n + 1, 0);

    // build: O(N)
    for (auto i = 0; i < n; i++) tree[i + 1] = nums[i];
    for (auto i = 1; i <= n; ++i) {
      auto parent = i + (i & -i);
      if (parent <= n) tree[parent] += tree[i];
    }
  }

  // Update: O(logN); nums[idx] += delta
  void update(int idx, int delta) {
    // start at x+1 since x in [0, x+1)
    for (auto i = idx + 1; i <= n; i += (i & -i)) {
      tree[i] += delta;
    }
  }

  // Query: O(logN); Sum of [0, r)
  int query(int r) {
    int sum = 0;
    for (auto i = r; i > 0; i -= (i & -i)) {
      sum += tree[i];
    }
    return sum;
  }

  // Range Query: O(logN); Sum of [l, r)
  int query(int l, int r) {
    if (l >= r) return 0;
    return query(r) - query(l);
  }
};
