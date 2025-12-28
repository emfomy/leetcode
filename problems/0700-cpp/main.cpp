// Source: https://leetcode.com/problems/search-in-a-binary-search-tree
// Title: Search in a Binary Search Tree
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the `root` of a binary search tree (BST) and an integer `val`.
//
// Find the node in the BST that the node's value equals `val` and return the subtree rooted with that node. If such a node does not exist, return `null`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/12/tree1.jpg
//
// ```
// Input: root = [4,2,7,1,3], val = 2
// Output: [2,1,3]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/01/12/tree2.jpg
//
// ```
// Input: root = [4,2,7,1,3], val = 5
// Output: []
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 5000]`.
// - `1 <= Node.val <= 10^7`
// - `root` is a binary search tree.
// - `1 <= val <= 10^7`
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

// Recursion
class Solution {
 public:
  TreeNode *searchBST(TreeNode *root, int val) {
    if (root == nullptr) return nullptr;

    if (val == root->val) return root;

    if (val < root->val) {
      return searchBST(root->left, val);
    } else {
      return searchBST(root->right, val);
    }
  }
};

// Loop
class Solution2 {
 public:
  TreeNode *searchBST(TreeNode *root, int val) {
    while (root != nullptr && root->val != val) {
      if (root->val > val) {
        root = root->left;
      } else {
        root = root->right;
      }
    }
    return root;
  }
};
