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

#include <vector>

using namespace std;

// Segment Tree
class NumArray {
  int n;
  vector<int> tree;  // parent i -> children 2i & 2i+1

 public:
  NumArray(const vector<int>& nums) {
    n = nums.size();
    tree.resize(2 * n);

    // build
    for (int i = 0; i < n; ++i) tree[i + n] = nums[i];  // Leaves
    for (int i = n - 1; i > 0; --i) tree[i] = tree[2 * i] + tree[2 * i + 1];
  }

  // Set data[i] = val
  void update(int i, int val) {
    // Leaf
    i += n;
    tree[i] = val;

    // Push up
    for (i /= 2; i > 0; i /= 2) {
      tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
  }

  // Sum of [l, r]
  int sumRange(int l, int r) {
    int sum = 0;
    ++r;  // convert ti [l, r)
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) sum += tree[l++];
      if (r & 1) sum += tree[--r];
    }
    return sum;
  }
};

// Fenwick Tree
class NumArray2 {
  int n;
  vector<int>& data;
  vector<int> tree;  // tree[i] = sum of [i-lowbit(i), i)

 public:
  NumArray2(vector<int>& nums) : data(nums) {
    n = nums.size();
    tree.assign(n + 1, 0);

    // build
    for (int i = 0; i < n; ++i) tree[i + 1] = nums[i];
    for (int i = 1; i <= n; ++i) {
      int p = i + (i & -i);
      if (p <= n) tree[p] += tree[i];
    }
  }

  // Set data[i] = val
  void update(int idx, int val) {
    const int delta = val - data[idx];
    data[idx] = val;

    for (int i = idx + 1; i <= n; i += (i & -i)) {  // start from [?, idx+1)
      tree[i] += delta;
    }
  }

  // Sum of [0, r]
  int sumRange(int r) {
    int sum = 0;
    for (int i = r + 1; i > 0; i -= (i & -i)) {  // start from [?, r+1)
      sum += tree[i];
    }
    return sum;
  }

  // Sum of [l, r]
  int sumRange(int l, int r) {  //
    return sumRange(r) - sumRange(l - 1);
  }
};
