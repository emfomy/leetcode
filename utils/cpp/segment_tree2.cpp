#include <vector>

using namespace std;

void prepare() {
  vector<int> coords;
  // insert data and query ranges into coords

  // Sort & Unique
  sort(coords.begin(), coords.end());
  coords.erase(unique(coords.begin(), coords.end()), coords.end());
}

// Iteration Version (ZKW) + Coordinates
class SegmentTree {
  int n;
  const vector<int>& coords;
  vector<int> tree;  // parent i -> child 2i & 2i+1

 public:
  SegmentTree(vector<int>& coords) : coords(coords) {
    n = coords.size();
    tree.assign(2 * n, 0);
  }

  // O(logN); find first coords[idx] >= coord
  int getIdx(int coord) {  //
    auto it = lower_bound(coords.cbegin(), coords.cend(), coord);
    return distance(coords.cbegin(), it);
  }

  // Update: O(logN)
  void update(int coord, int value) {
    // Update leaf
    auto p = getIdx(coord) + n;
    tree[p] = value;

    // Update parents
    for (p /= 2; p >= 1; p /= 2) {
      tree[p] = tree[2 * p] + tree[2 * p + 1];
    }
  }

  // Query: O(logN); Sum in [l, r)
  int query(int lCoord, int rCoord) {
    int sum = 0;
    auto l = getIdx(lCoord) + n, r = getIdx(rCoord) + n;
    for (; l < r; l /= 2, r /= 2) {
      if (l & 1) sum += tree[l++];  // l is odd, should add tree[l]; then move l
      if (r & 1) sum += tree[--r];  // r is odd, should add tree[r-1]; then move r
    }
    return sum;
  }
};
