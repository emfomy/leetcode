// Source: https://leetcode.com/problems/binary-tree-inorder-traversal
// Title: Binary Tree Inorder Traversal
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return the inorder traversal of its nodes' values.
//
// **Example 1:**
//
// ```
// Input: root = [1,null,2,3]
// Output: [1,3,2]
// Explanation:
// https://assets.leetcode.com/uploads/2024/08/29/screenshot-2024-08-29-202743.png
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
// Output: [4,2,6,5,7,1,3,9,8]
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
// - The number of nodes in the tree is in the range `[0, 100]`.
// - `-100 <= Node.val <= 100`
//
// **Follow up:** Recursive solution is trivial, could you do it iteratively?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
  vector<int> inorderTraversal(TreeNode *root) {
    auto ans = vector<int>();
    _preorder(root, ans);
    return ans;
  }

 private:
  void _preorder(TreeNode *node, vector<int> &ans) {
    if (!node) return;
    _preorder(node->left, ans);
    ans.push_back(node->val);
    _preorder(node->right, ans);
  }
};

// Use DFS (Stack)
class Solution2 {
 public:
  vector<int> inorderTraversal(TreeNode *root) {
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
          ans.push_back(item.first->val);
          if (item.first->right) st.push({item.first->right, 0});
          break;
        }
        case 2: {  // post
          st.pop();
          break;
        }
      }
    }

    return ans;
  }
};
