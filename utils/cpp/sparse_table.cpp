#include <algorithm>
#include <bit>
#include <vector>

using namespace std;

// Stores the minimal
class SparseTable {
  int n;
  vector<vector<int>> table;  // table[i][j] = min of [i, i+2^j)
  vector<int> logs;           // precompute logs

 public:
  // Build, O(NlogN)
  SparseTable(const vector<int>& nums) {
    n = nums.size();
    int logn = bit_width(size_t(n));  // floor(log(n)) + 1

    table.assign(n, vector<int>(logn));
    logs.assign(n + 1, 0);

    // Precompute logs (floor value)
    for (int i = 2; i <= n; ++i) {
      logs[i] = logs[i / 2] + 1;
    }

    // Initialize table layer 0
    for (int i = 0; i < n; ++i) {
      table[i][0] = nums[i];
    }

    // Fill the table
    for (int j = 1; j < logn; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  // Query: O(1); Min in [l, r)
  int query(int l, int r) const {
    int j = logs[r - l];
    return min(table[l][j], table[r - (1 << j)][j]);
  }
};
