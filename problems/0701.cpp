// Source: https://leetcode.com/problems/insert-into-a-binary-search-tree
// Title: Insert into a Binary Search Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the `root` node of a binary search tree (BST) and a `value` to insert into the tree. Return the root node of the BST after the insertion. It is **guaranteed** that the new value does not exist in the original BST.
//
// **Notice**that there may exist multiple valid ways for theinsertion, as long as the tree remains a BST after insertion. You can return **any of them**.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/10/05/insertbst.jpg
//
// ```
// Input: root = [4,2,7,1,3], val = 5
// Output: [4,2,7,1,3,5]
// Explanation: Another accepted tree is:
// https://assets.leetcode.com/uploads/2020/10/05/bst.jpg
// ```
//
// **Example 2:**
//
// ```
// Input: root = [40,20,60,10,30,50,70], val = 25
// Output: [40,20,60,10,30,50,70,null,null,25]
// ```
//
// **Example 3:**
//
// ```
// Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
// Output: [4,2,7,1,3,5]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree will be in the range `[0,10^4]`.
// - `-10^8 <= Node.val <= 10^8`
// - All the values `Node.val` are **unique**.
// - `-10^8 <= val <= 10^8`
// - It's **guaranteed** that `val` does not exist in the original BST.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
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
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    if (!root) return new TreeNode(val);

    if (val < root->val) {
      root->left = insertIntoBST(root->left, val);
    } else {
      root->right = insertIntoBST(root->right, val);
    }

    return root;
  }
};

// Iteration
class Solution2 {
 public:
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    if (!root) return new TreeNode(val);

    TreeNode *node = root;
    while (node) {
      if (val < node->val) {
        if (!node->left) {
          node->left = new TreeNode(val);
          break;
        }
        node = node->left;
      } else {
        if (!node->right) {
          node->right = new TreeNode(val);
          break;
        }
        node = node->right;
      }
    }

    return root;
  }
};

// Iteration, Double Pointer
class Solution3 {
 public:
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    // Find
    TreeNode **nodePtr = &root;
    while (*nodePtr) {
      if (val < (*nodePtr)->val) {
        nodePtr = &((*nodePtr)->left);
      } else {
        nodePtr = &((*nodePtr)->right);
      }
    }

    // Insert
    *nodePtr = new TreeNode(val);

    return root;
  }
};

// Iteration, Reference Wrapper
class Solution4 {
  using NodeRef = reference_wrapper<TreeNode *>;

 public:
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    // Find
    NodeRef nodeRef = root;
    while (nodeRef.get()) {
      if (val < nodeRef.get()->val) {
        nodeRef = nodeRef.get()->left;
      } else {
        nodeRef = nodeRef.get()->right;
      }
    }

    // Insert
    nodeRef.get() = new TreeNode(val);

    return root;
  }
};
