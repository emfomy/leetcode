// Source: https://leetcode.com/problems/reverse-linked-list-ii
// Title: Reverse Linked List II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/02/19/rev2ex2.jpg
//
//   Input: head = [1,2,3,4,5], left = 2, right = 4
//   Output: [1,4,3,2,5]
//
// Example 2:
//
//   Input: head = [5], left = 1, right = 1
//   Output: [5]
//
// Constraints:
//
//   The number of nodes in the list is n.
//   1 <= n <= 500
//   -500 <= Node.val <= 500
//   1 <= left <= right <= n
//
// Follow up: Could you do it in one pass?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    auto preHead = new ListNode(0, head);

    // Jump to left
    ListNode* prev = preHead;
    for (auto i = 1; i < left; i++) {
      prev = prev->next;
    }
    auto leftOut = prev;
    auto leftIn = prev->next;

    // Reverse
    auto curr = prev->next;
    for (auto i = left; i <= right; i++) {
      auto next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    leftOut->next = prev;
    leftIn->next = curr;

    auto ans = preHead->next;
    delete preHead;
    return ans;
  }
};
