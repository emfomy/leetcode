// Source: https://leetcode.com/problems/range-sum-query-mutable
// Title: Range Sum Query - Mutable
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, handle multiple queries of the following types:
//
// - **Update** the value of an element in `nums`.
// - Calculate the **sum** of the elements of `nums` between indices `left` and `right` **inclusive** where `left <= right`.
//
// Implement the `NumArray` class:
//
// - `NumArray(int[] nums)` Initializes the object with the integer array `nums`.
// - `void update(int index, int val)` **Updates** the value of `nums[index]` to be `val`.
// - `int sumRange(int left, int right)` Returns the **sum** of the elements of `nums` between indices `left` and `right` **inclusive** (i.e. `nums[left] + nums[left + 1] + ... + nums[right]`).
//
// **Example 1:**
//
// ```
// Input:
// ["NumArray", "sumRange", "update", "sumRange"]
// [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
//
// Output:
// [null, 9, null, 8]
//
// Explanation:
// * NumArray numArray = new NumArray([1, 3, 5]);
// * numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
// * numArray.update(1, 2);   // nums = [1, 2, 5]
// * numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 3 * 10^4`
// - `-100 <= nums[i] <= 100`
// - `0 <= index < nums.length`
// - `-100 <= val <= 100`
// - `0 <= left <= right < nums.length`
// - At most `3 * 10^4` calls will be made to `update` and `sumRange`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <vector>

using namespace std;

// Segment Tree
class NumArray {
  int n;
  vector<int> tree;

 public:
  NumArray(vector<int>& nums) {
    n = ssize(nums);
    tree.resize(2 * n);

    // Init data
    for (auto i = 0; i < n; ++i) tree[i + n] = nums[i];                         // leaves
    for (auto i = n - 1; i >= 1; --i) tree[i] = tree[2 * i] + tree[2 * i + 1];  // parents
  }

  // Update nums[idx] = val
  void update(int idx, int val) {
    // Update leaf
    idx += n;
    tree[idx] = val;

    // Update parents
    for (idx /= 2; idx >= 1; idx /= 2) {
      tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }
  }

  int sumRange(int left, int right) {
    ++right;  // [left, right)
    auto sum = 0;
    for (left += n, right += n; left < right; left /= 2, right /= 2) {
      if (left & 1) sum += tree[left++];
      if (right & 1) sum += tree[--right];
    }
    return sum;
  }
};

// Fenwick Tree
class NumArray2 {
  int n;
  vector<int>& nums;
  vector<int> tree;

 public:
  NumArray2(vector<int>& nums) : nums(nums) {
    n = ssize(nums);
    tree.resize(n + 1);  // [i-lowbit(i), i)

    // Init data
    for (auto i = 0; i < n; ++i) tree[i + 1] = nums[i];
    for (auto i = 1; i <= n; ++i) {
      auto parent = i + (i & -i);
      if (parent <= n) tree[parent] += tree[i];
    }
  }

  // Update nums[idx] = val
  void update(int idx, int val) {
    auto delta = val - nums[idx];
    nums[idx] = val;
    for (auto i = idx + 1; i <= n; i += (i & -i)) {
      tree[i] += delta;
    }
  }

  // Query [0, r)
  int query(int r) {
    auto sum = 0;
    for (auto i = r; i > 0; i -= (i & -i)) {
      sum += tree[i];
    }
    return sum;
  }

  int sumRange(int left, int right) {
    ++right;  // [left, right)
    return query(right) - query(left);
  }
};
