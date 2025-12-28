// Source: https://leetcode.com/problems/validate-binary-search-tree
// Title: Validate Binary Search Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, determine if it is a valid binary search tree (BST).
//
// A **valid BST** is defined as follows:
//
// - The left <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:r1v:" data-state="closed" class="">subtree</button> of a node contains only nodes with keys**strictly less than** the node's key.
// - The right subtree of a node contains only nodes with keys **strictly greater than** the node's key.
// - Both the left and right subtrees must also be binary search trees.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/12/01/tree1.jpg
//
// ```
// Input: root = [2,1,3]
// Output: true
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/12/01/tree2.jpg
//
// ```
// Input: root = [5,1,4,null,null,3,6]
// Output: false
// Explanation: The root node's value is 5 but its right child's value is 4.
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 10^4]`.
// - `-2^31 <= Node.val <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <stack>

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
  bool isValidBST(TreeNode *root, TreeNode *minNode = nullptr, TreeNode *maxNode = nullptr) {
    if (root == nullptr) return true;

    // Check current node
    if (minNode && root->val <= minNode->val) return false;
    if (maxNode && root->val >= maxNode->val) return false;

    // Check child nodes
    return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
  }
};

// Stack + State
class Solution2 {
 public:
  bool isValidBST(TreeNode *root) {
    // Prepare
    auto st = stack<pair<TreeNode *, bool>>();  // node, seen
    st.push({root, false});

    // Loop
    auto prev = INT64_MIN;
    while (!st.empty()) {
      auto [node, seen] = st.top();
      st.pop();

      if (node == nullptr) continue;

      if (seen) {
        if (node->val <= prev) return false;
        prev = node->val;
      } else {
        st.push({node->right, false});
        st.push({node, true});
        st.push({node->left, false});
      }
    }

    return true;
  }
};
