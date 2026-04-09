// Source: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree
// Title: All Nodes Distance K in Binary Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary tree, the value of a target node `target`, and an integer `k`, return an array of the values of all nodes that have a distance `k` from the target node.
//
// You can return the answer in **any order**.
//
// **Example 1:**
// https://s3-lc-upload.s3.amazonaws.com/uploads/2018/06/28/sketch0.png
//
// ```
// Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
// Output: [7,4,1]
// Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.
// ```
//
// **Example 2:**
//
// ```
// Input: root = [1], target = 1, k = 3
// Output: []
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 500]`.
// - `0 <= Node.val <= 500`
// - All the values `Node.val` are **unique**.
// - `target` is the value of one of the nodes in the tree.
// - `0 <= k <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <unordered_map>
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

// BFS + Hash Map
//
// First loop for all nodes to create inverse edge.
//
// Next run BFS on target.
class Solution {
 public:
  vector<int> distanceK(TreeNode *root, TreeNode *target, int k) {
    // Trivial case
    if (!root || !target) return {};

    // Prepare graph
    auto parents = unordered_map<TreeNode *, TreeNode *>();

    // BFS on root
    auto que = queue<TreeNode *>();
    que.push(root);
    parents[root] = nullptr;
    while (!que.empty()) {
      TreeNode *node = que.front();
      que.pop();

      // Traversal
      if (node->left) {
        que.push(node->left);
        parents[node->left] = node;
      }
      if (node->right) {
        que.push(node->right);
        parents[node->right] = node;
      }
    }

    // BFS on target
    auto prev = vector<TreeNode *>();
    auto curr = vector<TreeNode *>();
    auto visited = unordered_set<TreeNode *>();
    visited.insert(nullptr);
    curr.push_back(target);
    for (int i = 0; i < k; ++i) {
      if (curr.empty()) break;

      swap(curr, prev);
      curr.clear();

      for (TreeNode *node : prev) {
        visited.insert(node);

        if (!visited.contains(node->left)) curr.push_back(node->left);
        if (!visited.contains(node->right)) curr.push_back(node->right);
        if (!visited.contains(parents[node])) curr.push_back(parents[node]);
      }
    }

    // Answer
    auto ans = vector<int>();
    ans.reserve(curr.size());
    for (TreeNode *node : curr) {
      ans.push_back(node->val);
    }

    return ans;
  }
};
