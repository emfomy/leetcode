// Source: https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii
// Title: Subarrays Distinct Element Sum of Squares II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed **integer array `nums`.
//
// The **distinct count** of a subarray of `nums` is defined as:
//
// - Let `nums[i..j]` be a subarray of `nums` consisting of all the indices from `i` to `j` such that `0 <= i <= j < nums.length`. Then the number of distinct values in `nums[i..j]` is called the distinct count of `nums[i..j]`.
//
// Return the sum of the **squares** of **distinct counts** of all subarrays of `nums`.
//
// Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// A subarray is a contiguous **non-empty** sequence of elements within an array.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,1]
// Output: 15
// Explanation: Six possible subarrays are:
// [1]: 1 distinct value
// [2]: 1 distinct value
// [1]: 1 distinct value
// [1,2]: 2 distinct values
// [2,1]: 2 distinct values
// [1,2,1]: 2 distinct values
// The sum of the squares of the distinct counts in all subarrays is equal to 1^2 + 1^2 + 1^2 + 2^2 + 2^2 + 2^2 = 15.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,2]
// Output: 3
// Explanation: Three possible subarrays are:
// [2]: 1 distinct value
// [2]: 1 distinct value
// [2,2]: 1 distinct value
// The sum of the squares of the distinct counts in all subarrays is equal to 1^2 + 1^2 + 1^2 = 3.```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Hash Set, TLE
class Solution {
  static constexpr int modulo = 1e9 + 7;

 public:
  int sumCounts(const vector<int>& nums) {
    const int n = nums.size();

    int sum = 0;
    for (int i = 0; i < n; ++i) {
      auto numSet = unordered_set<int>();
      numSet.reserve(n);
      for (int j = i; j < n; ++j) {
        numSet.insert(nums[j]);
        int count = (numSet.size() * numSet.size()) % modulo;
        sum = (sum + count) % modulo;
      }
    }

    return sum;
  }
};

// Hash Map, TLE
//
// Say there is an subarray with x distinct elements.
// After adding an extra element, then distinct count becomes (x+1).
// The increase of its square is (x+1)^2 - x^2 = 2x+1.
//
// The main idea is to scan the index i from left to right,
// and compute the square value of all subarrays end at i.
//
// We use a hash map to store the last index of each value.
// Say we reach the element `a` at index j, assume that its previous position is i.
// All subarrays starts after i will increase by one, and the others won't change.
// After updating the values, we update the sum using above math property.
class Solution2 {
  static constexpr int modulo = 1e9 + 7;

 public:
  int sumCounts(const vector<int>& nums) {
    const int n = nums.size();

    auto prevMap = unordered_map<int, int>();  // previous index after the same number
    prevMap.reserve(n);

    auto scores = vector<int>(n);  // subarray start at i
    int squares = 0;               // sum of squares
    int sum = 0;                   // total sum
    for (int curr = 0; curr < n; ++curr) {
      int num = nums[curr];
      int prev = prevMap[num];
      prevMap[num] = curr + 1;

      // Add 1 for [prev, curr]
      for (int i = prev; i <= curr; ++i) {
        squares += 2 * scores[i] + 1;
        squares %= modulo;
        ++scores[i];  // at most 10^5, less than modulo
      }

      sum += squares;
      sum %= modulo;
    }

    return sum;
  }
};

// Hash Map + Fenwick Tree (BIT)
//
// We need to range update and range sum for the score array.
// More precisely:
// range update for [i, j] by adding one;
// range sum for [i, j].
//
// However, BIT can only do single update.
// Therefore we store the diff instead.
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
class Solution3 {
  static constexpr int64_t modulo = 1e9 + 7;

  class FenwickTree {
    int n;

    // tree[i] = sum of range [i-lowbit(i), i); length is lowbit(i)
    vector<int64_t> tree1;  // D[t]
    vector<int64_t> tree2;  // t*D[t]

   private:
    // Update: O(logN); nums[idx] += delta
    void update(vector<int64_t>& tree, int idx, int64_t delta) {
      // start at x+1 since x in [0, x+1)
      for (int i = idx + 1; i <= n; i += (i & -i)) {
        tree[i] += delta;
      }
    }

    // Query: O(logN); Sum of [0, r)
    int64_t query(const vector<int64_t>& tree, int r) const {
      int64_t sum = 0;
      for (int i = r; i >= 1; i -= (i & -i)) {
        sum += tree[i];
      }
      return sum;
    }

   public:
    FenwickTree(int n) : n(n), tree1(n + 1, 0), tree2(n + 1, 0) {}

    // Range Update: O(logN); [l, r) += delta
    void update(int l, int r, int64_t delta) {
      if (l >= r) return;
      update(tree1, l, delta);
      update(tree1, r, -delta);
      update(tree2, l, l * delta);
      update(tree2, r, -r * delta);
    }

    // Query: O(logN); Sum of [0, r)
    int64_t query(int r) const {  //
      return r * query(tree1, r) - query(tree2, r);
    }

    // Range Query: O(logN); Sum of [l, r)
    int64_t query(int l, int r) const {
      if (l >= r) return 0;
      return query(r) - query(l);
    }
  };

 public:
  int sumCounts(const vector<int>& nums) {
    const int n = nums.size();

    auto prevMap = unordered_map<int, int>();  // previous index after the same number
    prevMap.reserve(n);

    auto tree = FenwickTree(n);

    int64_t squares = 0;  // sum of squares
    int64_t sum = 0;      // total sum
    for (int curr = 0; curr < n; ++curr) {
      int num = nums[curr];
      int prev = prevMap[num];
      prevMap[num] = curr + 1;

      // Update squares
      squares += 2 * tree.query(prev, curr + 1) + (curr - prev + 1);

      // Add 1 for [prev, curr]
      tree.update(prev, curr + 1, 1);

      // Update sum
      sum += squares;
      sum %= modulo;
    }

    return sum;
  }
};
