// Source: https://leetcode.com/problems/longest-balanced-subarray-i
// Title: Longest Balanced Subarray I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`.
//
// A **subarray** is called **balanced** if the number of **distinct even** numbers in the subarray is equal to the number of **distinct odd** numbers.
//
// Return the length of the **longest** balanced subarray.
//
// **Example 1:**
//
// ```
// Input: nums = [2,5,4,3]
// Output: 4
// Explanation:
// - The longest balanced subarray is `[2, 5, 4, 3]`.
// - It has 2 distinct even numbers `[2, 4]` and 2 distinct odd numbers `[5, 3]`. Thus, the answer is 4.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [3,2,2,5,4]
// Output: 5
// Explanation:
// - The longest balanced subarray is `[3, 2, 2, 5, 4]`.
// - It has 2 distinct even numbers `[2, 4]` and 2 distinct odd numbers `[3, 5]`. Thus, the answer is 5.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3,2]
// Output: 3
// Explanation:
// - The longest balanced subarray is `[2, 3, 2]`.
// - It has 1 distinct even number `[2]` and 1 distinct odd number `[3]`. Thus, the answer is 3.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1500`
// - `1 <= nums[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Brute Force
class Solution {
 public:
  int longestBalanced(vector<int>& nums) {
    const int n = nums.size();

    // Subarray [i, j]
    int maxLen = 0;
    for (int i = 0; i < n; ++i) {
      auto odds = unordered_set<int>();
      auto evens = unordered_set<int>();
      for (int j = i; j < n; ++j) {
        const int num = nums[j];
        if (num % 2) {
          odds.insert(num);
        } else {
          evens.insert(num);
        }

        if (odds.size() == evens.size()) {
          maxLen = max(maxLen, j - i + 1);
        }
      }
    }

    return maxLen;
  }
};

// Segment Tree + Hash Map
//
// First consider the problem without the "unique" constraint (i.e. count all numbers).
// Now loop through the index r, and find the leftmost l such that [l, r) is balanced.
// This problem is easier. Define F[i] be the `odd-even` in [0, i).
// We use a hash map with F[i] as key and leftmost i as value.
// Then for each r, we just need to find F[l] = F[r] to find the maximum subarray.
//
// However, in this problem, we can't use above method due to the "unique" constraint.
// Then we need to find an algorithm to find the leftmost l.
//
// Suppose we have an array D[i], which is the `odd-even` in [i, r).
// We store the max and min of D in the segment tree.
//
// To query the leftmost l, we first check if max >= 0 >= min.
// If not, then there is no balanced l.
// Otherwise, choose the leftmost segment satisfies max >= 0 >= min.
//
// To update the segment tree, we use a hash map to store the previous index of each number.
// When we extend r (i.e. ++r), we check if nums[r] is in the hash map.
// If not, then we can safely add/substract the range [0, r].
// Otherwise (say previous nums[r] is at i), we only update the range [i+1, r].
class Solution2 {
  class SegmentTree {
    // Lazy Tag
    struct Tag {
      int64_t toAdd;

      Tag() : toAdd(0) {}
      Tag(int64_t val) : toAdd(val) {}

      bool isLazy() const { return toAdd != 0; };
      void apply(const Tag& t) { toAdd += t.toAdd; };
      void reset() { toAdd = 0; };
    };

    // Node info
    struct Info {
      int64_t minVal;
      int64_t maxVal;

      Info(int64_t val = 0) : minVal(val), maxVal(val) {}

      static Info merge(const Info& left, const Info& right) {
        Info res;
        res.minVal = min(left.minVal, right.minVal);
        res.maxVal = max(left.maxVal, right.maxVal);
        return res;
      }

      void apply(const Tag& t) {
        if (!t.isLazy()) return;
        minVal += t.toAdd;
        maxVal += t.toAdd;
      }
    };

    // Tree node
    struct Node {
      Info info;
      Tag tag;
    };

    const int n;
    vector<Node> tree;  // parent i -> child 2i & 2i+1

    int leftChild(int p) { return 2 * p; }
    int rightChild(int p) { return 2 * p + 1; }

    void apply(int p, const Tag& t) {
      tree[p].info.apply(t);
      tree[p].tag.apply(t);
    }

    void pushUp(int p) { tree[p].info = Info::merge(tree[leftChild(p)].info, tree[rightChild(p)].info); }

    void pushDown(int p) {
      auto& node = tree[p];

      if (!node.tag.isLazy()) return;

      apply(leftChild(p), node.tag);
      apply(rightChild(p), node.tag);
      node.tag.reset();
    }

    // Update range [l, r)
    void update(int l, int r, int p, int lo, int hi, const Tag& t) {
      // Out of range
      if (r <= lo || hi <= l) return;

      // Full overlap
      if (l <= lo && hi <= r) {
        apply(p, t);
        return;
      }

      // Partial overlap
      pushDown(p);
      int mid = lo + (hi - lo) / 2;
      update(l, r, leftChild(p), lo, mid, t);
      update(l, r, rightChild(p), mid, hi, t);
      pushUp(p);
    }

    // Find left most zero in range [l, r).
    // Return -1 if no zero.
    int leftmostZero(int l, int r, int p, int lo, int64_t hi) {
      // Out of range
      if (r <= lo || hi <= l) return -1;

      // No zero in [lo, hi)
      if (tree[p].info.maxVal < 0 || 0 < tree[p].info.minVal) {
        return -1;
      }

      // Leaf node
      if (lo == hi - 1) {
        return lo;
      }

      // Try left child
      pushDown(p);
      int mid = lo + (hi - lo) / 2;
      auto leftIdx = leftmostZero(l, r, leftChild(p), lo, mid);
      if (leftIdx != -1) return leftIdx;

      // Try right child
      return leftmostZero(l, r, rightChild(p), mid, hi);
    }

   public:
    SegmentTree(const int n) : n(n), tree(4 * n) {}

    void update(int l, int r, int64_t val) { update(l, r, 1, 0, n, Tag(val)); }

    int leftmostZero(int l, int r) { return leftmostZero(l, r, 1, 0, n); }
  };

 public:
  int longestBalanced(vector<int>& nums) {
    const int n = nums.size();

    auto numMap = unordered_map<int, int>();  // index of previous same number
    auto tree = SegmentTree(n);

    // Subarray [l, r]
    int maxLen = 0;
    for (int r = 0; r < n; ++r) {
      // Find query update range
      int num = nums[r];
      int prevIdx = numMap.contains(num) ? numMap[num] : -1;

      // Update number map
      numMap[num] = r;

      // Update range [prevIdx+1, r]
      tree.update(prevIdx + 1, r + 1, (num % 2 ? +1 : -1));

      // Find leftmost 0 index
      auto l = tree.leftmostZero(0, r + 1);
      if (l != -1) maxLen = max(maxLen, r - l + 1);
    }

    return maxLen;
  }
};
