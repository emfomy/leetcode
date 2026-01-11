// Source: https://leetcode.com/problems/remove-duplicates-from-sorted-list
// Title: Remove Duplicates from Sorted List
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `head` of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list **sorted** as well.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/04/list1.jpg
//
// ```
// Input: head = [1,1,2]
// Output: [1,2]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/01/04/list2.jpg
//
// ```
// Input: head = [1,1,2,3,3]
// Output: [1,2,3]
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is in the range `[0, 300]`.
// - `-100 <= Node.val <= 100`
// - The list is guaranteed to be **sorted** in ascending order.
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
  ListNode* deleteDuplicates(ListNode* head) {
    auto node = head;
    while (node != nullptr) {
      while (node->next && node->val == node->next->val) {
        node->next = node->next->next;
      }
      node = node->next;
    }

    return head;
  }
};
