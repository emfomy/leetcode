// Source: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii
// Title: Remove Duplicates from Sorted List II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `head` of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list **sorted** as well.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/04/linkedlist1.jpg
//
// ```
// Input: head = [1,2,3,3,4,4,5]
// Output: [1,2,5]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/01/04/linkedlist2.jpg
//
// ```
// Input: head = [1,1,1,2,3]
// Output: [2,3]
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is in the range `[0, 300]`.
// - `-100 <= Node.val <= 100`
// - The list is guaranteed to be **sorted** in ascending order.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Use counter
class Solution {
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    auto preHead = new ListNode(-1000, head);

    auto counter = unordered_map<int, int>();

    auto curr = head;
    while (curr) {
      counter[curr->val]++;
      curr = curr->next;
    }

    curr = preHead;
    while (curr->next) {
      auto next = curr->next;
      auto val = next->val;
      if (counter[val] > 1) {
        while (next && next->val == val) {
          curr->next = next->next;
          delete next;
          next = curr->next;
        }
      } else {
        curr = curr->next;
      }
    }

    auto ans = preHead->next;
    delete preHead;
    return ans;
  }
};

class Solution2 {
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    auto preHead = new ListNode(-1000, head);

    auto curr = preHead;
    while (curr->next) {
      auto next = curr->next;
      auto val = next->val;

      // Count duplicate
      auto count = 0;
      while (next && next->val == val) {
        count++;
        next = next->next;
      }

      // Delete
      if (count > 1) {
        next = curr->next;
        for (auto i = 0; i < count; i++) {
          curr->next = next->next;
          delete next;
          next = curr->next;
        }
      } else {
        curr = curr->next;
      }
    }

    auto ans = preHead->next;
    delete preHead;
    return ans;
  }
};
