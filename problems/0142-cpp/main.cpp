// Source: https://leetcode.com/problems/linked-list-cycle-ii
// Title: Linked List Cycle II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `head` of a linked list, return the node where the cycle begins. If there is no cycle, return `null`.
//
// There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the `next` pointer. Internally, `pos` is used to denote the index of the node that tail's `next` pointer is connected to (**0-indexed**). It is `-1` if there is no cycle. **Note that** `pos` **is not passed as a parameter**.
//
// **Do not modify** the linked list.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png
//
// ```
// Input: head = [3,2,0,-4], pos = 1
// Output: tail connects to node index 1
// Explanation: There is a cycle in the linked list, where tail connects to the second node.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test2.png
//
// ```
// Input: head = [1,2], pos = 0
// Output: tail connects to node index 0
// Explanation: There is a cycle in the linked list, where tail connects to the first node.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test3.png
//
// ```
// Input: head = [1], pos = -1
// Output: no cycle
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
//
// Let X be the node where cycle starts.
// Let Y be the node where slow-fast pointer meets.
//
// Let a be the distance from head to X.
// Let b be the distance from X to Y.
// Let r be the size of the cycle.
//
// We label the nodes on the cycle from 0 to r-1 (start from X).
// That is, Y is labeled as b.
//
// Let s be the number of steps that the slow pointer moves.
// Therefore the fast pointer moves 2s.
//
// We have s = a+b (mod r), 2s = 2(a+b) (mod r)
// Therefore a+b = 0 (mod r)
//
// Now we use another two pointer P & Q.
// P starts from head and Q starts from Y.
//
// We move P & Q a steps.
// P is at X (label 0) now.
// Q is at label b+a = 0 (mod r) now (that is, X).
class Solution {
 public:
  ListNode *detectCycle(ListNode *head) {
    auto fast = head;
    auto slow = head;

    auto found = false;
    while (fast != nullptr && fast->next != nullptr) {
      fast = fast->next->next;
      slow = slow->next;
      if (fast == slow) {
        found = true;
        break;
      }
    }

    if (!found) return nullptr;

    fast = head;  // reuse fast pointer
    while (fast != slow) {
      fast = fast->next;
      slow = slow->next;
    }

    return fast;
  }
};
