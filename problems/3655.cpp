// Source: https://leetcode.com/problems/xor-after-range-multiplication-queries-ii
// Title: XOR After Range Multiplication Queries II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n` and a 2D integer array `queries` of size `q`, where `queries[i] = [l_i, r_i, k_i, v_i]`.
//
// For each query, you must apply the following operations in order:
//
// - Set `idx = l_i`.
// - While `idx <= r_i`:
//   - Update: `nums[idx] = (nums[idx] * v_i) % (10^9 + 7)`.
//   - Set `idx += k_i`.
//
// Return the **bitwise XOR** of all elements in `nums` after processing all queries.
//
// **Example 1:**
//
// ```
// Input: nums = [1,1,1], queries = [[0,2,1,4]]
// Output: 4
// Explanation:
// - A single query `[0, 2, 1, 4]` multiplies every element from index 0 through index 2 by 4.
// - The array changes from `[1, 1, 1]` to `[4, 4, 4]`.
// - The XOR of all elements is `4 ^ 4 ^ 4 = 4`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,3,1,5,4], queries = [[1,4,2,3],[0,2,1,2]]
// Output: 31
// Explanation:
// - The first query `[1, 4, 2, 3]` multiplies the elements at indices 1 and 3 by 3, transforming the array to `[2, 9, 1, 15, 4]`.
// - The second query `[0, 2, 1, 2]` multiplies the elements at indices 0, 1, and 2 by 2, resulting in `[4, 18, 2, 15, 4]`.
// - Finally, the XOR of all elements is `4 ^ 18 ^ 2 ^ 15 ^ 4 = 31`.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `1 <= q == queries.length <= 10^5`
// - `queries[i] = [l_i, r_i, k_i, v_i]`
// - `0 <= l_i <= r_i < n`
// - `1 <= k_i <= n`
// - `1 <= v_i <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// Simulation, TLE
// Worst Case O(qn)
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

 public:
  int xorAfterQueries(vector<int>& nums, const vector<vector<int>>& queries) {
    // Queries
    for (const auto& query : queries) {
      const int l = query[0], r = query[1], k = query[2];
      const int64_t v = query[3];
      for (int i = l; i <= r; i += k) {
        nums[i] = (nums[i] * v) % modulo;
      }
    }

    // XOR
    int ans = 0;
    for (const int num : nums) {
      ans ^= num;
    }

    return ans;
  }
};

// Difference Array
// O(sqrt(n)q + sqrt(n)n) Time, O(sqrt(n)n) Space
//
// Let m = sqrt(n).
//
// For k >= m, there are at most n/m elements to update, just update it directly.
// For k < m, there are too many elements to update, we use lazy update trick.
// We create a difference array for each k <= m.
// For each query, diff_k[l] *= v and diff_k[r+1] *= inv(v)
class Solution2 {
  constexpr static int64_t modulo = 1e9 + 7;

  int64_t mod(int64_t x) {  //
    return x % modulo;
  }

  int64_t pow(int64_t x, int p) {  //
    int64_t res = 1;
    while (p > 0) {
      if (p % 2) res = mod(res * x);
      x = mod(x * x);
      p >>= 1;
    }
    return res;
  }

  int64_t inv(int64_t x) {  //
    return pow(x, modulo - 2);
  }

 public:
  int xorAfterQueries(vector<int>& nums, const vector<vector<int>>& queries) {
    const int n = nums.size();
    const int m = sqrt(n);

    // Prepare difference array
    auto diffs = vector<vector<int64_t>>(m, vector<int64_t>(n + m, 1));

    // Queries
    for (const auto& query : queries) {
      const int l = query[0], r = query[1], k = query[2];
      const int64_t v = query[3];

      if (k >= m) {
        for (int i = l; i <= r; i += k) {
          nums[i] = mod(nums[i] * v);
        }
      } else {
        int r2 = ((r - l) / k + 1) * k + l;  // real ending
        diffs[k][l] = mod(diffs[k][l] * v);
        diffs[k][r2] = mod(diffs[k][r2] * inv(v));
      }
    }

    // Fill difference array
    for (int k = 1; k < m; ++k) {
      for (int i = k; i < n; ++i) {
        diffs[k][i] = mod(diffs[k][i] * diffs[k][i - k]);
      }
    }

    // XOR
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      int64_t num = nums[i];
      for (int k = 1; k < m; ++k) {
        num = mod(num * diffs[k][i]);
      }
      ans ^= static_cast<int>(num);
    }

    return ans;
  }
};

// Difference Array
// O(sqrt(n)q + sqrt(n)n) Time, O(n) Space
//
// Reuse difference array
class Solution3 {
  constexpr static int64_t modulo = 1e9 + 7;

  int64_t mod(int64_t x) {  //
    return x % modulo;
  }

  int64_t pow(int64_t x, int p) {  //
    int64_t res = 1;
    while (p > 0) {
      if (p % 2) res = mod(res * x);
      x = mod(x * x);
      p >>= 1;
    }
    return res;
  }

  int64_t inv(int64_t x) {  //
    return pow(x, modulo - 2);
  }

  struct DiffQuery {
    int l, r;
    int64_t v;
  };

 public:
  int xorAfterQueries(vector<int>& nums, const vector<vector<int>>& queries) {
    const int n = nums.size();
    const int m = sqrt(n);

    // Query groups
    auto queryGroups = vector<vector<DiffQuery>>(m);

    // Queries
    for (const auto& query : queries) {
      const int l = query[0], r = query[1], k = query[2];
      const int64_t v = query[3];

      if (k >= m) {
        for (int i = l; i <= r; i += k) {
          nums[i] = (nums[i] * v) % modulo;
        }
      } else {
        int r2 = ((r - l) / k + 1) * k + l;  // real ending
        queryGroups[k].push_back(DiffQuery{l, r2, v});
      }
    }

    // Process difference array
    auto diffs = vector<int64_t>(n + m);
    for (int k = 1; k < m; ++k) {
      if (queryGroups[k].empty()) continue;

      // Reset diff array
      fill(diffs.begin(), diffs.end(), 1);

      // Fill diff array
      for (const auto [l, r, v] : queryGroups[k]) {
        diffs[l] = mod(diffs[l] * v);
        diffs[r] = mod(diffs[r] * inv(v));
      }

      // Aggregate diff array
      for (int i = k; i < n; ++i) {
        diffs[i] = mod(diffs[i] * diffs[i - k]);
      }

      // Apply diff array
      for (int i = 0; i < n; ++i) {
        nums[i] = mod(nums[i] * diffs[i]);
      }
    }

    // XOR
    int ans = 0;
    for (const int num : nums) {
      ans ^= num;
    }

    return ans;
  }
};
