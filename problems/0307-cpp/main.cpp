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

// Segment Tree (Tree)
class NumArray {
  struct Node {
    int val;
    int l, r;  // [l, r]
    Node *left, *right;

    inline int mid() { return l + (r - l) / 2; }
  };

  vector<int>& nums;
  Node* root;

 public:
  NumArray(vector<int>& nums) : nums(nums) {
    int n = nums.size();
    root = _build(nums, 0, n - 1);
  }

  void update(int index, int val) {  //
    _update(root, index, val);
  }

  int sumRange(int left, int right) {  //
    return _query(root, left, right);
  }

 private:
  Node* _build(vector<int>& nums, int l, int r) {
    // Check leaf
    if (l == r) {
      return new Node(nums[l], l, r);
    }

    // DFS
    auto node = new Node(0, l, r);
    auto mid = node->mid();
    node->left = _build(nums, l, mid);
    node->right = _build(nums, mid + 1, r);

    // Root
    node->val = node->left->val + node->right->val;
    return node;
  }

  void _update(Node* node, int index, int val) {
    // Check leaf
    if (node->l == node->r) {
      node->val = val;
      return;
    }

    // DFS
    if (index <= node->mid()) {
      _update(node->left, index, val);
    } else {
      _update(node->right, index, val);
    }

    // Root
    node->val = node->left->val + node->right->val;
  }

  int _query(Node* node, int qL, int qR) {
    // Found node
    if (node->l == qL && node->r == qR) {
      return node->val;
    }

    // DFS
    auto val = 0;
    auto mid = node->mid();
    if (qL <= mid) val += _query(node->left, qL, min(qR, mid));
    if (qR > mid) val += _query(node->right, max(qL, mid + 1), qR);
    return val;
  }
};

// Segment Tree (Array)
class NumArray2 {
  int n;
  vector<int> data;  // 4n length, child of node i are 2i+1 & 2i+2

 public:
  NumArray2(vector<int>& nums) {
    n = nums.size();
    data.resize(4 * n);
    _build(nums, 0, 0, n - 1);
  }

  void update(int index, int val) {  //
    _update(0, 0, n - 1, index, val);
  }

  int sumRange(int left, int right) {  //
    return _query(0, 0, n - 1, left, right);
  }

 private:
  void _build(vector<int>& nums, int id, int l, int r) {
    // Check leaf
    if (l == r) {
      data[id] = nums[l];
      return;
    }

    // DFS
    auto val = 0;
    auto mid = l + (r - l) / 2;
    _build(nums, id * 2 + 1, l, mid);
    _build(nums, id * 2 + 2, mid + 1, r);
    data[id] = data[id * 2 + 1] + data[id * 2 + 2];
  }

  void _update(int id, int l, int r, int index, int val) {
    // Check leaf
    if (l == r) {
      data[id] = val;
      return;
    }

    // DFS
    auto mid = l + (r - l) / 2;
    if (index <= mid) {
      _update(id * 2 + 1, l, mid, index, val);
    } else {
      _update(id * 2 + 2, mid + 1, r, index, val);
    }
    data[id] = data[id * 2 + 1] + data[id * 2 + 2];
  }

  int _query(int id, int l, int r, int qL, int qR) {
    // Found node
    if (l == qL && r == qR) {
      return data[id];
    }

    // DFS
    auto val = 0;
    auto mid = l + (r - l) / 2;
    if (qL <= mid) val += _query(id * 2 + 1, l, mid, qL, min(qR, mid));
    if (qR > mid) val += _query(id * 2 + 2, mid + 1, r, max(qL, mid + 1), qR);
    return val;
  }
};
