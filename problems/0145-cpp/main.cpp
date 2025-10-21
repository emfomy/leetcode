// Source: https://leetcode.com/problems/binary-tree-postorder-traversal
// Title: Binary Tree Postorder Traversal
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of abinary tree, return the postorder traversal of its nodes' values.
//
// **Example 1:**
//
// ```
// Input: root = [1,null,2,3]
// Output: [3,2,1]
// Explanation:
// https://assets.leetcode.com/uploads/2024/08/29/screenshot-2024-08-29-202743.png
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
// Output: [4,6,7,5,2,9,8,3,1]
// Explanation:
// https://assets.leetcode.com/uploads/2024/08/29/tree_2.png
// ```
//
// **Example 3:**
//
// ```
// Input: root = []
// Output: []
// ```
//
// **Example 4:**
//
// ```
// Input: root = [1]
// Output: [1]
// ```
//
// **Constraints:**
//
// - The number of the nodes in the tree is in the range `[0, 100]`.
// - `-100 <= Node.val <= 100`
//
// **Follow up:** Recursive solution is trivial, could you do it iteratively?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <stack>
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

// Use DFS (Recursion)
class Solution {
 public:
  vector<int> postorderTraversal(TreeNode *root) {
    auto ans = vector<int>();
    _preorder(root, ans);
    return ans;
  }

 private:
  void _preorder(TreeNode *node, vector<int> &ans) {
    if (!node) return;
    _preorder(node->left, ans);
    _preorder(node->right, ans);
    ans.push_back(node->val);
  }
};

// Use DFS (Stack)
//
// Do preorder from right to left ans then reverse the result
class Solution2 {
 public:
  vector<int> postorderTraversal(TreeNode *root) {
    if (!root) return {};

    auto ans = vector<int>();
    auto st = stack<TreeNode *>();
    st.push(root);

    while (!st.empty()) {
      auto node = st.top();
      st.pop();
      ans.push_back(node->val);
      if (node->left) st.push(node->left);
      if (node->right) st.push(node->right);
    }

    reverse(ans.begin(), ans.end());
    return ans;
  }
};

// Use DFS (Stack)
class Solution3 {
 public:
  vector<int> postorderTraversal(TreeNode *root) {
    if (!root) return {};

    auto ans = vector<int>();
    auto st = stack<pair<TreeNode *, int>>();  // (node, pre/in/post)
    st.push({root, 0});

    while (!st.empty()) {
      auto &item = st.top();
      switch (item.second) {
        case 0: {  // pre
          ++item.second;
          if (item.first->left) st.push({item.first->left, 0});
          break;
        }
        case 1: {  // in
          ++item.second;
          if (item.first->right) st.push({item.first->right, 0});
          break;
        }
        case 2: {  // post
          ans.push_back(item.first->val);
          st.pop();
          break;
        }
      }
    }

    return ans;
  }
};
