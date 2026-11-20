// Source: https://leetcode.com/problems/n-ary-tree-level-order-traversal
// Title: N-ary Tree Level Order Traversal
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an n-ary tree, return the level order traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png
//
// ```
// Input: root = [1,null,3,2,4,null,5,6]
// Output: [[1],[3,2,4],[5,6]]
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2019/11/08/sample_4_964.png
//
// ```
// Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
// Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]
// ```
//
// **Constraints:**
//
// - The height of the n-ary tree is less than or equal to `1000`
// - The total number of nodes is between `[0, 10^4]`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

class Node {
 public:
  int val;
  vector<Node*> children;

  Node() {}
  Node(int val) : val(val) {}
  Node(int val, vector<Node*> children) : val(val), children(children) {}
};

// Use BFS (Queue)
class Solution {
 public:
  vector<vector<int>> levelOrder(Node* root) {
    if (!root) return {};

    auto ans = vector<vector<int>>();
    auto curr = queue<Node*>();
    auto next = queue<Node*>();
    curr.push(root);

    while (!curr.empty()) {
      auto currAns = vector<int>();
      while (!curr.empty()) {
        auto node = curr.front();
        curr.pop();
        currAns.push_back(node->val);
        for (auto child : node->children) next.push(child);
      }
      ans.push_back(currAns);
      swap(curr, next);
    }

    return ans;
  }
};

// Use BFS (Single Queue)
class Solution2 {
 public:
  vector<vector<int>> levelOrder(Node* root) {
    if (!root) return {};

    auto ans = vector<vector<int>>();
    auto que = queue<Node*>();
    que.push(root);

    while (!que.empty()) {
      auto currAns = vector<int>();
      int size = que.size();
      for (auto i = 0; i < size; ++i) {
        auto node = que.front();
        que.pop();
        currAns.push_back(node->val);
        for (auto child : node->children) que.push(child);
      }
      ans.push_back(currAns);
    }

    return ans;
  }
};
