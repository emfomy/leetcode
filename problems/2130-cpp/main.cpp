// Source: https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list
// Title: Maximum Twin Sum of a Linked List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In a linked list of size `n`, where `n` is **even**, the `i^th` node (**0-indexed**) of the linked list is known as the **twin** of the `(n-1-i)^th` node, if `0 <= i <= (n / 2) - 1`.
//
// - For example, if `n = 4`, then node `0` is the twin of node `3`, and node `1` is the twin of node `2`. These are the only nodes with twins for `n = 4`.
//
// The **twin sum **is defined as the sum of a node and its twin.
//
// Given the `head` of a linked list with even length, return the **maximum twin sum** of the linked list.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/12/03/eg1drawio.png
//
// ```
// Input: head = [5,4,2,1]
// Output: 6
// Explanation:
// Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum = 6.
// There are no other nodes with twins in the linked list.
// Thus, the maximum twin sum of the linked list is 6.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/12/03/eg2drawio.png
//
// ```
// Input: head = [4,2,2,3]
// Output: 7
// Explanation:
// The nodes with twins present in this linked list are:
// - Node 0 is the twin of node 3 having a twin sum of 4 + 3 = 7.
// - Node 1 is the twin of node 2 having a twin sum of 2 + 2 = 4.
// Thus, the maximum twin sum of the linked list is max(7, 4) = 7.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/12/03/eg3drawio.png
//
// ```
// Input: head = [1,100000]
// Output: 100001
// Explanation:
// There is only one node with a twin in the linked list having twin sum of 1 + 100000 = 100001.
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is an **even** integer in the range `[2, 10^5]`.
// - `1 <= Node.val <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Two Pointer
//
// First use fast-slow pointer to find the middle of the list.
// Split the list into two half, and reverse the last half.
// Now loop though both half simultaneously to find the max pair sum.
class Solution {
 public:
  int pairSum(ListNode* head) {
    ListNode* mid = findMid(head);
    mid = reverse(mid);
    int maxSum = head->val + mid->val;
    for (ListNode *p1 = head, *p2 = mid; p2 != nullptr; p1 = p1->next, p2 = p2->next) {
      maxSum = max(maxSum, p1->val + p2->val);
    }
    // reverse(mid); // restore the list
    return maxSum;
  }

  ListNode* findMid(ListNode* head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast != nullptr) {
      fast = fast->next->next;  // safe since n is even
      slow = slow->next;
    }
    return slow;
  }

  ListNode* reverse(ListNode* head) {
    ListNode* prev = head;
    ListNode* curr = head->next;  // safe since n is not zero
    prev->next = nullptr;
    while (curr != nullptr) {
      ListNode* next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    return prev;
  }
};
