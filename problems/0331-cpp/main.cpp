// Source: https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree
// Title: Verify Preorder Serialization of a Binary Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// One way to serialize a binary tree is to use **preorder traversal**. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as `'#'`.
//
// https://assets.leetcode.com/uploads/2021/03/12/pre-tree.jpg
//
// For example, the above binary tree can be serialized to the string `"9,3,4,#,#,1,#,#,2,#,6,#,#"`, where `'#'` represents a null node.
//
// Given a string of comma-separated values `preorder`, return `true` if it is a correct preorder traversal serialization of a binary tree.
//
// It is **guaranteed** that each comma-separated value in the string must be either an integer or a character `'#'` representing null pointer.
//
// You may assume that the input format is always valid.
//
// - For example, it could never contain two consecutive commas, such as `"1,,3"`.
//
// **Note:**You are not allowed to reconstruct the tree.
//
// **Example 1:**
//
// ```
// Input: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: preorder = "1,#"
// Output: false
// ```
//
// **Example 3:**
//
// ```
// Input: preorder = "9,#,#,1"
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= preorder.length <= 10^4`
// - `preorder` consist of integers in the range `[0, 100]` and `'#'` separated by commas `','`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Count free edges
class Solution {
 public:
  bool isValidSerialization(string preorder) {
    auto nodes = split(preorder);
    auto edge = 1;  // from dummy root
    for (auto node : nodes) {
      if (edge <= 0) return false;  // no more edge
      --edge;                       // use one edge for this node
      if (node) edge += 2;          // create 2 more edges
    }

    return edge == 0;  // all edges must be used
  }

 private:
  vector<bool> split(const string &s) {
    istringstream iss(s);
    vector<bool> nodes;
    string num;
    while (getline(iss, num, ',')) {
      if (num == "#") {
        nodes.push_back(false);  // null
      } else {
        nodes.push_back(true);  // node
      }
    }
    return nodes;
  }
};
