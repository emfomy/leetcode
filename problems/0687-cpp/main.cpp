// Source: https://leetcode.com/problems/longest-univalue-path
// Title: Longest Univalue Path
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return the length of the longest path, where each node in the path has the same value. This path may or may not pass through the root.
//
// **The length of the path** between two nodes is represented by the number of edges between them.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/10/13/ex1.jpg
//
// ```
// Input: root = [5,4,5,1,1,null,5]
// Output: 2
// Explanation: The shown image shows that the longest path of the same value (i.e. 5).
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/10/13/ex2.jpg
//
// ```
// Input: root = [1,4,5,4,4,null,5]
// Output: 2
// Explanation: The shown image shows that the longest path of the same value (i.e. 4).
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 10^4]`.
// - `-1000 <= Node.val <= 1000`
// - The depth of the tree will not exceed `1000`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
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
//
// Each node has three edges (to parent, to left child, to right child).
// A path should pass two of these three edges.
class Solution {
 public:
  int longestUnivaluePath(const TreeNode *root) {
    int ans = 0;
    dfs(root, ans);

    return ans;
  }

 private:
  //  returns child value and node count
  pair<int, int> dfs(const TreeNode *node, int &ans) {
    if (!node) return {0, 0};

    auto [leftVal, leftCount] = dfs(node->left, ans);
    auto [rightVal, rightCount] = dfs(node->right, ans);
    if (node->val != leftVal) leftCount = 0;
    if (node->val != rightVal) rightCount = 0;

    // Path: Left + Right
    ans = max(ans, leftCount + rightCount);

    // Path: (Left or Right) + Parent
    return {node->val, max(leftCount, rightCount) + 1};
  }
};

// DFS
//
// Each node has three edges (to parent, to left child, to right child).
// A path should pass two of these three edges.
class Solution2 {
 public:
  int longestUnivaluePath(const TreeNode *root) {
    // Guard
    if (!root) return 0;

    int ans = 0;
    dfs(root, ans);

    return ans;
  }

 private:
  // `node` must be non-nil, returns current length
  int dfs(const TreeNode *node, int &ans) {
    int leftCount = 0, rightCount = 0;

    if (node->left) {
      int count = dfs(node->left, ans);
      if (node->val == node->left->val) leftCount = count;
    }

    if (node->right) {
      int count = dfs(node->right, ans);
      if (node->val == node->right->val) rightCount = count;
    }

    // Path: Left + Right
    ans = max(ans, leftCount + rightCount);

    // Path: (Left or Right) + Parent
    return max(leftCount, rightCount) + 1;
  }
};
