// Source: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii
// Title: Lowest Common Ancestor of a Binary Tree III
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two nodes of abinary tree `p` and `q`, return their lowest common ancestor (LCA).
//
// Each node will have a reference to its parent node. The definition for `Node` is below:
//
// ```
// class Node {
//     public int val;
//     public Node left;
//     public Node right;
//     public Node parent;
// }
// ```
//
// According to the **definition of LCA on Wikipedia** (https://en.wikipedia.org/wiki/Lowest_common_ancestor): "The lowest common ancestor of two nodes p and q in a tree T is the lowest node that has both p and q as descendants (where we allow **a node to be a descendant of itself**)."
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/12/14/binarytree.png
//
// ```
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
// Output: 3
// Explanation: The LCA of nodes 5 and 1 is 3.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2018/12/14/binarytree.png
//
// ```
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
// Output: 5
// Explanation: The LCA of nodes 5 and 4 is 5 since a node can be a descendant of itself according to the LCA definition.
// ```
//
// **Example 3:**
//
// ```
// Input: root = [1,2], p = 1, q = 2
// Output: 1
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[2, 10^5]`.
// - `-10^9 <= Node.val <= 10^9`
// - All `Node.val` are **unique**.
// - `p != q`
// - `p` and `q` exist in the tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <stack>
#include <unordered_set>

using namespace std;

struct Node {
  int val;
  Node* left;
  Node* right;
  Node* parent;
};

// Stack
class Solution {
 public:
  Node* lowestCommonAncestor(Node* p, Node* q) {
    // p stack
    auto pStack = stack<Node*>();
    for (auto node = p; node != nullptr; node = node->parent) pStack.push(node);

    // q stack
    auto qStack = stack<Node*>();
    for (auto node = q; node != nullptr; node = node->parent) qStack.push(node);

    // find common
    Node* ans = nullptr;
    while (!pStack.empty() && !qStack.empty() && pStack.top() == qStack.top()) {
      ans = pStack.top();
      pStack.pop();
      qStack.pop();
    }

    return ans;
  }
};

// Two pointer
class Solution2 {
 public:
  Node* lowestCommonAncestor(Node* p, Node* q) {
    auto a = p, b = q;

    while (a != b) {
      a = a->parent ? a->parent : q;
      b = b->parent ? b->parent : p;
    }

    return a;
  }
};
