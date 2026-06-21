// Source: https://leetcode.com/problems/maximum-total-subarray-value-ii
// Title: Maximum Total Subarray Value II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n` and an integer `k`.
//
// You must select **exactly** `k` **distinct** non-empty <button>subarrays</button> `nums[l..r]` of `nums`. Subarrays may overlap, but the exact same subarray (same `l` and `r`) **cannot** be chosen more than once.
//
// The **value** of a subarray `nums[l..r]` is defined as: `max(nums[l..r]) - min(nums[l..r])`.
//
// The **total value** is the sum of the **values** of all chosen subarrays.
//
// Return the **maximum** possible total value you can achieve.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,2], k = 2
// Output: 4
// Explanation:
// One optimal approach is:
// - Choose `nums[0..1] = [1, 3]`. The maximum is 3 and the minimum is 1, giving a value of `3 - 1 = 2`.
// - Choose `nums[0..2] = [1, 3, 2]`. The maximum is still 3 and the minimum is still 1, so the value is also `3 - 1 = 2`.
// Adding these gives `2 + 2 = 4`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [4,2,5,1], k = 3
// Output: 12
// Explanation:
// One optimal approach is:
// - Choose `nums[0..3] = [4, 2, 5, 1]`. The maximum is 5 and the minimum is 1, giving a value of `5 - 1 = 4`.
// - Choose `nums[1..3] = [2, 5, 1]`. The maximum is 5 and the minimum is 1, so the value is also `4`.
// - Choose `nums[2..3] = [5, 1]`. The maximum is 5 and the minimum is 1, so the value is again `4`.
// Adding these gives `4 + 4 + 4 = 12`.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 5 * 10^4`
// - `0 <= nums[i] <= 10^9`
// - `1 <= k <= min(10^5, n * (n + 1) / 2)`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

// Brute-Force + Sliding Window + Heap (TLE)
//
// Loop for all possible subarray.
// Use sliding window to track the max & min value,
// and put the value into a heap (only keep top k).
class Solution {
  using Heap = priority_queue<int, vector<int>, greater<>>;  // min-heap

 public:
  long long maxTotalValue(const vector<int>& nums, int k) {
    const int n = nums.size();

    // Loop
    Heap heap;
    for (int i = 0; i < n; ++i) {
      int maxVal = INT_MIN, minVal = INT_MAX;
      for (int j = i; j < n; ++j) {
        maxVal = max(maxVal, nums[j]);
        minVal = min(minVal, nums[j]);
        heap.push(maxVal - minVal);
        if (heap.size() > k) heap.pop();
      }
    }

    // Total
    long long total = 0;
    while (!heap.empty()) {
      total += heap.top();
      heap.pop();
    }

    return total;
  }
};

// Sparse Table + Heap
//
// The longer the subarray is, the larger the value is.
// For each l, fix corresponding r at the end.
// Use a heap to store these (l, r) pairs.
//
// Find the largest k pairs.
class Solution2 {
  class SparseTable {
    int n;
    vector<vector<int>> maxs;  // table[i][j] = max of [i, i+2^j)
    vector<vector<int>> mins;  // table[i][j] = min of [i, i+2^j)
    vector<int> logs;          // precompute logs

   public:
    SparseTable(const vector<int>& nums) {
      n = nums.size();
      int logn = bit_width(size_t(n));  // floor(log(n)) + 1

      maxs.assign(n, vector<int>(logn));
      mins.assign(n, vector<int>(logn));
      logs.assign(n + 1, 0);

      // Precompute logs (floor value)
      for (int i = 2; i <= n; ++i) {
        logs[i] = logs[i / 2] + 1;
      }

      // Initialize table layer 0
      for (int i = 0; i < n; ++i) {
        maxs[i][0] = nums[i];
        mins[i][0] = nums[i];
      }

      // Fill the table
      for (int j = 1; j < logn; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
          maxs[i][j] = max(maxs[i][j - 1], maxs[i + (1 << (j - 1))][j - 1]);
          mins[i][j] = min(mins[i][j - 1], mins[i + (1 << (j - 1))][j - 1]);
        }
      }
    }

    // Find "max-min" of [l, r)
    int query(int l, int r) {
      int j = logs[r - l];
      int maxVal = max(maxs[l][j], maxs[r - (1 << j)][j]);
      int minVal = min(mins[l][j], mins[r - (1 << j)][j]);
      return maxVal - minVal;
    }
  };

  using HeapData = tuple<int, int, int>;  // value, l, r

  using Heap = priority_queue<HeapData, vector<HeapData>, less<>>;  // max-heap

 public:
  long long maxTotalValue(const vector<int>& nums, int k) {
    const int n = nums.size();

    // Sparse table
    auto table = SparseTable(nums);

    // Init heap
    Heap heap;
    for (int l = 0; l < n; ++l) {
      heap.push({table.query(l, n), l, n});
    }

    // Total
    long long total = 0;
    for (; k > 0; --k) {
      auto [value, l, r] = heap.top();
      heap.pop();

      total += value;

      // ignore empty range
      if (l != --r) {
        heap.push({table.query(l, r), l, r});
      }
    }

    return total;
  }
};

// Segment Tree + Heap
//
// Use segment tree to store the max and min.
class Solution3 {
  class SegmentTree {
    int n;
    vector<int> maxs;  // parent i -> child 2i & 2i+1
    vector<int> mins;  // parent i -> child 2i & 2i+1

   public:
    // Build: O(N)
    SegmentTree(const vector<int>& nums) {
      n = nums.size();

      // only need 2n for iteration version
      maxs.resize(2 * n);
      mins.resize(2 * n);

      for (int i = 0; i < n; ++i) {  // leaves
        maxs[i + n] = nums[i];
        mins[i + n] = nums[i];
      }
      for (int i = n - 1; i >= 1; --i) {
        maxs[i] = max(maxs[2 * i], maxs[2 * i + 1]);
        mins[i] = min(mins[2 * i], mins[2 * i + 1]);
      }
    }

    // Query: O(logN); "max-min" in [l, r)
    int query(int l, int r) const {
      int maxVal = INT_MIN, minVal = INT_MAX;
      for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l & 1) {  // l is odd, should add tree[l]; then move l
          maxVal = max(maxVal, maxs[l]);
          minVal = min(minVal, mins[l]);
          ++l;
        }
        if (r & 1) {  // r is odd, should add tree[r-1]; then move r
          --r;
          maxVal = max(maxVal, maxs[r]);
          minVal = min(minVal, mins[r]);
        }
      }
      return maxVal - minVal;
    }
  };

  using HeapData = tuple<int, int, int>;  // value, l, r

  using Heap = priority_queue<HeapData, vector<HeapData>, less<>>;  // max-heap

 public:
  long long maxTotalValue(const vector<int>& nums, int k) {
    const int n = nums.size();

    // Sparse table
    auto tree = SegmentTree(nums);

    // Init heap
    Heap heap;
    for (int l = 0; l < n; ++l) {
      heap.push({tree.query(l, n), l, n});
    }

    // Total
    long long total = 0;
    for (; k > 0; --k) {
      auto [value, l, r] = heap.top();
      heap.pop();

      total += value;

      // ignore empty range
      if (l != --r) {
        heap.push({tree.query(l, r), l, r});
      }
    }

    return total;
  }
};
