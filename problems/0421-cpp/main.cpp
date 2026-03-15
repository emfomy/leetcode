// Source: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array
// Title: Maximum XOR of Two Numbers in an Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return the maximum result of `nums[i] XOR nums[j]`, where `0 <= i <= j < n`.
//
// **Example 1:**
//
// ```
// Input: nums = [3,10,5,25,2,8]
// Output: 28
// Explanation: The maximum result is 5 XOR 25 = 28.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
// Output: 127
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 2 * 10^5`
// - `0 <= nums[i] <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Trie
//
// We put the numbers into a trie of its binary form.
//
// Now loop for all numbers.
// For each number, start from the trie root,
// always choose the node with different bit if possible.
class Solution {
  constexpr static int kMaxBit = 31;

  struct Node {
    Node* child[2];
  };

  void insert(Node* root, const unsigned num) {
    Node* node = root;
    for (int i = kMaxBit; i >= 0; --i) {
      int b = (num >> i) & 1u;
      if (!node->child[b]) node->child[b] = new Node();
      node = node->child[b];
    }
  }

  // Find max XOR partner
  int find(Node* root, const unsigned num) {
    unsigned ans = 0;

    Node* node = root;
    for (int i = kMaxBit; i >= 0; --i) {
      int b = !((num >> i) & 1u);   // pick complement
      if (!node->child[b]) b = !b;  // go to sibling
      ans = (ans << 1 | b);
      node = node->child[b];
    }

    return ans;
  }

 public:
  int findMaximumXOR(const vector<int>& nums) {
    const int n = nums.size();

    // Build tree
    auto trie = new Node();
    for (const unsigned num : nums) {
      insert(trie, num);
    }

    // Find answer
    unsigned ans = 0;
    for (const unsigned num : nums) {
      ans = max(ans, (num ^ find(trie, num)));
    }

    return ans;
  }
};
