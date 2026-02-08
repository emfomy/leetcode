// Source: https://leetcode.com/problems/merge-two-sorted-lists
// Title: Merge Two Sorted Lists
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the heads of two sorted linked lists `list1` and `list2`.
//
// Merge the two lists into one **sorted** list. The list should be made by splicing together the nodes of the first two lists.
//
// Return the head of the merged linked list.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/10/03/merge_ex1.jpg
//
// ```
// Input: list1 = [1,2,4], list2 = [1,3,4]
// Output: [1,1,2,3,4,4]
// ```
//
// **Example 2:**
//
// ```
// Input: list1 = [], list2 = []
// Output: []
// ```
//
// **Example 3:**
//
// ```
// Input: list1 = [], list2 = [0]
// Output: [0]
// ```
//
// **Constraints:**
//
// - The number of nodes in both lists is in the range `[0, 50]`.
// - `-100 <= Node.val <= 100`
// - Both `list1` and `list2` are sorted in **non-decreasing** order.
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
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    auto dummy = ListNode();

    auto node = &dummy;
    while (list1 != nullptr && list2 != nullptr) {
      if (list1->val < list2->val) {
        node->next = list1;
        list1 = list1->next;
      } else {
        node->next = list2;
        list2 = list2->next;
      }
      node = node->next;
    }

    node->next = list1 ? list1 : list2;

    return dummy.next;
  }
};
