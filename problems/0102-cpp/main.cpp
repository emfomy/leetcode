// Source: https://leetcode.com/problems/binary-tree-level-order-traversal
// Title: Binary Tree Level Order Traversal
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/02/19/tree1.jpg
//
// ```
// Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[9,20],[15,7]]
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1]
// Output: [[1]]
// ```
//
// **Example 3:**
//
// ```
// Input: root = []
// Output: []
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 2000]`.
// - `-1000 <= Node.val <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
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

// Use BFS (Queue)
class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    if (!root) return {};

    auto ans = vector<vector<int>>();
    auto curr = queue<TreeNode *>();
    auto next = queue<TreeNode *>();
    curr.push(root);

    while (!curr.empty()) {
      auto currAns = vector<int>();
      while (!curr.empty()) {
        auto node = curr.front();
        curr.pop();
        currAns.push_back(node->val);
        if (node->left) next.push(node->left);
        if (node->right) next.push(node->right);
      }

      swap(curr, next);
      ans.push_back(currAns);
    }

    return ans;
  }
};

// Use BFS (Single Queue)
class Solution2 {
 public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    if (!root) return {};

    auto ans = vector<vector<int>>();
    auto que = queue<TreeNode *>();
    que.push(root);

    while (!que.empty()) {
      auto currAns = vector<int>();
      int queSize = que.size();
      for (auto i = 0; i < queSize; ++i) {
        auto node = que.front();
        que.pop();
        currAns.push_back(node->val);
        if (node->left) que.push(node->left);
        if (node->right) que.push(node->right);
      }
      ans.push_back(currAns);
    }

    return ans;
  }
};
