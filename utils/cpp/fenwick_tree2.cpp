#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

void prepare() {
  vector<int> coords;
  // insert data and query ranges into coords

  // Sort & Unique
  sort(coords.begin(), coords.end());
  coords.erase(unique(coords.begin(), coords.end()), coords.end());
}

class FenwickTree {
  int n;
  const vector<int>& coords;
  vector<int> tree;  // tree[i] = sum of range [i-lowbit(i), i); length is lowbit(i)

 public:
  FenwickTree(vector<int>& coords) : coords(coords) {
    n = coords.size();
    tree.assign(n + 1, 0);
  }

  // O(logN); find first coords[idx] >= coord
  int getIdx(int coord) {  //
    auto it = lower_bound(coords.cbegin(), coords.cend(), coord);
    return distance(coords.cbegin(), it);
  }

  // Update: O(logN); nums[idx] += delta
  void update(int coord, int delta) {
    // start at x+1 since x in [0, x+1)
    for (auto i = getIdx(coord) + 1; i <= n; i += (i & -i)) {
      tree[i] += delta;
    }
  }

  // Query: O(logN); Sum of [0, r)
  int query(int r) {
    int sum = 0;
    for (auto i = getIdx(r); i > 0; i -= (i & -i)) {
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
