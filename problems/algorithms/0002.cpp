// Source: https://leetcode.com/problems/add-two-numbers/
// Title: Add Two Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//
// Example:
//
//   Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
//   Output: 7 -> 0 -> 8
//   Explanation: 342 + 465 = 807.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
 public:
  ListNode* addTwoNumbers( ListNode* l1, ListNode* l2, int carry = 0 ) {
    if ( !l1 && !l2 ) {
      return carry ? new ListNode(carry) : nullptr;
    }
    carry += (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
    auto *l3 = new ListNode(carry%10);
    l1 = l1 ? l1->next : nullptr;
    l2 = l2 ? l2->next : nullptr;
    l3->next = addTwoNumbers(l1, l2, carry/10);
    return l3;
  }
};
