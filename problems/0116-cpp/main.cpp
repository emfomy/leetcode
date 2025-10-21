// Source: https://leetcode.com/problems/populating-next-right-pointers-in-each-node
// Title: Populating Next Right Pointers in Each Node
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **perfect binary tree** where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:
//
// ```
// struct Node {
//   int val;
//   Node *left;
//   Node *right;
//   Node *next;
// }
// ```
//
// Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to `NULL`.
//
// Initially, all next pointers are set to `NULL`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/02/14/116_sample.png
//
// ```
// Input: root = [1,2,3,4,5,6,7]
// Output: [1,#,2,3,#,4,5,6,7,#]
// Explanation: Given the above perfect binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.
// ```
//
// **Example 2:**
//
// ```
// Input: root = []
// Output: []
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 2^12 - 1]`.
// - `-1000 <= Node.val <= 1000`
//
// **Follow-up:**
//
// - You may only use constant extra space.
// - The recursive approach is fine. You may assume implicit stack space does not count as extra space for this problem.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

class Node {
 public:
  int val;
  Node* left;
  Node* right;
  Node* next;

  Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
  Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
  Node(int _val, Node* _left, Node* _right, Node* _next) : val(_val), left(_left), right(_right), next(_next) {}
};

// First traverse the tree
// Set node->left->next to node->right
// Set node->right->next to node->next->left
class Solution {
 public:
  Node* connect(Node* root) {
    if (!root) return nullptr;
    if (root->left) {
      root->left->next = root->right;
      if (root->next) root->right->next = root->next->left;
    }

    connect(root->left);
    connect(root->right);
    return root;
  }
};

// Double For Loop
// First traverse through left
// For each loop, traverse through next
// For each node,
// * Set node->left->next to node->right
// * Set node->right->next to node->next->left
class Solution2 {
 public:
  Node* connect(Node* root) {
    if (!root) return nullptr;
    for (auto node1 = root; node1->left != nullptr; node1 = node1->left) {
      for (auto node2 = node1; node2 != nullptr; node2 = node2->next) {
        node2->left->next = node2->right;
        if (node2->next) node2->right->next = node2->next->left;
      }
    }
    return root;
  }
};
