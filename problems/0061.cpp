// Source: https://leetcode.com/problems/rotate-list
// Title: Rotate List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `head` of a linkedlist, rotate the list to the right by `k` places.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/11/13/rotate1.jpg
//
// ```
// Input: head = [1,2,3,4,5], k = 2
// Output: [4,5,1,2,3]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/11/13/roate2.jpg
//
// ```
// Input: head = [0,1,2], k = 4
// Output: [2,0,1]
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is in the range `[0, 500]`.
// - `-100 <= Node.val <= 100`
// - `0 <= k <= 2 * 10^9`
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
  ListNode* rotateRight(ListNode* head, int k) {
    // Trivial case
    if (!head) return nullptr;

    // Find list size
    int n = 1;
    ListNode* tail = head;
    while (tail->next) {
      tail = tail->next;
      ++n;
    }
    k %= n;

    // Early stop
    if (k == 0) return head;

    // Find (n-k-1)-th node, it should be the newest tail
    ListNode* newTail = head;
    for (int i = 1; i < n - k; ++i) {
      newTail = newTail->next;
    }
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;
    tail->next = head;

    return newHead;
  }
};
