// Source: https://leetcode.com/problems/binary-tree-longest-consecutive-sequence
// Title: Binary Tree Longest Consecutive Sequence
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return the length of the longest **consecutive sequence path**.
//
// A **consecutive sequence path** is a path where the values **increase by one** along the path.
//
// Note that the path can start **at any node** in the tree, and you cannot go from a node to its parent in the path.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/14/consec1-1-tree.jpg
//
// ```
// Input: root = [1,null,3,2,4,null,null,null,5]
// Output: 3
// Explanation: Longest consecutive sequence path is 3-4-5, so return 3.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/14/consec1-2-tree.jpg
//
// ```
// Input: root = [2,null,3,2,null,1]
// Output: 2
// Explanation: Longest consecutive sequence path is 2-3, not 3-2-1, so return 2.
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 3 * 10^4]`.
// - `-3 * 10^4 <= Node.val <= 3 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  int longestConsecutive(TreeNode *root) {
    auto [_, ans] = longestConsecutive_(root);
    return ans;
  }

  // Returns current max length and global max length
  pair<int, int> longestConsecutive_(TreeNode *root) {
    auto currLen = 1;
    auto globalLen = 1;

    if (root->left) {
      auto [leftLen, leftGlobalLen] = longestConsecutive_(root->left);
      globalLen = max(globalLen, leftGlobalLen);
      if (root->left->val == root->val + 1) {
        currLen = max(currLen, leftLen + 1);
      }
    }

    if (root->right) {
      auto [rightLen, rightGlobalLen] = longestConsecutive_(root->right);
      globalLen = max(globalLen, rightGlobalLen);
      if (root->right->val == root->val + 1) {
        currLen = max(currLen, rightLen + 1);
      }
    }

    globalLen = max(globalLen, currLen);

    return {currLen, globalLen};
  }
};
