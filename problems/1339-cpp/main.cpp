// Source: https://leetcode.com/problems/maximum-product-of-splitted-binary-tree
// Title: Maximum Product of Splitted Binary Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, split the binary tree into two subtrees by removing one edge such that the product of the sums of the subtrees is maximized.
//
// Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it **modulo** `10^9 + 7`.
//
// **Note** that you need to maximize the answer before taking the mod and not after taking it.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/01/21/sample_1_1699.png
//
// ```
// Input: root = [1,2,3,4,5,6]
// Output: 110
// Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/01/21/sample_2_1699.png
//
// ```
// Input: root = [1,null,2,3,4,null,null,5,6]
// Output: 90
// Explanation: Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[2, 5 * 10^4]`.
// - `1 <= Node.val <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// DFS, Two-Pass
//
// First loop through all node and compute sum of each subtree.
// Next loop again and compute the products.
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

 public:
  int maxProduct(TreeNode *root) {
    auto ans = int64_t(-1);
    auto sum = dfsSum(root);
    dfsProd(root, sum, ans);
    return ans % modulo;
  }

  // DFS, store subtree sum into val
  int dfsSum(TreeNode *node) {
    if (node == nullptr) return 0;
    node->val += dfsSum(node->left) + dfsSum(node->right);
    return node->val;
  }

  // DFS, find maximum product
  void dfsProd(TreeNode *node, int totalSum, int64_t &ans) {
    if (node == nullptr) return;
    ans = max(ans, int64_t(node->val) * int64_t(totalSum - node->val));
    dfsProd(node->left, totalSum, ans);
    dfsProd(node->right, totalSum, ans);
  }
};
