#include <vector>

using namespace std;

class FenwickTree2D {
  int m, n;                  // number of rows / columns
  vector<vector<int>> tree;  // tree[i][j] = sum of range [i-lowbit(i), i) x [j-lowbit(j), j)

 public:
  FenwickTree2D(int m, int n) : m(m), n(n) {  //
    tree.assign(m + 1, vector<int>(n + 1, 0));
  }

  FenwickTree2D(const vector<vector<int>>& nums) {
    m = nums.size(), n = nums[0].size();
    tree.assign(m + 1, vector<int>(n + 1, 0));

    // build: O(MN)
    // now tree[i][j] = sum of [i-1, i) x [j-1, j)
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        tree[i][j] = nums[i - 1][j - 1];
      }
    }

    // Update row-wise parent
    // now tree[i][j] = sum of [i-1, i) x [j-lowbit(j), j)
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        int p = j + (j & -j);
        if (p <= n) tree[i][p] += tree[i][j];
      }
    }

    // Update column-wise parent
    // here we put i in outer loop for better memory efficiency
    // now tree[i][j] = sum of [i-lowbit(i), i) x [j-lowbit(j), j)
    for (int i = 1; i <= m; ++i) {
      int p = i + (i & -i);
      if (p > m) continue;
      for (int j = 1; j <= n; ++j) {
        tree[p][j] += tree[i][j];
      }
    }
  }

  // Update: O(logM logN); nums[row][col] += delta
  void update(int row, int col, int delta) {
    // start at x+1 since x in [0, x+1)
    for (int i = row + 1; i <= m; i += (i & -i)) {
      for (int j = col + 1; j <= n; j += (j & -j)) {
        tree[i][j] += delta;
      }
    }
  }

  // Query: O(logN logN); Sum of [0, row) x [0, col)
  int query(int row, int col) const {
    int sum = 0;
    for (int i = row; i >= 1; i -= (i & -i)) {
      for (int j = col; j >= 1; j -= (j & -j)) {
        sum += tree[i][j];
      }
    }
    return sum;
  }

  // Range Query: O(logN); Sum of [rowLo, rowHi) x [colLo, colHi)
  int query(int rowLo, int colLo, int rowHi, int colHi) const {
    if (rowLo >= rowHi || colLo >= colHi) return 0;
    return query(rowHi, colHi) + query(rowLo, colLo) - query(rowHi, colLo) - query(rowLo, colHi);
  }
};
