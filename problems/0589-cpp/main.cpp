// Source: https://leetcode.com/problems/n-ary-tree-preorder-traversal
// Title: N-ary Tree Preorder Traversal
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of an n-ary tree, return the preorder traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png
//
// ```
// Input: root = [1,null,3,2,4,null,5,6]
// Output: [1,3,5,6,2,4]
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2019/11/08/sample_4_964.png
//
// ```
// Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
// Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[0, 10^4]`.
// - `0 <= Node.val <= 10^4`
// - The height of the n-ary tree is less than or equal to `1000`.
//
// **Follow up:** Recursive solution is trivial, could you do it iteratively?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <stack>
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

// Use DFS (Recursion)
class Solution {
 public:
  vector<int> preorder(Node* root) {
    auto ans = vector<int>();
    _preorder(root, ans);
    return ans;
  }

 private:
  void _preorder(Node* node, vector<int>& ans) {
    if (!node) return;
    ans.push_back(node->val);
    for (auto child : node->children) _preorder(child, ans);
  }
};

// Use DFS (Stack)
class Solution2 {
 public:
  vector<int> preorder(Node* root) {
    if (!root) return {};

    auto ans = vector<int>();
    auto st = stack<Node*>();
    st.push(root);

    while (!st.empty()) {
      auto node = st.top();
      st.pop();
      ans.push_back(node->val);
      for (auto it = node->children.crbegin(); it != node->children.crend(); ++it) st.push(*it);
    }

    return ans;
  }
};
