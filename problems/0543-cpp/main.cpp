// Source: https://leetcode.com/problems/diameter-of-binary-tree
// Title: Diameter of Binary Tree
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return the length of the **diameter** of the tree.
//
// The **diameter** of a binary tree is the **length** of the longest path between any two nodes in a tree. This path may or may not pass through the `root`.
//
// The **length** of a path between two nodes is represented by the number of edges between them.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/06/diamtree.jpg
//
// ```
// Input: root = [1,2,3,4,5]
// Output: 3
// Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1,2]
// Output: 1
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 10^4]`.
// - `-100 <= Node.val <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// DFS
class Solution {
 public:
  int diameterOfBinaryTree(TreeNode* root) {
    auto diameter = 0;
    dfs(root, diameter);
    return diameter;
  }

 private:
  int dfs(TreeNode* node, int& diameter) {  // depth
    if (node == nullptr) return 0;

    auto leftDepth = dfs(node->left, diameter);
    auto rightDepth = dfs(node->right, diameter);

    diameter = max(diameter, leftDepth + rightDepth);

    return max(leftDepth, rightDepth) + 1;
  }
};
