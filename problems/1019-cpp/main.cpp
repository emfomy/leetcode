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

// Vector + Monotonic Stack
class Solution {
 public:
  vector<int> nextLargerNodes(ListNode* head) {
    // Convert to vector
    auto nums = vector<int>();
    while (head != nullptr) {
      nums.push_back(head->val);
      head = head->next;
    }

    // Monotonic stack
    int n = nums.size();
    auto st = stack<int>();
    auto ans = vector<int>(n);
    for (auto i = n - 1; i >= 0; --i) {
      auto num = nums[i];
      while (!st.empty() && st.top() <= num) st.pop();
      ans[i] = st.empty() ? 0 : st.top();
      st.push(num);
    }

    return ans;
  }
};
