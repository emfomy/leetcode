// Source: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
// Title: Construct Binary Tree from Inorder and Postorder Traversal
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integer arrays `inorder` and `postorder` where `inorder` is the inorder traversal of a binary tree and `postorder` is the postorder traversal of the same tree, construct and return the binary tree.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/02/19/tree.jpg
//
// ```
// Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
// Output: [3,9,20,null,null,15,7]
// ```
//
// **Example 2:**
//
// ```
// Input: inorder = [-1], postorder = [-1]
// Output: [-1]
// ```
//
// **Constraints:**
//
// - `1 <= inorder.length <= 3000`
// - `postorder.length == inorder.length`
// - `-3000 <= inorder[i], postorder[i] <= 3000`
// - `inorder` and `postorder` consist of **unique** values.
// - Each value of `postorder` also appears in `inorder`.
// - `inorder` is **guaranteed** to be the inorder traversal of the tree.
// - `postorder` is **guaranteed** to be the postorder traversal of the tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iterator>
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

// Use reverse iterator
// in:   [left, root, right]
// post: [left, right, root]
class Solution {
  using Iter = vector<int>::const_reverse_iterator;

 public:
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    return dfs(postorder.crbegin(), inorder.crbegin(), inorder.crend());
  }

 private:
  TreeNode *dfs(Iter postFirst, Iter inFirst, Iter inLast) {
    if (distance(inFirst, inLast) <= 0) return nullptr;

    auto rootVal = *(postFirst++);
    auto inMid = find(inFirst, inLast, rootVal);

    auto rightSize = inMid - inFirst;
    auto right = dfs(postFirst, inFirst, inMid);
    auto left = dfs(postFirst + rightSize, inMid + 1, inLast);

    return new TreeNode(rootVal, left, right);
  }
};

// Use reverse iterator
// in:   [left, root, right]
// post: [left, right, root]
class Solution2 {
  using Iter = vector<int>::const_reverse_iterator;
  using IterMap = unordered_map<int, Iter>;

 public:
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    auto n = postorder.size();
    auto inMap = IterMap();
    for (auto it = inorder.crbegin(); it != inorder.crend(); ++it) {
      inMap[*it] = it;
    }

    return dfs(inMap, postorder.crbegin(), inorder.crbegin(), n);
  }

 private:
  TreeNode *dfs(IterMap &inMap, Iter postFirst, Iter inFirst, int size) {
    if (size <= 0) return nullptr;

    auto rootVal = *postFirst;
    ++postFirst, --size;

    auto inMid = inMap[rootVal];
    auto rightSize = inMid - inFirst;
    auto right = dfs(inMap, postFirst, inFirst, rightSize);
    auto left = dfs(inMap, postFirst + rightSize, inMid + 1, size - rightSize);

    return new TreeNode(rootVal, left, right);
  }
};
