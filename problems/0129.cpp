// Source: https://leetcode.com/problems/sum-root-to-leaf-numbers
// Title: Sum Root to Leaf Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given the `root` of a binary tree containing digits from `0` to `9` only.
//
// Each root-to-leaf path in the tree represents a number.
//
// - For example, the root-to-leaf path `1 -> 2 -> 3` represents the number `123`.
//
// Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer will fit in a **32-bit** integer.
//
// A **leaf** node is a node with no children.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/02/19/num1tree.jpg
//
// ```
// Input: root = [1,2,3]
// Output: 25
// Explanation:
// The root-to-leaf path `1->2` represents the number `12`.
// The root-to-leaf path `1->3` represents the number `13`.
// Therefore, sum = 12 + 13 = `25`.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/02/19/num2tree.jpg
//
// ```
// Input: root = [4,9,0,5,1]
// Output: 1026
// Explanation:
// The root-to-leaf path `4->9->5` represents the number 495.
// The root-to-leaf path `4->9->1` represents the number 491.
// The root-to-leaf path `4->0` represents the number 40.
// Therefore, sum = 495 + 491 + 40 = `1026`.
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 1000]`.
// - `0 <= Node.val <= 9`
// - The depth of the tree will not exceed `10`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <utility>
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

// DFS (Stack)
class Solution {
 public:
  int sumNumbers(TreeNode *root) {
    // Edge case
    if (root == nullptr) return 0;

    // Prepare
    auto pathVal = 0;
    auto st = stack<pair<TreeNode *, bool>>();  // node, seen
    st.push({root, false});

    // Loop
    auto ans = 0;
    while (!st.empty()) {
      auto [node, seen] = st.top();
      st.pop();

      if (seen) {
        pathVal /= 10;
        continue;
      }

      if (node->left == nullptr && node->right == nullptr) {
        ans += pathVal * 10 + node->val;
        continue;
      }

      pathVal = pathVal * 10 + node->val;
      st.push({node, true});
      if (node->right) st.push({node->right, false});
      if (node->left) st.push({node->left, false});
    }

    return ans;
  }
};
