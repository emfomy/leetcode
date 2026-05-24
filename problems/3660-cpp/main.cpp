// Source: https://leetcode.com/problems/jump-game-ix
// Title: Jump Game IX
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`.
//
// From any index `i`, you can jump to another index `j` under the following rules:
//
// - Jump to index `j` where `j > i` is allowed only if `nums[j] < nums[i]`.
// - Jump to index `j` where `j < i` is allowed only if `nums[j] > nums[i]`.
//
// For each index `i`, find the **maximum** **value** in `nums` that can be reached by following **any** sequence of valid jumps starting at `i`.
//
// Return an array `ans` where `ans[i]` is the **maximum** **value** reachable starting from index `i`.
//
// **Example 1:**
//
// ```
// Input: nums = [2,1,3]
// Output: [2,2,3]
// Explanation:
// - For `i = 0`: No jump increases the value.
// - For `i = 1`: Jump to `j = 0` as `nums[j] = 2` is greater than `nums[i]`.
// - For `i = 2`: Since `nums[2] = 3` is the maximum value in `nums`, no jump increases the value.
// Thus, `ans = [2, 2, 3]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,3,1]
// Output: [3,3,3]
// Explanation:
// - For `i = 0`: Jump forward to `j = 2` as `nums[j] = 1` is less than `nums[i] = 2`, then from `i = 2` jump to `j = 1` as `nums[j] = 3` is greater than `nums[2]`.
// - For `i = 1`: Since `nums[1] = 3` is the maximum value in `nums`, no jump increases the value.
// - For `i = 2`: Jump to `j = 1` as `nums[j] = 3` is greater than `nums[2] = 1`.
// Thus, `ans = [3, 3, 3]`.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <stack>
#include <vector>

using namespace std;

// Greedy + Union-Find
//
// First make a graph by connecting jumpable path.
// The problem is equal to find the connectivity of the graph.
//
// We compute the prefix max and suffix min of each number
// Denoted as Pre[x] and Suf[x] (include x itself).
//
// Say we have two adjacent number i < j.
// If Pre[i] > Suf[j], then i and j are connected.
class Solution {
  class UnionFind {
    const vector<int>& nums;
    vector<int> parents;

   public:
    UnionFind(const vector<int>& nums) : nums(nums), parents(nums.size()) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    // Merge by its number
    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure nums(x) >= nums(y)
      if (nums[x] < nums[y]) swap(x, y);

      // Merge y into x
      parents[y] = x;
    }
  };

 public:
  vector<int> maxValue(const vector<int>& nums) {
    const int n = nums.size();

    // Prefix max and suffix min
    auto prefixs = vector<int>(n);
    auto suffixs = vector<int>(n);
    prefixs[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      prefixs[i] = max(prefixs[i - 1], nums[i]);
    }
    suffixs[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      suffixs[i] = min(suffixs[i + 1], nums[i]);
    }

    // Connectivity
    auto uf = UnionFind(nums);
    for (int i = 1; i < n; ++i) {
      if (prefixs[i - 1] > suffixs[i]) uf.unite(i - 1, i);
    }

    // Answer
    auto ans = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      ans[i] = nums[uf.find(i)];
    }

    return ans;
  }
};

// Monotonic Stack
//
// We use monotonic stack instead of union-find.
//
// Pick any number x and a connected component to its left.
// If the maximum of that connected component is greater then x,
// then we can merge x into that connected component.
//
// Now focus on how to pick the connected component to merge.
// Say there are two connected A and B. Amax <= Bmax.
// If x < Amax, then we must have x < Bmax,
// meaning that A, B, x can merge into a larger component.
// In other words, x merge the top components into a single large component.
//
// We can track the connected components into a monotonic stack.
// For each new number x, we merge the top components with x if possible.
// If x is larger than the top component, then x is a new component.
class Solution2 {
  struct Comp {       // connected component
    int max;          // max value
    int left, right;  // range
  };

 public:
  vector<int> maxValue(const vector<int>& nums) {
    const int n = nums.size();

    // Loop
    auto st = vector<Comp>();
    for (int i = 0; i < n; ++i) {
      auto comp = Comp{nums[i], i, i};

      while (!st.empty() && st.back().max > nums[i]) {
        comp.max = max(comp.max, st.back().max);
        comp.left = st.back().left;
        st.pop_back();
      }

      st.push_back(comp);
    }

    // Answer
    auto ans = vector<int>(n);
    for (const Comp comp : st) {
      for (int i = comp.left; i <= comp.right; ++i) {
        ans[i] = comp.max;
      }
    }

    return ans;
  }
};
