// Source: https://leetcode.com/problems/reverse-nodes-in-k-group
// Title: Reverse Nodes in k-Group
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `head` of a linked list, reverse the nodes of the list `k` at a time, and return the modified list.
//
// `k` is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of `k` then left-out nodes, in the end, should remain as it is.
//
// You may not alter the values in the list's nodes, only nodes themselves may be changed.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/10/03/reverse_ex1.jpg
//
// ```
// Input: head = [1,2,3,4,5], k = 2
// Output: [2,1,4,3,5]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/10/03/reverse_ex2.jpg
//
// ```
// Input: head = [1,2,3,4,5], k = 3
// Output: [3,2,1,4,5]
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is `n`.
// - `1 <= k <= n <= 5000`
// - `0 <= Node.val <= 1000`
//
// **Follow-up:** Can you solve the problem in `O(1)` extra memory space?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <utility>

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
  ListNode* reverseKGroup(ListNode* head, int k) {
    auto preHead = new ListNode(0, head);

    auto jumpK = [=](ListNode* node) -> pair<ListNode*, bool> {
      for (auto i = 0; i < k; i++) {
        if (node == nullptr) return {nullptr, false};
        node = node->next;
      }
      return {node, true};
    };

    auto leftOut = preHead;
    auto leftIn = head;
    while (leftIn) {
      auto [rightIn, ok] = jumpK(leftOut);
      if (!ok || !rightIn) break;
      auto rightOut = rightIn->next;

      // Swap
      auto prev = leftOut;
      auto curr = leftIn;
      do {
        auto next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
      } while (curr != rightOut);

      leftOut->next = rightIn;
      leftIn->next = rightOut;

      leftOut = leftIn;
      leftIn = rightOut;
    }

    auto ans = preHead->next;
    delete preHead;
    return ans;
  }
};
