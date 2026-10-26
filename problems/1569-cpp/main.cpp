// Source: https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst
// Title: Number of Ways to Reorder Array to Get Same BST
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array `nums` that represents a permutation of integers from `1` to `n`. We are going to construct a binary search tree (BST) by inserting the elements of `nums` in order into an initially empty BST. Find the number of different ways to reorder `nums` so that the constructed BST is identical to that formed from the original array `nums`.
//
// - For example, given `nums = [2,1,3]`, we will have 2 as the root, 1 as a left child, and 3 as a right child. The array `[2,3,1]` also yields the same BST but `[3,2,1]` yields a different BST.
//
// Return the number of ways to reorder `nums` such that the BST formed is identical to the original BST formed from `nums`.
//
// Since the answer may be very large, **return it modulo **`10^9 + 7`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2026/02/23/1569_ex0.png
//
// ```
// Input: nums = [2,1,3]
// Output: 1
// Explanation: We can reorder nums to be [2,3,1] which will yield the same BST. There are no other ways to reorder nums which will yield the same BST.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2026/02/23/1569_ex.png
//
// ```
// Input: nums = [3,4,5,1,2]
// Output: 5
// Explanation: The following 5 arrays will yield the same BST:
// [3,1,2,4,5]
// [3,1,4,2,5]
// [3,1,4,5,2]
// [3,4,1,2,5]
// [3,4,1,5,2]
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2026/02/23/1569_ex2.png
//
// ```
// Input: nums = [1,2,3]
// Output: 0
// Explanation: There are no other orderings of nums that will yield the same BST.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1000`
// - `1 <= nums[i] <= nums.length`
// - All integers in `nums` are **distinct**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

// Divide and Conquer
//
// The first element (root) is fixed.
//
// Next we divide the problem into left and right subtree.
// The order in left tree doesn't effect the right tree.
//
// Say there are L ways for left tree, and R ways for right tree.
// The size of left is l, the size of right is r.
// The total ways are L * R * C(l+r, r)
class Solution {
  static constexpr int N = 1000;
  static constexpr int modulo = 1e9 + 7;

  struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int val) : val(val), left(nullptr), right(nullptr) {}
  };

  struct Res {
    int64_t ways;
    int size;
  };

  // Precompute comb using Pascal
  static inline int comb[N + 1][N + 1];
  static void init() {
    comb[0][0] = 1;
    for (int i = 1; i <= N; ++i) {
      comb[i][0] = 1;
      for (int j = 1; j <= i; ++j) {
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % modulo;
      }
    }
  }
  static inline const bool initialized = (init(), true);

 public:
  int numOfWays(const vector<int>& nums) {
    // Build
    const auto root = buildTree(nums);

    // Find ways
    auto [ways, _] = findWays(root);
    return (ways - 1 + modulo) % modulo;
  }

 private:
  Res findWays(const Node* root) {
    if (root == nullptr) return {1, 0};

    auto [leftWays, leftSize] = findWays(root->left);
    auto [rightWays, rightSize] = findWays(root->right);

    int size = leftSize + rightSize;
    int64_t ways = (leftWays * rightWays) % modulo;
    ways = (ways * comb[size][leftSize]) % modulo;
    return {ways, size + 1};
  }

  Node* buildTree(const vector<int>& nums) {
    const int n = nums.size();
    auto root = new Node(nums[0]);
    for (int i = 1; i < n; ++i) {
      treeInsert(root, nums[i]);
    }
    return root;
  }

  void treeInsert(Node* root, int num) {
    if (num < root->val) {
      if (root->left != nullptr) {
        treeInsert(root->left, num);
      } else {
        root->left = new Node(num);
      }
    } else {
      if (root->right != nullptr) {
        treeInsert(root->right, num);
      } else {
        root->right = new Node(num);
      }
    }
  }
};

// Divide and Conquer
//
// Instead of building the tree, we use array form instead.
class Solution2 {
  static constexpr int N = 1000;
  static constexpr int modulo = 1e9 + 7;

  // Precompute comb using Pascal
  static inline int comb[N + 1][N + 1];
  static void init() {
    comb[0][0] = 1;
    for (int i = 1; i <= N; ++i) {
      comb[i][0] = 1;
      for (int j = 1; j <= i; ++j) {
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % modulo;
      }
    }
  }
  static inline const bool initialized = (init(), true);

 public:
  int numOfWays(const vector<int>& nums) {
    int64_t ways = findWays(nums);
    return (ways - 1 + modulo) % modulo;
  }

 private:
  int64_t findWays(const vector<int>& nums) {
    if (nums.empty()) return 1;

    // Find left and right subtree
    const int n = nums.size();
    int root = nums[0];

    auto lefts = vector<int>();
    auto rights = vector<int>();
    lefts.reserve(n);
    rights.reserve(n);

    for (int i = 1; i < n; ++i) {
      if (nums[i] < root) {
        lefts.push_back(nums[i]);
      } else {
        rights.push_back(nums[i]);
      }
    }

    // Count ways
    auto leftWays = findWays(lefts);
    auto rightWays = findWays(rights);

    int64_t ways = (leftWays * rightWays) % modulo;
    ways = (ways * comb[n - 1][lefts.size()]) % modulo;
    return ways;
  }
};

// Divide and Conquer
//
// Since N is small, we reuse the original array instead.
class Solution3 {
  static constexpr int N = 1000;
  static constexpr int modulo = 1e9 + 7;

  // Precompute comb using Pascal
  static inline int comb[N + 1][N + 1];
  static void init() {
    comb[0][0] = 1;
    for (int i = 1; i <= N; ++i) {
      comb[i][0] = 1;
      for (int j = 1; j <= i; ++j) {
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % modulo;
      }
    }
  }
  static inline const bool initialized = (init(), true);

 public:
  int numOfWays(const vector<int>& nums) {
    int64_t ways = findWays(nums, 1, nums.size());
    return (ways - 1 + modulo) % modulo;
  }

 private:
  int64_t findWays(const vector<int>& nums, int lo, int hi) {
    // Empty
    if (lo > hi) return 1;

    // Find root
    int mid = *find_if(nums.cbegin(), nums.cend(), [lo, hi](int num) {
      return lo <= num && num <= hi;  //
    });

    // Count ways
    int leftSize = mid - lo;
    int rightSize = hi - mid;
    auto leftWays = findWays(nums, lo, mid - 1);
    auto rightWays = findWays(nums, mid + 1, hi);

    int64_t ways = (leftWays * rightWays) % modulo;
    ways = (ways * comb[leftSize + rightSize][leftSize]) % modulo;
    return ways;
  }
};
