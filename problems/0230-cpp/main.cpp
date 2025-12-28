// Source: https://leetcode.com/problems/kth-smallest-element-in-a-bst
// Title: Kth Smallest Element in a BST
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary search tree, and an integer `k`, return the `k^th` smallest value (**1-indexed**) of all the values of the nodes in the tree.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/28/kthtree1.jpg
//
// ```
// Input: root = [3,1,4,null,2], k = 1
// Output: 1
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/01/28/kthtree2.jpg
//
// ```
// Input: root = [5,3,6,2,4,null,null,1], k = 3
// Output: 3
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is `n`.
// - `1 <= k <= n <= 10^4`
// - `0 <= Node.val <= 10^4`
//
// **Follow up:** If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Stack + State
//
// Traverse
class Solution {
 public:
  int kthSmallest(TreeNode *root, int k) {
    // Prepare
    auto st = stack<pair<TreeNode *, bool>>();  // node, seen
    st.push({root, false});

    int ans = 0;
    while (k > 0) {
      auto [node, seen] = st.top();
      st.pop();

      if (node == nullptr) continue;
      if (seen) {
        ans = node->val;
        --k;
      } else {
        st.push({node->right, false});
        st.push({node, true});
        st.push({node->left, false});
      }
    }

    return ans;
  }
};
