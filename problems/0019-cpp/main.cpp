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

class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto preHead = new ListNode(0, head);

    // Find size
    auto curr = head;
    auto m = 0;
    while (curr != nullptr) {
      curr = curr->next;
      m++;
    }

    // Find m-n
    curr = preHead;
    for (auto i = 0; i < m - n; i++) {
      curr = curr->next;
    }

    // Delete
    auto next = curr->next;
    curr->next = next->next;
    delete next;

    auto ans = preHead->next;
    delete preHead;
    return ans;
  }
};

// Use two pointer
class Solution2 {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto preHead = new ListNode(0, head);

    // Jump
    auto left = preHead;
    auto right = preHead;
    for (auto i = 0; i <= n; i++) {
      right = right->next;
    }

    // Find end
    while (right) {
      left = left->next;
      right = right->next;
    }

    // Delete
    auto next = left->next;
    left->next = next->next;
    delete next;

    auto ans = preHead->next;
    delete preHead;
    return ans;
  }
};
