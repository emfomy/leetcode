// Source: https://leetcode.com/problems/count-complete-tree-nodes
// Title: Count Complete Tree Nodes
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a **complete** binary tree, return the number of the nodes in the tree.
//
// According to **Wikipedia**, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. It can have between `1` and `2^h` nodes inclusive at the last level `h`.
//
// Design an algorithm that runs in less than `O(n)` time complexity.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/14/complete.jpg
//
// ```
// Input: root = [1,2,3,4,5,6]
// Output: 6
// ```
//
// **Example 2:**
//
// ```
// Input: root = []
// Output: 0
// ```
//
// **Example 3:**
//
// ```
// Input: root = [1]
// Output: 1
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 5 * 10^4]`.
// - `0 <= Node.val <= 5 * 10^4`
// - The tree is guaranteed to be **complete**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// O(log^2 n)
//
// For each step, at least one of the child must be full.
// Therefore we only need to treverse one side.
//
// Complexity: say n = 2^k
// log(2^k) + log(2^(k-1)) + ... + log(1)
// = k + k-1 + ... + 1
// = O(k^2) = O(log^2 n)
class Solution {
 public:
  int countNodes(TreeNode *root) {
    auto lh = 0;
    for (auto node = root; node != nullptr; node = node->left) ++lh;

    auto rh = 0;
    for (auto node = root; node != nullptr; node = node->right) ++rh;

    // is full tree
    if (lh == rh) return (1 << lh) - 1;

    return 1 + countNodes(root->left) + countNodes(root->right);
  }
};
