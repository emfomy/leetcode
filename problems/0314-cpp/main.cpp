// Source: https://leetcode.com/problems/binary-tree-vertical-order-traversal
// Title: Binary Tree Vertical Order Traversal
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, return **the vertical order traversal** of its nodes' values. (i.e., from top to bottom, column by column).
//
// If two nodes are in the same row and column, the order should be from **left to right**.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2024/09/23/image1.png
//
// ```
// Input: root = [3,9,20,null,null,15,7]
// Output: [[9],[3,15],[20],[7]]
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2024/09/23/image3.png
//
// ```
// Input: root = [3,9,8,4,0,1,7]
// Output: [[4],[9],[3,0,1],[8],[7]]
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2024/09/23/image2.png
//
// ```
// Input: root = [1,2,3,4,10,9,11,null,5,null,null,null,null,null,null,null,6]
// Output: [[4],[2,5],[1,10,9,6],[3],[11]]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 100]`.
// - `-100 <= Node.val <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <unordered_map>
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

// Use BFS + Hash Map
class Solution {
 public:
  vector<vector<int>> verticalOrder(TreeNode *root) {
    unordered_map<int, vector<int>> colMap;
    queue<pair<TreeNode *, int>> bfsQueue;  // (node, col)

    // BFS
    auto minCol = 0;
    auto maxCol = 0;
    bfsQueue.emplace(root, 0);
    while (bfsQueue.size()) {
      auto [node, col] = bfsQueue.front();
      bfsQueue.pop();

      if (node == nullptr) {
        continue;
      }

      minCol = min(minCol, col);
      maxCol = max(maxCol, col);
      colMap[col].push_back(node->val);

      bfsQueue.emplace(node->left, col - 1);
      bfsQueue.emplace(node->right, col + 1);
    }

    // Sort column
    vector<vector<int>> ans;
    ans.reserve(maxCol - minCol + 1);
    for (auto col = minCol; col <= maxCol; col++) {
      ans.push_back(colMap[col]);
    }

    return ans;
  }
};

// Use BFS
// Use vector as queue to get rid of hash map
class Solution2 {
 public:
  vector<vector<int>> verticalOrder(TreeNode *root) {
    if (root == nullptr) {
      return {};
    }

    // BFS
    auto minCol = 0;
    auto maxCol = 0;
    vector<pair<TreeNode *, int>> queue;  // (node, col)
    queue.emplace_back(root, 0);
    for (auto i = 0; i < queue.size(); i++) {
      auto [node, col] = queue[i];
      minCol = min(minCol, col);
      maxCol = max(maxCol, col);
      if (node->left != nullptr) queue.emplace_back(node->left, col - 1);
      if (node->right != nullptr) queue.emplace_back(node->right, col + 1);
    }

    // Sort column
    vector<vector<int>> ans(maxCol - minCol + 1);
    for (auto [node, col] : queue) {
      ans[col - minCol].push_back(node->val);
    }

    return ans;
  }
};
