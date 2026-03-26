#include <bit>
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

  FenwickTree(const vector<int>& nums) {
    n = nums.size();
    tree.assign(n + 1, 0);

    // build: O(N)
    for (int i = 1; i <= n; ++i) tree[i] = nums[i - 1];
    for (int i = 1; i <= n; ++i) {
      int p = i + (i & -i);  // parent
      if (p <= n) tree[p] += tree[i];
    }
  }

  // Update: O(logN); nums[idx] += delta
  void update(int idx, int delta) {
    // start at x+1 since x in [0, x+1)
    for (int i = idx + 1; i <= n; i += (i & -i)) {
      tree[i] += delta;
    }
  }

  // Query: O(logN); Sum of [0, r)
  int query(int r) const {
    int sum = 0;
    for (int i = r; i >= 1; i -= (i & -i)) {
      sum += tree[i];
    }
    return sum;
  }

  // Range Query: O(logN); Sum of [l, r)
  int query(int l, int r) const {
    if (l >= r) return 0;
    return query(r) - query(l);
  }

  // Query: O(logN); Find last r with sum [0, r) < k
  int queryFirst(int k) {
    int r = 0;
    const int highbit = 1 << bit_width(static_cast<unsigned>(n - 1));
    for (int b = highbit; b > 0 && k > 0; b >>= 1) {
      if (r + b <= n && tree[r + b] < k) {
        r += b;
        k -= tree[r];
      }
    }

    return r;
  }
};
