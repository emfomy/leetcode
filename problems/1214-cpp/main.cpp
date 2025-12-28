// Source: https://leetcode.com/problems/two-sum-bsts
// Title: Two Sum BSTs
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the roots of two binary search trees, `root1` and `root2`, return `true` if and only if there is a node in the first tree and a node in the second tree whose values sum up to a given integer `target`.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2021/02/10/ex1.png
//
// ```
// Input: root1 = [2,1,4], root2 = [1,0,3], target = 5
// Output: true
// Explanation: 2 and 3 sum up to 5.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2021/02/10/ex2.png
//
// ```
// Input: root1 = [0,-10,10], root2 = [5,1,7,0,2], target = 18
// Output: false
// ```
//
// **Constraints:**
//
// - The number of nodes in each tree is in the range `[1, 5000]`.
// - `-10^9 <= Node.val, target <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <iterator>
#include <stack>
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

// Hash Set + DFS
class Solution {
 public:
  bool twoSumBSTs(TreeNode *root1, TreeNode *root2, int target) {
    auto numSet = unordered_set<int>();  // numbers in root1
    auto st = stack<TreeNode *>();

    // Pre-order tree 1
    st.push(root1);
    while (!st.empty()) {
      auto node = st.top();
      st.pop();
      numSet.insert(node->val);
      if (node->right) st.push(node->right);
      if (node->left) st.push(node->left);
    }

    // Pre-order tree 2
    st.push(root2);
    while (!st.empty()) {
      auto node = st.top();
      st.pop();
      if (numSet.contains(target - node->val)) return true;
      if (node->right) st.push(node->right);
      if (node->left) st.push(node->left);
    }

    return false;
  }
};

// Two pointer + DFS
//
// Loop from small to right in tree 1, from right to left in tree 2.
class Solution2 {
 public:
  bool twoSumBSTs(TreeNode *root1, TreeNode *root2, int target) {
    auto st1 = stack<TreeNode *>();
    auto st2 = stack<TreeNode *>();

    // Get next node from tree 1
    auto get1 = [&]() -> int {
      int ret = INT_MAX;
      if (root1 || !st1.empty()) {
        // Go left
        while (root1) {
          st1.push(root1);
          root1 = root1->left;
        }

        // Pop left most
        root1 = st1.top();
        st1.pop();
        ret = root1->val;
        root1 = root1->right;
      }
      return ret;
    };

    // Get next node from tree 1
    auto get2 = [&]() -> int {
      int ret = INT_MAX;
      if (root2 || !st2.empty()) {
        // Go right
        while (root2) {
          st2.push(root2);
          root2 = root2->right;
        }

        // Pop right most
        root2 = st2.top();
        st2.pop();
        ret = root2->val;
        root2 = root2->left;
      }
      return ret;
    };

    // Two pointer
    auto val1 = get1(), val2 = get2();
    while (val1 != INT_MAX && val2 != INT_MAX) {
      printf("%d, %d\n", val1, val2);
      auto sum = val1 + val2;
      if (sum == target) return true;

      if (sum < target) {
        val1 = get1();
      } else {
        val2 = get2();
      }
    }
    return false;
  }
};
