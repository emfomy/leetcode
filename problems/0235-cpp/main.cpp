// Source: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree
// Title: Lowest Common Ancestor of a Binary Search Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.
//
// According to the **definition of LCA on Wikipedia** (https://en.wikipedia.org/wiki/Lowest_common_ancestor): “The lowest common ancestor is defined between two nodes `p` and `q` as the lowest node in `T` that has both `p` and `q` as descendants (where we allow **a node to be a descendant of itself**).”
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/12/14/binarysearchtree_improved.png
//
// ```
// Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
// Output: 6
// Explanation: The LCA of nodes 2 and 8 is 6.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2018/12/14/binarysearchtree_improved.png
//
// ```
// Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
// Output: 2
// Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
// ```
//
// **Example 3:**
//
// ```
// Input: root = [2,1], p = 2, q = 1
// Output: 2
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[2, 10^5]`.
// - `-10^9 <= Node.val <= 10^9`
// - All `Node.val` are **unique**.
// - `p != q`
// - `p` and `q` will exist in the BST.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <utility>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// Binary Search
class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val > q->val) swap(p, q);
    return dfs(root, p->val, q->val);
  }

 private:
  TreeNode* dfs(TreeNode* root, int pVal, int qVal) {
    if (!root) return nullptr;

    // Traverse
    if (qVal < root->val) return dfs(root->left, pVal, qVal);
    if (root->val < pVal) return dfs(root->right, pVal, qVal);
    return root;
  }
};
