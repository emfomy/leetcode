// Source: https://leetcode.com/problems/add-two-numbers-ii
// Title: Add Two Numbers II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two **non-empty** linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/04/09/sumii-linked-list.jpg
//
// ```
// Input: l1 = [7,2,4,3], l2 = [5,6,4]
// Output: [7,8,0,7]
// ```
//
// **Example 2:**
//
// ```
// Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [8,0,7]
// ```
//
// **Example 3:**
//
// ```
// Input: l1 = [0], l2 = [0]
// Output: [0]
// ```
//
// **Constraints:**
//
// - The number of nodes in each linked list is in the range `[1, 100]`.
// - `0 <= Node.val <= 9`
// - It is guaranteed that the list represents a number that does not have leading zeros.
//
// **Follow up:** Could you solve it without reversing the input lists?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Use stack
class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // Put digits into stack
    auto st1 = stack<int>();
    auto st2 = stack<int>();
    while (l1) {
      st1.push(l1->val);
      l1 = l1->next;
    }
    while (l2) {
      st2.push(l2->val);
      l2 = l2->next;
    }

    // Add
    ListNode* l3 = nullptr;
    auto val = 0;  // carry
    while (!st1.empty() || !st2.empty()) {
      if (!st1.empty()) {
        val += st1.top();
        st1.pop();
      }
      if (!st2.empty()) {
        val += st2.top();
        st2.pop();
      }
      l3 = new ListNode(val % 10, l3);
      val /= 10;
    }
    if (val) {
      l3 = new ListNode(val, l3);
    }

    return l3;
  }
};
