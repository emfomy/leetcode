#include <vector>

using namespace std;

// 2D Iteration Version (ZKW)
class SegmentTree2D {
  int m, n;                  // number of rows / columns
  vector<vector<int>> tree;  // tree[i][j] = tree[i][2j] + tree[i][2j+1]
                             //            = tree[2i][j] + tree[2i+1][j]

 public:
  SegmentTree2D(int m, int n) : m(m), n(n) {  //
    tree.assign(2 * m, vector<int>(2 * n, 0));
  }

  SegmentTree2D(const vector<vector<int>>& nums) {
    m = nums.size(), n = nums[0].size();
    tree.assign(2 * m, vector<int>(2 * n, 0));

    // build: O(MN)

    // Set leaves, set [m, 2m) x [n, 2n)
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        tree[i + m][j + n] = nums[i][j];
      }
    }

    // Update row-wise, set [m, 2m) x [1, n)
    for (int i = m; i < 2 * m; ++i) {
      for (int j = n - 1; j >= 1; --j) {
        tree[i][j] = tree[i][2 * j] + tree[i][2 * j + 1];
      }
    }

    // Update column-wise, set [1, m) x [1, 2n)
    // here we put i in outer loop for better memory efficiency
    for (int i = m - 1; i >= 1; --i) {
      for (int j = 1; j < 2 * n; ++j) {
        tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
      }
    }
  }

  // Update: O(logM logN); nums[r][c] = val
  void update(int r, int c, int val) {
    // Update leaf; [r][c] in [m, 2m) x [n, 2n)
    r += m, c += n;
    tree[r][c] = val;

    // Update row-wise; [r][j] in [m, 2m) x [1, n)
    for (int j = c / 2; j >= 1; j /= 2) {
      tree[r][j] = tree[r][2 * j] + tree[r][2 * j + 1];
    }

    // Update column-wise; [i][j] in [1, m) x [1, 2n)
    for (int i = r / 2; i >= 1; i /= 2) {
      for (int j = c; j >= 1; j /= 2) {
        tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
      }
    }
  }

  // Query: O(logN); Sum in [r] x [c0, c1)
  int queryRow(int r, int c0, int c1) const {
    int sum = 0;
    for (c0 += n, c1 += n; c0 < c1; c0 /= 2, c1 /= 2) {
      if (c0 & 1) sum += tree[r][c0++];
      if (c1 & 1) sum += tree[r][--c1];
    }
    return sum;
  }

  // Query: O(logM logN); Sum in [r0, r1) x [c0, c1)
  int query(int r0, int c0, int r1, int c1) const {
    int sum = 0;
    for (r0 += m, r1 += m; r0 < r1; r0 /= 2, r1 /= 2) {
      if (r0 & 1) sum += queryRow(r0++, c0, c1);
      if (r1 & 1) sum += queryRow(--r1, c0, c1);
    }
    return sum;
  }
};
