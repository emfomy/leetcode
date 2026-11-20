// Source: https://leetcode.com/problems/delete-nodes-and-return-forest
// Title: Delete Nodes And Return Forest
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, each node in the tree has a distinct value.
//
// After deleting all nodes with a value in `to_delete`, we are left with a forest (a disjoint union of trees).
//
// Return the roots of the trees in the remaining forest. You may return the result in any order.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/07/01/screen-shot-2019-07-01-at-53836-pm.png
//
// ```
// Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
// Output: [[1,2,null,4],[6],[7]]
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1,2,4,null,3], to_delete = [3]
// Output: [[1,2,4]]
// ```
//
// **Constraints:**
//
// - The number of nodes in the given tree is at most `1000`.
// - Each node has a distinct value between `1` and `1000`.
// - `to_delete.length <= 1000`
// - `to_delete` contains distinct values between `1` and `1000`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_set>
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

// Hash Set + DFS
//
// First convert toDelete into a hash set.
// Next do DFS on the tree.
// If a node it deleteing, tell its children to put themself into the forest
class Solution {
 public:
  vector<TreeNode *> delNodes(TreeNode *root, const vector<int> &toDelete) {
    // Trivial case
    if (toDelete.empty()) return {root};

    // Prepare data
    auto deleteSet = unordered_set<int>(toDelete.cbegin(), toDelete.cend());
    auto forest = vector<TreeNode *>();

    // DFS
    dfs(root, true, deleteSet, forest);

    return forest;
  }

 private:
  // Returns updated node
  TreeNode *dfs(TreeNode *node, bool parentDeleted, const unordered_set<int> &deleteSet, vector<TreeNode *> &forest) {
    // Empty node
    if (!node) return nullptr;

    // Delete current node
    bool currentDeleted = deleteSet.contains(node->val);

    // Traversal
    node->left = dfs(node->left, currentDeleted, deleteSet, forest);
    node->right = dfs(node->right, currentDeleted, deleteSet, forest);

    // Delete node
    if (currentDeleted) {
      delete node;
      return nullptr;
    }

    // Put into forest
    if (parentDeleted) {
      forest.push_back(node);
    }

    return node;
  }
};

// Hash Set + DFS
//
// First convert toDelete into a hash set.
// Next do post-order DFS on the tree.
// If a node is deleting, then put its non-nil children into the forest
class Solution2 {
 public:
  vector<TreeNode *> delNodes(TreeNode *root, vector<int> &toDelete) {
    // Trivial case
    if (toDelete.empty()) return {root};

    // Prepare data
    auto deleteSet = unordered_set<int>(toDelete.cbegin(), toDelete.cend());
    auto forest = vector<TreeNode *>();

    // DFS and check root node
    if (dfs(root, deleteSet, forest)) {
      forest.push_back(root);
    }

    return forest;
  }

 private:
  // Returns updated node
  TreeNode *dfs(TreeNode *node, const unordered_set<int> &deleteSet, vector<TreeNode *> &forest) {
    // Empty node
    if (!node) return nullptr;

    // Traversal
    node->left = dfs(node->left, deleteSet, forest);
    node->right = dfs(node->right, deleteSet, forest);

    // Delete node
    if (deleteSet.contains(node->val)) {
      if (node->left) forest.push_back(node->left);
      if (node->right) forest.push_back(node->right);
      delete node;
      return nullptr;
    }

    return node;
  }
};
