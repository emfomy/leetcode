// Source: https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers
// Title: Sum of Root To Leaf Binary Numbers
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the `root` of a binary tree where each node has a value `0` or `1`. Each root-to-leaf path represents a binary number starting with the most significant bit.
//
// - For example, if the path is `0 -> 1 -> 1 -> 0 -> 1`, then this could represent `01101` in binary, which is `13`.
//
// For all leaves in the tree, consider the numbers represented by the path from the root to that leaf. Return the sum of these numbers.
//
// The test cases are generated so that the answer fits in a **32-bits** integer.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/04/04/sum-of-root-to-leaf-binary-numbers.png
//
// ```
// Input: root = [1,0,1,0,1,0,1]
// Output: 22
// Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
// ```
//
// **Example 2:**
//
// ```
// Input: root = [0]
// Output: 0
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 1000]`.
// - `Node.val` is `0` or `1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <string>
#include <string_view>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// DFS, Recursion
class Solution {
 public:
  int sumRootToLeaf(TreeNode *root) {
    // Guard
    if (!root) return 0;

    // DFS
    int sum = 0;
    dfs(root, 0, sum);

    return sum;
  }

 private:
  void dfs(TreeNode *node, int num, int &sum) {
    // Shift
    num = (num << 1) + node->val;

    // Leaf Node
    if (!node->left && !node->right) {
      sum += num;
      return;
    }

    if (node->left) {
      dfs(node->left, num, sum);
    }

    if (node->right) {
      dfs(node->right, num, sum);
    }
  }
};

// DFS, Iteration
class Solution2 {
  struct State {
    TreeNode *node;
    int num;
  };

 public:
  int sumRootToLeaf(TreeNode *root) {
    // Guard
    if (!root) return 0;

    // Prepare
    int sum = 0;
    auto st = stack<State>();
    st.push({root, 0});

    // DFS
    while (!st.empty()) {
      auto [node, num] = st.top();
      st.pop();

      // Shift
      num = (num << 1) + node->val;

      // Leaf Node
      if (!node->left && !node->right) {
        sum += num;
        continue;
      }

      if (node->left) st.push({node->left, num});
      if (node->right) st.push({node->right, num});
    }

    return sum;
  }
};
