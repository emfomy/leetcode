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
  bool isValidBST(TreeNode *root, optional<int> minVal = nullopt, optional<int> maxVal = nullopt) {
    if (root == nullptr) return true;

    // Check root
    if (minVal && minVal >= root->val) return false;
    if (maxVal && maxVal <= root->val) return false;

    // Check children
    return isValidBST(root->left, minVal, root->val) && isValidBST(root->right, root->val, maxVal);
  }
};

// Iteration + Stack
//
// Use pre-order traversal.
class Solution2 {
  struct State {
    TreeNode *root;
    optional<int> minVal;
    optional<int> maxVal;
  };

 public:
  bool isValidBST(TreeNode *root) {
    if (!root) return true;

    // Traversal
    auto st = stack<State>();
    st.push(State{root, nullopt, nullopt});
    while (!st.empty()) {
      auto [node, minVal, maxVal] = st.top();
      st.pop();

      // Check node
      if (minVal && *minVal >= node->val) return false;
      if (maxVal && *maxVal <= node->val) return false;

      // Push child
      if (node->left) st.push(State{node->left, minVal, node->val});
      if (node->right) st.push(State{node->right, node->val, maxVal});
    }

    return true;
  }
};

// Iteration + Stack
//
// Use in-order traversal.
// Compare with previous value.
class Solution3 {
  struct State {
    TreeNode *root;
    bool seen;
  };

 public:
  bool isValidBST(TreeNode *root) {
    // Traversal
    optional<int> prevVal = nullopt;
    auto st = stack<State>();
    st.push(State{root, false});
    while (!st.empty()) {
      auto [node, seen] = st.top();
      st.pop();

      if (!node) continue;

      if (!seen) {
        st.push(State{node->right, false});
        st.push(State{node, true});
        st.push(State{node->left, false});
        continue;
      }

      if (prevVal && *prevVal >= node->val) return false;
      prevVal = node->val;
    }

    return true;
  }
};
