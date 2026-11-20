// Source: https://leetcode.com/problems/remove-nth-node-from-end-of-list
// Title: Remove Nth Node From End of List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `head` of a linked list, remove the `n^th` node from the end of the list and return its head.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg
//
// ```
// Input: head = [1,2,3,4,5], n = 2
// Output: [1,2,3,5]
// ```
//
// **Example 2:**
//
// ```
// Input: head = [1], n = 1
// Output: []
// ```
//
// **Example 3:**
//
// ```
// Input: head = [1,2], n = 1
// Output: [1]
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is `sz`.
// - `1 <= sz <= 30`
// - `0 <= Node.val <= 100`
// - `1 <= n <= sz`
//
// **Follow up:** Could you do this in one pass?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Count length
class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto dummy = new ListNode(0, head);  // dummy head

    // Count length
    auto len = 0;
    for (auto node = head; node != nullptr; node = node->next) ++len;

    // Find node before target
    auto node = dummy;
    for (auto i = 0; i < len - n; ++i) node = node->next;

    // Delete node
    node->next = node->next->next;

    head = dummy->next;
    delete dummy;

    return head;
  }
};

// Two pointer
//
// Move first pointer n steps, then move both together
class Solution2 {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto dummy = new ListNode(0, head);  // dummy head

    auto fast = dummy;
    auto slow = dummy;

    // Move fast
    for (auto i = 0; i <= n; ++i) fast = fast->next;

    // Move both
    while (fast != nullptr) {
      fast = fast->next;
      slow = slow->next;
    }

    // Delete node
    slow->next = slow->next->next;

    head = dummy->next;
    delete dummy;

    return head;
  }
};
