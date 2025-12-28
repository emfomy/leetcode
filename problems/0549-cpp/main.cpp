// Source: https://leetcode.com/problems/binary-tree-longest-consecutive-sequence-ii
// Title: Binary Tree Longest Consecutive Sequence II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return the length of the longest consecutive path in the tree.
//
// A consecutive path is a path where the values of the consecutive nodes in the path differ by one. This path can be either increasing or decreasing.
//
// - For example, `[1,2,3,4]` and `[4,3,2,1]` are both considered valid, but the path `[1,2,4,3]` is not valid.
//
// On the other hand, the path can be in the child-Parent-child order, where not necessarily be parent-child order.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/14/consec2-1-tree.jpg
//
// ```
// Input: root = [1,2,3]
// Output: 2
// Explanation: The longest consecutive path is [1, 2] or [2, 1].
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/03/14/consec2-2-tree.jpg
//
// ```
// Input: root = [2,1,3]
// Output: 3
// Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 3 * 10^4]`.
// - `-3 * 10^4 <= Node.val <= 3 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <stack>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// DFS
class Solution {
 public:
  int longestConsecutive(TreeNode *root) {
    auto ans = 0;
    dfs(root, ans);
    return ans;
  }

  // Returns the sizes of increasing / decreasing paths
  pair<int, int> dfs(TreeNode *root, int &ans) {
    if (root == nullptr) return {0, 0};

    auto [leftInc, leftDesc] = dfs(root->left, ans);
    if (root->left && root->left->val != root->val + 1) leftInc = 0;
    if (root->left && root->left->val != root->val - 1) leftDesc = 0;

    auto [rightInc, rightDesc] = dfs(root->right, ans);
    if (root->right && root->right->val != root->val + 1) rightInc = 0;
    if (root->right && root->right->val != root->val - 1) rightDesc = 0;

    ans = max({ans, leftInc + rightDesc + 1, rightInc + leftDesc + 1});

    return {max(leftInc, rightInc) + 1, max(leftDesc, rightDesc) + 1};
  }
};
