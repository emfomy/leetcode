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

// Use Heap
class Solution {
 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    // Prepare queue
    auto comp = [](ListNode* a, ListNode* b) -> bool { return !(a->val < b->val); };  // heap comp is inverted
    auto queue = priority_queue(comp, vector<ListNode*>());
    for (auto& node : lists) {
      if (node != nullptr) {
        queue.push(node);
      }
    }

    // Sort
    auto head = new ListNode();
    auto prev = head;
    while (!queue.empty()) {
      auto node = queue.top();
      queue.pop();

      prev->next = node;
      prev = node;
      if (node->next) {
        queue.push(node->next);
      }
    }

    // Answer
    auto ans = head->next;
    delete head;
    return ans;
  }
};
