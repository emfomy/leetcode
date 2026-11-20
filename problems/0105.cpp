// Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal
// Title: Construct Binary Tree from Preorder and Inorder Traversal
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integer arrays `preorder` and `inorder` where `preorder` is the preorder traversal of a binary tree and `inorder` is the inorder traversal of the same tree, construct and return the binary tree.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/02/19/tree.jpg
//
// ```
// Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// Output: [3,9,20,null,null,15,7]
// ```
//
// **Example 2:**
//
// ```
// Input: preorder = [-1], inorder = [-1]
// Output: [-1]
// ```
//
// **Constraints:**
//
// - `1 <= preorder.length <= 3000`
// - `inorder.length == preorder.length`
// - `-3000 <= preorder[i], inorder[i] <= 3000`
// - `preorder` and `inorder` consist of **unique** values.
// - Each value of `inorder` also appears in `preorder`.
// - `preorder` is **guaranteed** to be the preorder traversal of the tree.
// - `inorder` is **guaranteed** to be the inorder traversal of the tree.
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

// pre: [root, left, right]
// in:  [left, root, right]
class Solution {
  using Iter = vector<int>::const_iterator;

 public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    return dfs(preorder.cbegin(), inorder.cbegin(), inorder.cend());
  }

 private:
  TreeNode *dfs(Iter preFirst, Iter inFirst, Iter inLast) {
    if (distance(inFirst, inLast) <= 0) return nullptr;

    auto rootVal = *(preFirst++);
    auto inMid = find(inFirst, inLast, rootVal);

    auto leftSize = inMid - inFirst;
    auto left = dfs(preFirst, inFirst, inMid);
    auto right = dfs(preFirst + leftSize, inMid + 1, inLast);

    return new TreeNode(rootVal, left, right);
  }
};

// pre: [root, left, right]
// in:  [left, root, right]
class Solution2 {
  using Iter = vector<int>::const_iterator;
  using IterMap = unordered_map<int, Iter>;

 public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    auto n = preorder.size();
    auto inMap = IterMap();
    for (auto it = inorder.cbegin(); it != inorder.cend(); ++it) {
      inMap[*it] = it;
    }

    return dfs(inMap, preorder.cbegin(), inorder.cbegin(), n);
  }

 private:
  TreeNode *dfs(IterMap &inMap, Iter preFirst, Iter inFirst, int size) {
    if (size <= 0) return nullptr;

    auto rootVal = *preFirst;
    ++preFirst, --size;

    auto inMid = inMap[rootVal];
    auto leftSize = inMid - inFirst;
    auto left = dfs(inMap, preFirst, inFirst, leftSize);
    auto right = dfs(inMap, preFirst + leftSize, inMid + 1, size - leftSize);

    return new TreeNode(rootVal, left, right);
  }
};
