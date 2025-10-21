// Source: https://leetcode.com/problems/binary-tree-preorder-traversal
// Title: Binary Tree Preorder Traversal
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return the preorder traversal of its nodes' values.
//
// **Example 1:**
//
// ```
// Input: root = [1,null,2,3]
// Output: [1,2,3]
// Explanation:
// https://assets.leetcode.com/uploads/2024/08/29/screenshot-2024-08-29-202743.png
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
// Output: [1,2,4,5,6,7,3,8,9]
// Explanation:
// https://assets.leetcode.com/uploads/2024/08/29/tree_2.png
// ```
//
// **Example 3:**
//
// ```
// Input: root = []
// Output: []
// ```
//
// **Example 4:**
// ```
// Input: root = [1]
// Output: [1]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 100]`.
// - `-100 <= Node.val <= 100`
//
// **Follow up:** Recursive solution is trivial, could you do it iteratively?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <utility>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

// Two Pointer
//
// First find length of both list.
// Move the longer on first, and move both together.
class Solution {
 public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    // Find length
    auto lenA = 0;
    for (auto node = headA; node != nullptr; node = node->next) ++lenA;

    auto lenB = 0;
    for (auto node = headB; node != nullptr; node = node->next) ++lenB;

    // Ensure lenA >= lenB
    if (lenA < lenB) {
      swap(headA, headB);
      swap(lenA, lenB);
    }

    // Move A
    while (lenA > lenB) {
      headA = headA->next;
      --lenA;
    }

    // Move both
    while (headA != headB) {
      headA = headA->next;
      headB = headB->next;
    }

    return headA;
  }
};

// Two Pointer
//
// Say the intersection node is C.
// Say dist(A, C) = a, dist(B, C) = b, dist(C, tail) = c.
//
// Use two pointer P1 & P2.
// Let P1 traverse A -> C -> Tail -> (jump) -> B -> C.
// Let P2 traverse B -> C -> Tail -> (jump) -> A -> C
// Both pointer moves a + b + c steps.
class Solution2 {
 public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    auto nodeA = headA, nodeB = headB;

    while (nodeA != nodeB) {
      nodeA = nodeA ? nodeA->next : headB;
      nodeB = nodeB ? nodeB->next : headA;
    }

    return nodeA;
  }
};
