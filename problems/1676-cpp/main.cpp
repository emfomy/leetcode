// Source: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iv
// Title: Lowest Common Ancestor of a Binary Tree IV
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree and an array of `TreeNode` objects `nodes`, return the lowest common ancestor (LCA) of **all the nodes** in `nodes`. All the nodes will exist in the tree, and all values of the tree's nodes are **unique**.
//
// Extending the **definition of LCA on Wikipedia** (https://en.wikipedia.org/wiki/Lowest_common_ancestor): "The lowest common ancestor of `n` nodes `p_1`, `p_2`, ..., `p_n` in a binary tree `T` is the lowest node that has every `p_i` as a **descendant** (where we allow **a node to be a descendant of itself**) for every valid `i`". A **descendant** of a node `x` is a node `y` that is on the path from node `x` to some leaf node.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/12/14/binarytree.png
//
// ```
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [4,7]
// Output: 2
// Explanation: The lowest common ancestor of nodes 4 and 7 is node 2.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2018/12/14/binarytree.png
//
// ```
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [1]
// Output: 1
// Explanation: The lowest common ancestor of a single node is the node itself.
//
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2018/12/14/binarytree.png
//
// ```
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [7,6,2,4]
// Output: 5
// Explanation: The lowest common ancestor of the nodes 7, 6, 2, and 4 is node 5.
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 10^4]`.
// - `-10^9 <= Node.val <= 10^9`
// - All `Node.val` are **unique**.
// - All `nodes[i]` will exist in the tree.
// - All `nodes[i]` are distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_set>

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
  TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*>& nodes) {
    auto nodeSet = unordered_set<TreeNode*>(nodes.cbegin(), nodes.cend());

    return dfs(root, nodeSet);
  };

 private:
  TreeNode* dfs(TreeNode* root, unordered_set<TreeNode*>& nodeSet) {
    if (!root) return nullptr;
    if (nodeSet.contains(root)) return root;

    // Traverse
    auto left = dfs(root->left, nodeSet);
    auto right = dfs(root->right, nodeSet);

    // Found in both child
    if (left && right) return root;

    return left ? left : right;
  }
};
