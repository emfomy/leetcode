// Source: https://leetcode.com/problems/flatten-binary-tree-to-linked-list
// Title: Flatten Binary Tree to Linked List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, flatten the tree into a "linked list":
//
// - The "linked list" should use the same `TreeNode` class where the `right` child pointer points to the next node in the list and the `left` child pointer is always `null`.
// - The "linked list" should be in the same order as a **pre-order traversal** of the binary tree.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/14/flaten.jpg
//
// ```
// Input: root = [1,2,5,3,4,null,6]
// Output: [1,null,2,null,3,null,4,null,5,null,6]
// ```
//
// **Example 2:**
//
// ```
// Input: root = []
// Output: []
// ```
//
// **Example 3:**
//
// ```
// Input: root = [0]
// Output: [0]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 2000]`.
// - `-100 <= Node.val <= 100`
//
// **Follow up:** Can you flatten the tree in-place (with `O(1)` extra space)?
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
  void flatten(TreeNode *root) {  //
    traverse(root);
  }

 private:
  TreeNode *traverse(TreeNode *node) {  // returns the tail
    if (node == nullptr) return nullptr;

    auto tail = node;

    auto left = node->left, right = node->right;
    node->left = nullptr;

    auto leftTail = traverse(left);
    if (leftTail) {
      node->right = left;
      leftTail->right = right;
      tail = leftTail;
    }

    auto rightTail = traverse(right);
    if (rightTail) {
      tail = rightTail;
    }

    return tail;
  }
};

// Iteration
//
// Move right child to the rightmost child of left child, then move left child to right
class Solution2 {
 public:
  void flatten(TreeNode *root) {
    if (root == nullptr) return;

    auto node = root;
    while (node) {
      if (node->left) {
        // Find rightmost child
        auto rightmost = node->left;
        while (rightmost->right) {
          rightmost = rightmost->right;
        }
        rightmost->right = node->right;

        node->right = node->left;
        node->left = nullptr;
      }

      node = node->right;
    }
  }
};
