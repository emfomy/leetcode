// Source: https://leetcode.com/problems/balance-a-binary-search-tree
// Title: Balance a Binary Search Tree
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the `root` of a binary search tree, return a **balanced** binary search tree with the same node values. If there is more than one answer, return **any of them**.
//
// A binary search tree is **balanced** if the depth of the two subtrees of every node never differs by more than `1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/08/10/balance1-tree.jpg
//
// ```
// Input: root = [1,null,2,null,3,null,4,null,null]
// Output: [2,1,3,null,null,null,4]
// Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/08/10/balanced2-tree.jpg
//
// ```
// Input: root = [2,1,3]
// Output: [2,1,3]
// ```
//
// **Constraints:**
//
// - The number of nodes in the tree is in the range `[1, 10^4]`.
// - `1 <= Node.val <= 10^5`
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

// DFS + Divide & Conquer
//
// First convert to array.
// Next build the BST.
class Solution {
  // Convert BST to array of node; Inorder DFS.
  void bst2arr(TreeNode *root, vector<TreeNode *> &nodes) {
    if (root == nullptr) return;

    // DFS
    bst2arr(root->left, nodes);
    nodes.push_back(root);
    bst2arr(root->right, nodes);
  }

  // Build balanced BST from array; Divide and Conquer.
  TreeNode *arr2bst(vector<TreeNode *> &nodes, int start, int end) {
    if (start >= end) return nullptr;

    int mid = start + (end - start) / 2;
    auto root = nodes[mid];
    root->left = arr2bst(nodes, start, mid);
    root->right = arr2bst(nodes, mid + 1, end);
    return root;
  }

 public:
  TreeNode *balanceBST(TreeNode *root) {
    if (root == nullptr) return nullptr;

    auto nodes = vector<TreeNode *>();
    bst2arr(root, nodes);
    return arr2bst(nodes, 0, nodes.size());
  }
};

// DFS + Divide & Conquer
//
// First convert to linked list.
// Next build the BST.
class Solution2 {
  struct ListWriter {
    int size;
    TreeNode dummy;
    TreeNode *tail;

    ListWriter() : size(0), dummy(), tail(&dummy) {}

    TreeNode *head() { return dummy.right; }

    void push(TreeNode *node) {
      ++size;
      tail->right = node;
      tail = tail->right;
    }
  };

  struct ListReader {
    TreeNode *head;

    ListReader(TreeNode *head) : head(head) {}

    TreeNode *pop() {
      if (head == nullptr) return nullptr;

      auto node = head;
      head = head->right;
      return node;
    }
  };

  // Convert BST to linked list; Inorder DFS.
  void bst2list(TreeNode *root, ListWriter &writer) {
    if (root == nullptr) return;

    // DFS
    bst2list(root->left, writer);
    writer.push(root);
    bst2list(root->right, writer);
  }

  // Build balanced BST from list; Divide and Conquer.
  TreeNode *list2bst(int size, ListReader &reader) {
    if (size <= 0) return nullptr;

    int leftSize = size / 2;
    int rightSize = size - leftSize - 1;

    TreeNode *left = list2bst(leftSize, reader);
    TreeNode *root = reader.pop();
    TreeNode *right = list2bst(rightSize, reader);

    root->left = left;
    root->right = right;
    return root;
  }

 public:
  TreeNode *balanceBST(TreeNode *root) {
    if (root == nullptr) return nullptr;

    auto writer = ListWriter();
    bst2list(root, writer);

    auto reader = ListReader(writer.head());
    return list2bst(writer.size, reader);
  }
};
