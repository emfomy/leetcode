// Source: https://leetcode.com/problems/reorder-list
// Title: Reorder List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the head of a singly linked-list. The list can be represented as:
//
// ```
// L_0 → L_1 → … → L_n - 1 → L_n
// ```
//
// Reorder the list to be on the following form:
//
// ```
// L_0 → L_n → L_1 → L_n - 1 → L_2 → L_n - 2 → …
// ```
//
// You may not modify the values in the list's nodes. Only nodes themselves may be changed.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/04/reorder1linked-list.jpg
//
// ```
// Input: head = [1,2,3,4]
// Output: [1,4,2,3]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/09/reorder2-linked-list.jpg
//
// ```
// Input: head = [1,2,3,4,5]
// Output: [1,5,2,4,3]
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is in the range `[1, 5 * 10^4]`.
// - `1 <= Node.val <= 1000`
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
 private:
  //  Find middle node
  // [] -> null
  // [1] -> 1
  // [1, 2] -> 1
  // [1, 2, 3] -> 2
  // [1, 2, 3, 4] -> 2
  ListNode* getMiddle(ListNode* head) {
    if (head == nullptr) return nullptr;

    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
      fast = fast->next->next;
      slow = slow->next;
    }
    return slow;
  }

  // Reverse List
  // [] -> []
  // [1] -> [1]
  // [1, 2, 3] -> [3, 2, 1]
  ListNode* reverseList(ListNode* head) {
    ListNode* reverseHead = nullptr;

    auto node = head;
    while (node != nullptr) {
      auto currNode = node;
      node = node->next;

      // Push at front of reversed list
      currNode->next = reverseHead;
      reverseHead = currNode;
    }

    return reverseHead;
  }

  // Merge both list alternatively.
  // The new head is left head.
  void mergeLists(ListNode* left, ListNode* right) {
    ListNode dummy;
    auto node = &dummy;

    while (left != nullptr && right != nullptr) {
      // Insert left
      node->next = left;
      left = left->next;
      node = node->next;

      // Insert right
      node->next = right;
      right = right->next;
      node = node->next;
    }

    // Insert remaining nodes
    node->next = (left != nullptr) ? left : right;
  }

 public:
  void reorderList(ListNode* head) {
    // Edge case, ensure midNode is not null
    if (head == nullptr) return;

    // Find middle node (end of left half)
    auto midNode = getMiddle(head);

    // Reverse right half
    auto rightHead = reverseList(midNode->next);
    midNode->next = nullptr;  // disconnect end of left half

    // Merge both lists
    mergeLists(head, rightHead);
  }
};
