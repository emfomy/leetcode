// Source: https://leetcode.com/problems/binary-tree-right-side-view
// Title: Binary Tree Right Side View
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, imagine yourself standing on the **right side** of it, return the values of the nodes you can see ordered from top to bottom.
//
// **Example 1:**
//
// ```
// Input: root = [1,2,3,null,5,null,4]
// Output: [1,3,4]
// Explanation:
// https://assets.leetcode.com/uploads/2024/11/24/tmpd5jn43fs-1.png
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1,2,3,4,null,null,null,5]
// Output: [1,3,4,5]
// Explanation:
// https://assets.leetcode.com/uploads/2024/11/24/tmpkpe40xeh-1.png
// ```
//
// **Example 3:**
//
// ```
// Input: root = [1,null,3]
// Output: [1,3]
// ```
//
// **Example 4:**
//
// ```
// Input: root = []
// Output: []
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 100]`.
// - `-100 <= Node.val <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <utility>
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

// BFS
class Solution {
 public:
  vector<int> rightSideView(TreeNode *root) {
    // Edge case
    if (root == nullptr) return {};

    // Prepare
    auto curr = vector<TreeNode *>();
    auto prev = vector<TreeNode *>();
    curr.push_back(root);

    // Loop
    auto ans = vector<int>();
    while (!curr.empty()) {
      swap(prev, curr);
      curr.clear();

      ans.push_back(prev.front()->val);
      for (auto node : prev) {
        if (node->right) curr.push_back(node->right);
        if (node->left) curr.push_back(node->left);
      }
    }

    return ans;
  }
};

// DFS (Stack)
class Solution2 {
 public:
  vector<int> rightSideView(TreeNode *root) {
    // Edge case
    if (root == nullptr) return {};

    // Prepare
    auto st = stack<pair<TreeNode *, int>>();  // node, level
    st.push({root, 1});

    // Loop
    auto ans = vector<int>();
    while (!st.empty()) {
      auto [node, level] = st.top();
      st.pop();

      if (ans.size() < level) ans.push_back(node->val);
      if (node->left) st.push({node->left, level + 1});
      if (node->right) st.push({node->right, level + 1});
    }

    return ans;
  }
};
