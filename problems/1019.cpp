// Source: https://leetcode.com/problems/next-greater-node-in-linked-list
// Title: Next Greater Node In Linked List
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the `head` of a linked list with `n` nodes.
//
// For each node in the list, find the value of the **next greater node**. That is, for each node, find the value of the first node that is next to it and has a **strictly larger** value than it.
//
// Return an integer array `answer` where `answer[i]` is the value of the next greater node of the `i^th` node (**1-indexed**). If the `i^th` node does not have a next greater node, set `answer[i] = 0`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/08/05/linkedlistnext1.jpg
//
// ```
// Input: head = [2,1,5]
// Output: [5,5,0]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/08/05/linkedlistnext2.jpg
//
// ```
// Input: head = [2,7,4,3,5]
// Output: [7,0,5,5,0]
// ```
//
// **Constraints:**
//
// - The number of nodes in the list is `n`.
// - `1 <= n <= 10^4`
// - `1 <= Node.val <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Monotonic Stack
//
// Loop through the list, and store the node into the stack.
// Keep the stack non-strictly decreasing.
//
// For each node pop from the stack, we point that node to current node.

class Solution {
 public:
  vector<int> nextLargerNodes(ListNode* head) {
    auto ans = vector<int>();
    auto st = stack<pair<int, int>>();  // (number, index)

    auto idx = 1;
    while (head != nullptr) {
      while (!st.empty() && st.top().first < head->val) {
        ans[st.top().second - 1] = head->val;
        st.pop();
      }
      st.push({head->val, idx});
      ans.push_back(0);
      head = head->next;
      ++idx;
    }

    return ans;
  }
};
