// Source: https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree
// Title: Maximum Level Sum of a Binary Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, the level of its root is `1`, the level of its children is `2`, and so on.
//
// Return the **smallest** level `x` such that the sum of all the values of nodes at level `x` is **maximal**.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/05/03/capture.JPG
//
// ```
// Input: root = [1,7,0,7,-8,null,null]
// Output: 2
// Explanation:
// Level 1 sum = 1.
// Level 2 sum = 7 + 0 = 7.
// Level 3 sum = 7 + -8 = -1.
// So we return the level with the maximum sum which is level 2.
// ```
//
// **Example 2:**
//
// ```
// Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
// Output: 2
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 10^4]`.
// - `-10^5 <= Node.val <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// BFS
class Solution {
 public:
  int maxLevelSum(TreeNode *root) {
    if (root == nullptr) return 0;

    auto prev = vector<TreeNode *>();
    auto curr = vector<TreeNode *>({root});

    auto idx = 0, maxIdx = -1, maxSum = int(-1e6);
    while (!curr.empty()) {
      swap(curr, prev);
      curr.clear();
      ++idx;

      auto sum = 0;
      for (auto node : prev) {
        sum += node->val;
        if (node->left) curr.push_back(node->left);
        if (node->right) curr.push_back(node->right);
      }

      if (maxSum < sum) {
        maxIdx = idx;
        maxSum = sum;
      }
    }

    return maxIdx;
  }
};
