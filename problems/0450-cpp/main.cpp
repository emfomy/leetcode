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

// First find the node to be deleted.
//
// If node has no child, just delete it.
// If node has only one child, replace with its child.
// If node has two children, replace with leftmost of right child. (Or rightmost of left child).
class Solution {
 public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    if (root == nullptr) return nullptr;

    if (key == root->val) {
      if (root->left == nullptr) return root->right;
      if (root->right == nullptr) return root->left;

      // Find leftmost of right
      auto child = root->right;
      while (child->left) child = child->left;

      // Delete from right
      root->right = deleteNode(root->right, child->val);

      // Replace current node
      child->left = root->left;
      child->right = root->right;
      root = child;
    } else if (key < root->val) {
      root->left = deleteNode(root->left, key);
    } else {
      root->right = deleteNode(root->right, key);
    }

    return root;
  }
};
