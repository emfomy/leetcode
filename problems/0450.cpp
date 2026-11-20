// Source: https://leetcode.com/problems/delete-node-in-a-bst
// Title: Delete Node in a BST
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the **root node reference** (possibly updated) of the BST.
//
// Basically, the deletion can be divided into two stages:
//
// - Search for a node to remove.
// - If the node is found, delete the node.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/09/04/del_node_1.jpg
//
// ```
// Input: root = [5,3,6,2,4,null,7], key = 3
// Output: [5,4,6,2,null,null,7]
// Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
// One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
// Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.
// https://assets.leetcode.com/uploads/2020/09/04/del_node_supp.jpg
// ```
//
// **Example 2:**
//
// ```
// Input: root = [5,3,6,2,4,null,7], key = 0
// Output: [5,3,6,2,4,null,7]
// Explanation: The tree does not contain a node with value = 0.
// ```
//
// **Example 3:**
//
// ```
// Input: root = [], key = 0
// Output: []
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 10^4]`.
// - `-10^5 <= Node.val <= 10^5`
// - Each node has a **unique** value.
// - `root` is a valid binary search tree.
// - `-10^5 <= key <= 10^5`
//
// **Follow up:** Could you solve it with time complexity `O(height of tree)`?
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
//
// First find node to be deleted
//
// If node has no child, just delete it.
// If node has only one child, replace with its child.
// If node has two children:
//   Find the successor (i.e. leftmost of right child).
//   Replace current node's value with successor's, and delete the successor.
class Solution {
 public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    if (!root) return nullptr;

    // Go left
    if (key < root->val) {
      root->left = deleteNode(root->left, key);
      return root;
    }

    // Go right
    if (key > root->val) {
      root->right = deleteNode(root->right, key);
      return root;
    }

    // No child or single left
    if (root->right == nullptr) {
      TreeNode *left = root->left;
      delete root;
      return left;
    }

    // Single right
    if (root->left == nullptr) {
      TreeNode *right = root->right;
      delete root;
      return right;
    }

    // Both child
    TreeNode *successor = root->right;
    while (successor->left) successor = successor->left;
    root->val = successor->val;
    root->right = deleteNode(root->right, successor->val);

    return root;
  }
};

// Iteration, Double Pointer
//
// First find node to be deleted
//
// If node has no child, just delete it.
// If node has only one child, replace with its child.
// If node has two children:
//   Find the successor (i.e. leftmost of right child).
//   Replace current node's value with successor's, and delete the successor.
class Solution2 {
 public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    TreeNode **nodePtr = &root;

    // Find
    while (*nodePtr) {
      // Found
      if (key == (*nodePtr)->val) break;

      // Traverse
      if (key < (*nodePtr)->val) {
        nodePtr = &(*nodePtr)->left;
      } else {
        nodePtr = &(*nodePtr)->right;
      }
    }

    // Not found
    if (*nodePtr == nullptr) return root;

    // Delete
    TreeNode *node = *nodePtr;
    if (node->left && node->right) {  // two child
      TreeNode *successor = node->right;
      while (successor->left) successor = successor->left;

      // Copy value
      node->val = successor->val;

      // Delete successor
      node->right = deleteNode(node->right, successor->val);

      // here we don't delete node
    } else if (node->left) {  // single left
      *nodePtr = node->left;
      delete node;
    } else {  // single right or no child
      *nodePtr = node->right;
      delete node;
    }

    return root;
  }
};

// Iteration, Reference Wrapper
//
// First find node to be deleted
//
// If node has no child, just delete it.
// If node has only one child, replace with its child.
// If node has two children:
//   Find the successor (i.e. leftmost of right child).
//   Replace current node's value with successor's, and delete the successor.
class Solution3 {
  using NodeRef = reference_wrapper<TreeNode *>;

 public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    NodeRef nodeRef = root;

    // Find
    while (nodeRef.get()) {
      // Found
      if (key == nodeRef.get()->val) break;

      // Traverse
      if (key < nodeRef.get()->val) {
        nodeRef = nodeRef.get()->left;
      } else {
        nodeRef = nodeRef.get()->right;
      }
    }

    // Not found
    if (nodeRef.get() == nullptr) return root;

    // Delete
    TreeNode *node = nodeRef.get();
    if (node->left && node->right) {  // two child
      TreeNode *successor = node->right;
      while (successor->left) successor = successor->left;

      // Copy value
      node->val = successor->val;

      // Delete successor
      node->right = deleteNode(node->right, successor->val);

      // here we don't delete node
    } else if (node->left) {  // single left
      nodeRef.get() = node->left;
      delete node;
    } else {  // single right or no child
      nodeRef.get() = node->right;
      delete node;
    }

    return root;
  }
};

// Iteration, Reference Wrapper, Avoid modify value
//
// First find node to be deleted
//
// If node has no child, just delete it.
// If node has only one child, replace with its child.
// If node has two children:
//   Find the successor (i.e. leftmost of right child).
//   Replace successor with its right child.
//   Replace current node with successor (connect old left/right child to it).
class Solution4 {
  using NodeRef = reference_wrapper<TreeNode *>;

 public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    NodeRef nodeRef = root;

    // Find
    while (nodeRef.get()) {
      // Found
      if (key == nodeRef.get()->val) break;

      // Traverse
      if (key < nodeRef.get()->val) {
        nodeRef = nodeRef.get()->left;
      } else {
        nodeRef = nodeRef.get()->right;
      }
    }

    // Not found
    if (nodeRef.get() == nullptr) return root;

    // Backup for delete
    const TreeNode *toDelete = nodeRef.get();

    // Remove
    if (toDelete->left && toDelete->right) {  // Both child
      // Find successor
      NodeRef successorRef = nodeRef.get()->right;
      while (successorRef.get()->left) {
        successorRef = successorRef.get()->left;
      }
      TreeNode *successor = successorRef.get();

      // Replace successor with its right child
      successorRef.get() = successor->right;

      // Replace current node with successor
      successor->left = toDelete->left;
      successor->right = toDelete->right;
      nodeRef.get() = successor;
    } else if (toDelete->left) {  // single left
      nodeRef.get() = toDelete->left;
    } else {  // single right or no child
      nodeRef.get() = toDelete->right;
    }

    // Delete
    delete toDelete;

    return root;
  }
};
