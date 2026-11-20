// Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal
// Title: Construct Binary Tree from Preorder and Postorder Traversal
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integer arrays, `preorder` and `postorder` where `preorder` is the preorder traversal of a binary tree of **distinct** values and `postorder` is the postorder traversal of the same tree, reconstruct and return the binary tree.
//
// If there exist multiple answers, you can **return any** of them.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/07/24/lc-prepost.jpg
//
// ```
// Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
// Output: [1,2,3,4,5,6,7]
// ```
//
// **Example 2:**
//
// ```
// Input: preorder = [1], postorder = [1]
// Output: [1]
// ```
//
// **Constraints:**
//
// - `1 <= preorder.length <= 30`
// - `1 <= preorder[i] <= preorder.length`
// - All the values of `preorder` are **unique**.
// - `postorder.length == preorder.length`
// - `1 <= postorder[i] <= postorder.length`
// - All the values of `postorder` are **unique**.
// - It is guaranteed that `preorder` and `postorder` are the preorder traversal and postorder traversal of the same binary tree.
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

// pre:  [root, left, right]
// post: [left, right, root]
class Solution {
  using Iter = vector<int>::const_iterator;
  using RIter = vector<int>::const_reverse_iterator;

 public:
  TreeNode *constructFromPrePost(vector<int> &preorder, vector<int> &postorder) {
    return dfs(preorder.cbegin(), postorder.crbegin(), preorder.size());
  }

 private:
  TreeNode *dfs(Iter preFirst, RIter postFirst, int size) {
    if (size == 0) return nullptr;
    if (size == 1) return new TreeNode(*preFirst);

    auto rootVal = *preFirst;
    ++preFirst, ++postFirst, --size;

    // Find right child root in pre-order
    auto preMid = find(preFirst, preFirst + size, *postFirst);

    // Traverse
    auto leftSize = preMid - preFirst;
    auto rightSize = size - leftSize;
    auto left = dfs(preFirst, postFirst + rightSize, leftSize);
    auto right = dfs(preFirst + leftSize, postFirst, rightSize);

    return new TreeNode(rootVal, left, right);
  }
};

// pre:  [root, left root, left, right root, right]
// post: [left, left root, right, right root, root]
class Solution2 {
  using Iter = vector<int>::const_iterator;
  using RIter = vector<int>::const_reverse_iterator;
  using IterMap = unordered_map<int, Iter>;

 public:
  TreeNode *constructFromPrePost(vector<int> &preorder, vector<int> &postorder) {
    auto n = preorder.size();

    auto preMap = IterMap();
    for (auto it = preorder.cbegin(); it != preorder.cend(); ++it) {
      preMap[*it] = it;
    }

    return dfs(preMap, preorder.cbegin(), postorder.crbegin(), n);
  }

 private:
  TreeNode *dfs(IterMap &preMap, Iter preFirst, RIter postFirst, int size) {
    if (size == 0) return nullptr;
    if (size == 1) return new TreeNode(*preFirst);

    auto rootVal = *preFirst;
    ++preFirst, ++postFirst, --size;

    // Find right child root in pre-order
    auto preMid = preMap[*postFirst];

    // Traverse
    auto leftSize = preMid - preFirst;
    auto rightSize = size - leftSize;
    auto left = dfs(preMap, preFirst, postFirst + rightSize, leftSize);
    auto right = dfs(preMap, preFirst + leftSize, postFirst, rightSize);

    return new TreeNode(rootVal, left, right);
  }
};
