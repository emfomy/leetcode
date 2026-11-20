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

// DFS, Two Pass
//
// First use DFS to compute the total sum.
// Next run DFS again and compute the sum of each subtree.
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

 public:
  int maxProduct(const TreeNode *root) {
    int64_t totalSum = dfsSum(root);
    int64_t maxProd = 0;
    dfsProd(root, totalSum, maxProd);
    return maxProd % modulo;
  }

  // Find total sum
  int64_t dfsSum(const TreeNode *root) {
    if (!root) return 0;
    return root->val + dfsSum(root->left) + dfsSum(root->right);
  }

  // Find max product
  int64_t dfsProd(const TreeNode *root, const int64_t totalSum, int64_t &maxProd) {
    if (!root) return 0;
    int64_t sum = root->val +                               //
                  dfsProd(root->left, totalSum, maxProd) +  //
                  dfsProd(root->right, totalSum, maxProd);  //
    maxProd = max(maxProd, sum * (totalSum - sum));
    return sum;
  }
};
