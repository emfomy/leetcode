#include <vector>

using namespace std;

// Support range update
//
// Let D be the diff array
// D[t] = A[t] - A[t-1], A[-1] = 0
//
// A[x]    = D[0] + D[1] + ... + D[x]
// Sum[<x] = A[0] + A[1] + ... + A[x-1]
//         = Sum[t<x] D[t] * (x-t)
//         = x Sum D - Sum[t<x] t*D[t]
// B[t] = t * D[t]
// Use a Fenwick for D, and another Fenwick for B
// Sum[<x] = x * D.query(x) - B.query(x)
class FenwickTreeRange {
  int n;

  // tree[i] = sum of range [i-lowbit(i), i); length is lowbit(i)
  vector<int> tree1;  // D[t]
  vector<int> tree2;  // t*D[t]

 private:
  // Update: O(logN); nums[idx] += delta
  void update(vector<int>& tree, int idx, int delta) {
    // start at x+1 since x in [0, x+1)
    for (int i = idx + 1; i <= n; i += (i & -i)) {
      tree[i] += delta;
    }
  }

  // Query: O(logN); Sum of [0, r)
  int query(const vector<int>& tree, int r) const {
    int sum = 0;
    for (int i = r; i >= 1; i -= (i & -i)) {
      sum += tree[i];
    }
    return sum;
  }

 public:
  FenwickTreeRange(int n) : n(n), tree1(n + 1, 0), tree2(n + 1, 0) {}

  FenwickTreeRange(const vector<int>& nums) {
    n = nums.size();
    tree1.assign(n + 1, 0);
    tree2.assign(n + 1, 0);

    // build: O(N)
    if (n <= 0) return;
    tree1[1] = nums[0];
    for (int i = 2; i <= n; ++i) {
      tree1[i] = nums[i - 1] - nums[i - 2];
      tree2[i] = (i - 1) * tree1[i];
    }
    for (int i = 1; i <= n; ++i) {
      int p = i + (i & -i);  // parent
      if (p <= n) {
        tree1[p] += tree1[i];
        tree2[p] += tree2[i];
      }
    }
  }

  // Range Update: O(logN); [l, r) += delta
  void update(int l, int r, int delta) {
    if (l >= r) return;
    update(tree1, l, delta);
    update(tree1, r, -delta);
    update(tree2, l, l * delta);
    update(tree2, r, -r * delta);
  }

  // Query: O(logN); Sum of [0, r)
  int query(int r) const {  //
    return r * query(tree1, r) - query(tree2, r);
  }

  // Range Query: O(logN); Sum of [l, r)
  int query(int l, int r) const {
    if (l >= r) return 0;
    return query(r) - query(l);
  }
};
