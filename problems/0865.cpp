// Source: https://leetcode.com/problems/car-fleet
// Title: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, the depth of each node is **the shortest distance to the root**.
//
// Return the smallest subtree such that it contains **all the deepest nodes** in the original tree.
//
// A node is called **the deepest** if it has the largest depth possible among any node in the entire tree.
//
// The **subtree** of a node is a tree consisting of that node, plus the set of all descendants of that node.
//
// **Example 1:**
// https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/01/sketch1.png
//
// ```
// Input: root = [3,5,1,6,2,0,8,null,null,7,4]
// Output: [2,7,4]
// Explanation: We return the node with value 2, colored in yellow in the diagram.
// The nodes coloured in blue are the deepest nodes of the tree.
// Notice that nodes 5, 3 and 2 contain the deepest nodes in the tree but node 2 is the smallest subtree among them, so we return it.
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1]
// Output: [1]
// Explanation: The root is the deepest node in the tree.
// ```
//
// **Example 3:**
//
// ```
// Input: root = [0,1,3,null,2]
// Output: [2]
// Explanation: The deepest node in the tree is 2, the valid subtrees are the subtrees of nodes 2, 1 and 0 but the subtree of node 2 is the smallest.
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree will be in the range `[1, 500]`.
// - `0 <= Node.val <= 500`
// - The values of the nodes in the tree are **unique**.
//
// **Note:** This question is the same as 1123: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// DFS
//
// For each node, check the depth of both child.
// If both are the same, then returns the current node (since both contains the deepest).
// If not, returns the deeper child.
class Solution {
 public:
  TreeNode *subtreeWithAllDeepest(TreeNode *root) {
    auto [ans, _] = dfs(root);
    return ans;
  }

  pair<TreeNode *, int> dfs(TreeNode *node) {
    if (node == nullptr) return {node, 0};

    auto [leftNode, leftDepth] = dfs(node->left);
    auto [rightNode, rightDepth] = dfs(node->right);

    if (leftDepth > rightDepth) return {leftNode, leftDepth + 1};
    if (leftDepth < rightDepth) return {rightNode, rightDepth + 1};

    return {node, leftDepth + 1};
  }
};
