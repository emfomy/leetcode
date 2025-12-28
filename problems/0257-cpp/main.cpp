// Source: https://leetcode.com/problems/binary-tree-paths
// Title: Binary Tree Paths
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return all root-to-leaf paths in **any order**.
//
// A **leaf** is a node with no children.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/03/12/paths-tree.jpg
//
// ```
// Input: root = [1,2,3,null,5]
// Output: ["1->2->5","1->3"]
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1]
// Output: ["1"]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 100]`.
// - `-100 <= Node.val <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <string>
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

// DFS (Recursion)
class Solution {
 public:
  vector<string> binaryTreePaths(TreeNode *root) {
    if (root == nullptr) return {};

    if (root->left == nullptr && root->right == nullptr) {
      return {to_string(root->val)};
    }

    auto paths = vector<string>();
    for (auto path : binaryTreePaths(root->left)) {
      paths.push_back(to_string(root->val) + "->" + path);
    }
    for (auto path : binaryTreePaths(root->right)) {
      paths.push_back(to_string(root->val) + "->" + path);
    }
    return paths;
  }
};

// DFS (Stack)
class Solution2 {
 public:
  vector<string> binaryTreePaths(TreeNode *root) {
    // Edge case
    if (root == nullptr) return {};

    // Prepare
    auto st = stack<pair<TreeNode *, bool>>();  // node, seen
    auto vals = vector<int>();
    st.push({root, false});

    // Loop
    auto ans = vector<string>();
    while (!st.empty()) {
      auto [node, seen] = st.top();
      st.pop();

      // Pop
      if (seen) {
        vals.pop_back();
        continue;
      }

      // Leaf
      if (node->left == nullptr && node->right == nullptr) {
        auto path = to_string(node->val);
        for (auto it = vals.crbegin(); it != vals.crend(); ++it) path = to_string(*it) + "->" + path;
        ans.push_back(path);
        continue;
      }

      // Recursion
      vals.push_back(node->val);
      st.push({node, true});
      if (node->right) st.push({node->right, false});
      if (node->left) st.push({node->left, false});
    }

    return ans;
  }
};
