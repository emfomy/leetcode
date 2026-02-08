// Source: https://leetcode.com/problems/balanced-binary-tree
// Title: Balanced Binary Tree
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary tree, determine if it is **height-balanced**.
//
// A **height-balanced** binary tree is a binary tree in which the depth of the two subtrees of every node never differs by more than one.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/10/06/balance_1.jpg
//
// ```
// **Input:** root = [3,9,20,null,null,15,7]
// **Output:** true
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/10/06/balance_2.jpg
//
// ```
// **Input:** root = [1,2,2,3,3,null,null,4,4]
// **Output:** false
// ```
//
// **Example 3:**
//
// ```
// **Input:** root = []
// **Output:** true
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 5000]`.
// - `-10^4 <= Node.val <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <utility>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Recursion
class Solution {
 private:
  // Get the depth of current node, and validate if the node is height-balanced.
  pair<int, bool> getDepthAndValidate(TreeNode *root) {
    if (root == nullptr) return {0, true};

    // Check left child
    auto [leftDepth, leftOk] = getDepthAndValidate(root->left);
    if (!leftOk) return {0, false};

    // Check right child
    auto [rightDepth, rightOk] = getDepthAndValidate(root->right);
    if (!rightOk) return {0, false};

    // Check balance
    if (abs(rightDepth - leftDepth) > 1) return {0, false};

    return {max(leftDepth, rightDepth) + 1, true};
  }

 public:
  bool isBalanced(TreeNode *root) {
    auto [_, ok] = getDepthAndValidate(root);
    return ok;
  }
};
