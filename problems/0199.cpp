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

#include <queue>
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
    // Trivial case
    if (!root) return {};

    // Prepare
    auto next = vector<TreeNode *>();
    auto curr = vector<TreeNode *>();
    curr.push_back(root);

    // Loop
    auto ans = vector<int>();
    while (!curr.empty()) {
      ans.push_back(curr.back()->val);

      next.clear();
      for (TreeNode *node : curr) {
        if (node->left) next.push_back(node->left);
        if (node->right) next.push_back(node->right);
      }
      swap(curr, next);
    }

    return ans;
  }
};

// DFS (Stack)
class Solution2 {
  struct State {
    TreeNode *node;
    int depth;
  };

 public:
  vector<int> rightSideView(TreeNode *root) {
    // Trivial case
    if (!root) return {};

    // Prepare
    auto st = stack<State>();
    st.emplace(root, 0);

    // Loop
    auto ans = vector<int>();
    while (!st.empty()) {
      auto [node, depth] = st.top();
      st.pop();

      if (depth == ans.size()) ans.push_back(node->val);
      if (node->left) st.emplace(node->left, depth + 1);
      if (node->right) st.emplace(node->right, depth + 1);
    }

    return ans;
  }
};
