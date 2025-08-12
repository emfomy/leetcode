// Source: https://leetcode.com/problems/partition-list
// Title: Partition List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `head` of a linked list and a value `x`, partition it such that all nodes **less than** `x` come before nodes **greater than or equal** to `x`.
//
// You should **preserve** the original relative order of the nodes in each of the two partitions.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/04/partition.jpg
//
// ```
// Input: head = [1,4,3,2,5,2], x = 3
// Output: [1,2,2,4,3,5]
// ```
//
// **Example 2:**
//
// ```
// Input: head = [2,1], x = 2
// Output: [1,2]
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is in the range `[0, 200]`.
// - `-100 <= Node.val <= 100`
// - `-200 <= x <= 200`
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
  ListNode* partition(ListNode* head, int x) {
    auto left = new ListNode();
    auto right = new ListNode();

    auto curr = head;
    auto lCurr = left;
    auto rCurr = right;
    while (curr) {
      if (curr->val < x) {
        lCurr->next = curr;
        lCurr = curr;
      } else {
        rCurr->next = curr;
        rCurr = curr;
      }
      curr = curr->next;
    }

    lCurr->next = right->next;
    rCurr->next = nullptr;
    auto ans = left->next;
    delete left;
    delete right;
    return ans;
  }
};
