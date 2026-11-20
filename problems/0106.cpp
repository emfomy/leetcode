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

// Divide and Conquer
//
// inorder:  [left, root,  right]
// preorder: [left, right, root]
class Solution1 {
 public:
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    int n = inorder.size();
    return build(inorder, postorder, n, 0, 0);
  }

  TreeNode *build(vector<int> &inorder, vector<int> &postorder, int size, int inShift, int postShift) {
    if (size == 0) return nullptr;

    auto rootVal = postorder[postShift + size - 1];
    auto leftSize = 0;
    while (inorder[inShift + leftSize] != rootVal) ++leftSize;
    auto rightSize = size - leftSize - 1;

    auto root = new TreeNode(rootVal);
    root->left = build(inorder, postorder, leftSize, inShift, postShift);
    root->right = build(inorder, postorder, rightSize, inShift + leftSize + 1, postShift + leftSize);
    return root;
  }
};

// Divide and Conquer + Reverse iterator
//
// inorder:  [left, root,  right]
// preorder: [left, right, root]
class Solution2 {
  using Iter = vector<int>::const_reverse_iterator;

 public:
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    return build(inorder.crbegin(), inorder.crend(), postorder.crbegin());
  }

  TreeNode *build(Iter inBegin, Iter inEnd, Iter postBegin) {
    if (distance(inBegin, inEnd) <= 0) return nullptr;

    auto rootVal = *postBegin;
    auto inMid = find(inBegin, inEnd, rootVal);  // root at inorder
    auto rightSize = distance(inBegin, inMid);

    auto root = new TreeNode(rootVal);
    root->right = build(inBegin, inMid, postBegin + 1);
    root->left = build(inMid + 1, inEnd, postBegin + 1 + rightSize);
    return root;
  }
};

// Divide and Conquer + Reverse iterator + Index map
//
// inorder:  [left, root,  right]
// preorder: [left, right, root]
//
// Instead of find root at inorder each time, we find the mapping at first
class Solution3 {
  using Iter = vector<int>::const_reverse_iterator;
  using IterMap = unordered_map<int, Iter>;

 public:
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    auto inMap = IterMap();
    for (auto it = inorder.crbegin(); it != inorder.crend(); ++it) {
      inMap[*it] = it;
    }

    return build(inorder.crbegin(), inorder.crend(), postorder.crbegin(), inMap);
  }

  TreeNode *build(Iter inBegin, Iter inEnd, Iter postBegin, IterMap &inMap) {
    if (distance(inBegin, inEnd) <= 0) return nullptr;

    auto rootVal = *postBegin;
    auto inMid = inMap[rootVal];
    auto rightSize = distance(inBegin, inMid);

    auto root = new TreeNode(rootVal);
    root->right = build(inBegin, inMid, postBegin + 1, inMap);
    root->left = build(inMid + 1, inEnd, postBegin + 1 + rightSize, inMap);
    return root;
  }
};
