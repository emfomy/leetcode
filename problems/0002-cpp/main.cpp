// Source: https://leetcode.com/problems/add-two-numbers
// Title: Add Two Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
//
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
//
// You can return the answer in any order.
//
// Example 1:
//
//   Input: nums = [2,7,11,15], target = 9
//   Output: [0,1]
//   Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
//
// Example 2:
//
//   Input: nums = [3,2,4], target = 6
//   Output: [1,2]
//
// Example 3:
//
//   Input: nums = [3,3], target = 6
//   Output: [0,1]
//
// Constraints:
//
//   2 <= nums.length <= 10^4
//   -10^9 <= nums[i] <= 10^9
//   -10^9 <= target <= 10^9
//   Only one valid answer exists.
//
// Follow-up: Can you come up with an algorithm that is less than O(n^2) time complexity?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    auto head = new ListNode(0);  // dummy head
    auto curr = head;
    auto carry = 0;
    while (l1 != nullptr || l2 != nullptr || carry != 0) {
      auto x = l1 ? l1->val : 0;
      auto y = l2 ? l2->val : 0;
      auto sum = x + y + carry;
      carry = sum / 10;
      curr->next = new ListNode(sum % 10);
      curr = curr->next;
      l1 = l1 ? l1->next : nullptr;
      l2 = l2 ? l2->next : nullptr;
    }

    auto ans = head->next;
    delete head;  // free dummy head
    return ans;
  }
};
