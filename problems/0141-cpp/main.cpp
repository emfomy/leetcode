// Source: https://leetcode.com/problems/linked-list-cycle
// Title: Linked List Cycle
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given `head`, the head of a linked list, determine if the linked list has a cycle in it.
//
// There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the`next`pointer. Internally, `pos`is used to denote the index of the node thattail's`next`pointer is connected to.**Note that`pos`is not passed as a parameter**.
//
// Return`true` if there is a cycle in the linked list. Otherwise, return `false`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png
//
// ```
// Input: head = [3,2,0,-4], pos = 1
// Output: true
// Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test2.png
//
// ```
// Input: head = [1,2], pos = 0
// Output: true
// Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test3.png
//
// ```
// Input: head = [1], pos = -1
// Output: false
// Explanation: There is no cycle in the linked list.
// ```
//
// **Constraints:**
//
// - The number of the nodes in the list is in the range `[0, 10^4]`.
// - `-10^5 <= Node.val <= 10^5`
// - `pos` is `-1` or a **valid index** in the linked-list.
//
// **Follow up:** Can you solve it using `O(1)` (i.e. constant) memory?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

// Use two pointer
class Solution {
 public:
  bool hasCycle(ListNode *head) {
    auto fast = head;
    auto slow = head;
    while (fast != nullptr && fast->next != nullptr) {
      fast = fast->next->next;
      slow = slow->next;
      if (fast == slow) return true;
    }
    return false;
  }
};
