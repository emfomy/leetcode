// Source: https://leetcode.com/problems/merge-k-sorted-lists
// Title: Merge k Sorted Lists
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of `k` linked-lists `lists`, each linked-list is sorted in ascending order.
//
// Merge all the linked-lists into one sorted linked-list and return it.
//
// **Example 1:**
//
// ```
// Input: lists = [[1,4,5],[1,3,4],[2,6]]
// Output: [1,1,2,3,4,4,5,6]
// Explanation: The linked-lists are:
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// merging them into one sorted linked list:
// 1->1->2->3->4->4->5->6
// ```
//
// **Example 2:**
//
// ```
// Input: lists = []
// Output: []
// ```
//
// **Example 3:**
//
// ```
// Input: lists = [[]]
// Output: []
// ```
//
// **Constraints:**
//
// - `k == lists.length`
// - `0 <= k <= 10^4`
// - `0 <= lists[i].length <= 500`
// - `-10^4 <= lists[i][j] <= 10^4`
// - `lists[i]` is sorted in **ascending order**.
// - The sum of `lists[i].length` will not exceed `10^4`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Heap
//
// Use a min-heap for the head of the lists.
class Solution {
  struct Comp {
    bool operator()(ListNode* a, ListNode* b) {
      return !(a->val < b->val);  // min-heap
    }
  };

  using Heap = priority_queue<ListNode*, vector<ListNode*>, Comp>;

 public:
  ListNode* mergeKLists(const vector<ListNode*>& lists) {
    // Init heap
    Heap heap;
    for (ListNode* node : lists) {
      if (node) heap.push(node);
    }

    // Loop
    ListNode dummy;
    ListNode* tail = &dummy;
    while (!heap.empty()) {
      ListNode* node = heap.top();
      heap.pop();

      // Push into new list
      tail->next = node;
      tail = tail->next;

      // Push next into heap
      if (node->next) {
        heap.push(node->next);
      }
    }

    // Clear end, no-op
    tail->next = nullptr;

    return dummy.next;
  }
};
