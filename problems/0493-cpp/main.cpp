// Source: https://leetcode.com/problems/reverse-pairs
// Title: Reverse Pairs
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return the number of **reverse pairs** in the array.
//
// A **reverse pair** is a pair `(i, j)` where:
//
// - `0 <= i < j < nums.length` and
// - `nums[i] > 2 * nums[j]`.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,2,3,1]
// Output: 2
// Explanation: The reverse pairs are:
// (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
// (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,4,3,5,1]
// Output: 3
// Explanation: The reverse pairs are:
// (1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
// (2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
// (3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 5 * 10^4`
// - `-2^31 <= nums[i] <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

// Multi-Set
//
// Scan the array. Store the visited numbers in the multi-set.
// For each nums[j], count number greater than 2*nums[j].
class Solution {
 public:
  int reversePairs(vector<int>& nums) {
    auto numSet = multiset<int64_t>();

    auto ans = 0;
    for (auto num : nums) {
      auto it = numSet.upper_bound(int64_t(num) * 2);
      ans += distance(it, numSet.cend());  // O(n), should be improved
      numSet.insert(num);
    }

    return ans;
  }
};

// Fenwick Tree
//
// Scan the array. Store the visited numbers in the tree.
// For each nums[j], count number greater than 2*nums[j].
class Solution2 {
  struct FenwickTree {
    int n;
    vector<int64_t>& xs;  // all possible queries
    vector<int> tree;     // 1-based

    FenwickTree(vector<int64_t>& xs) : xs(xs) {
      n = xs.size();
      tree.resize(n + 1);
    }

    // data[x] += delta
    void update(int64_t x, int delta) {
      // xs[idx-1] < x <= xs[idx]
      auto idx = distance(xs.cbegin(), lower_bound(xs.cbegin(), xs.cend(), x));
      ++idx;  // convert to 1-based
      if (idx > n) return;

      while (idx <= n) {
        tree[idx] += delta;
        idx += idx & (-idx);  // idx += lowbit(idx)
      }
    }

    // count [1, x]
    int query(int64_t x) {
      // xs[idx-1] <= x < xs[idx]
      auto idx = distance(xs.cbegin(), upper_bound(xs.cbegin(), xs.cend(), x));

      auto sum = 0;
      while (idx > 0) {
        sum += tree[idx];
        idx -= idx & (-idx);
      }
      return sum;
    }
  };

 public:
  int reversePairs(vector<int>& nums) {
    int n = nums.size();

    // Find unique numbers
    auto xs = vector<int64_t>();  // all 2nums
    for (int64_t num : nums) xs.push_back(num * 2);
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    // Loop
    auto tree = FenwickTree(xs);
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      int64_t num = nums[i];
      ans += i - tree.query(num * 2);
      tree.update(num, 1);
    }

    return ans;
  }
};

// Fenwick Tree
//
// Scan the array. Store the visited numbers in the tree.
// For each nums[j], count number greater than 2*nums[j].
//
// To avoid overflow, we store the ceil(num/2) in the tree.
class Solution3 {
  struct FenwickTree {
    int n;
    vector<int>& xs;   // all possible queries
    vector<int> tree;  // 1-based

    FenwickTree(vector<int>& xs) : xs(xs) {
      n = xs.size();
      tree.resize(n + 1);
    }

    // data[x] += delta
    void update(int x, int delta) {
      // xs[idx-1] < x <= xs[idx]
      auto idx = distance(xs.cbegin(), lower_bound(xs.cbegin(), xs.cend(), x));
      ++idx;  // convert to 1-based
      if (idx > n) return;

      while (idx <= n) {
        tree[idx] += delta;
        idx += idx & (-idx);  // idx += lowbit(idx)
      }
    }

    // count [1, x]
    int query(int x) {
      // xs[idx-1] <= x < xs[idx]
      auto idx = distance(xs.cbegin(), upper_bound(xs.cbegin(), xs.cend(), x));

      auto sum = 0;
      while (idx > 0) {
        sum += tree[idx];
        idx -= idx & (-idx);
      }
      return sum;
    }
  };

 public:
  int reversePairs(vector<int>& nums) {
    int n = nums.size();

    // Find unique numbers
    auto xs = vector<int>(nums.cbegin(), nums.cend());  // all nums
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    // Loop
    auto tree = FenwickTree(xs);
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      int num = nums[i];
      ans += i - tree.query(num);
      tree.update(ceil(num / 2.0), 1);
    }

    return ans;
  }
};
