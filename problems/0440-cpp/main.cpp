// Source: https://leetcode.com/problems/k-th-smallest-in-lexicographical-order
// Title: K-th Smallest in Lexicographical Order
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integers `n` and `k`, return the `k^th` lexicographically smallest integer in the range `[1, n]`.
//
// **Example 1:**
//
// ```
// Input: n = 13, k = 2
// Output: 10
// Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1, k = 1
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= k <= n <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// Heap, TLE
//
// Convert the numbers into string.
// Use a heap of size k to maintain the smallest k numbers.
class Solution {
  using Heap = priority_queue<string>;  // max-heap

 public:
  int findKthNumber(int n, int k) {
    // Guard
    if (k < 0 || n < k) return 0;

    // Find k-smallest
    Heap heap;
    for (int i = 1; i <= n; ++i) {
      heap.push(to_string(i));
      while (heap.size() > k) heap.pop();  // pop largest number
    }

    return stoi(heap.top());
  }
};

// DFS
//
// We treat all the numbers as a trie.
// We traverse the trie in pre-order.
class Solution2 {
 public:
  int findKthNumber(int64_t n, int64_t k) {
    // Guard
    if (k < 0 || n < k) return 0;

    auto st = stack<pair<int64_t, int>>();  // number, next digit
    for (int num = 9; num >= 1; --num) {
      st.push({num, -1});  // next digit = -1 means end of string
    }

    while (k > 0) {
      auto [num, digit] = st.top();
      st.pop();

      if (digit == -1) {
        --k;
        if (k == 0) return num;
      }

      // Traverse
      ++digit;
      if (digit >= 10) continue;

      // Next number
      int nextNum = num * 10 + digit;
      if (nextNum > n) continue;
      st.push({num, digit});
      st.push({nextNum, -1});
    }

    return 0;  // unreachable
  }
};

// DFS
//
// We can do early stop while traversing the trie.
//
// We first start with the root node, and write `next` as the next node's value.
//
// For examples:
// the next of root node is 1;
// the next of 1 is 10 or 2 (depends on whether if 10 exists in the trie);
// the next of 23 is 230 or 24 (depends on whether if 230 exists in the trie).
//
// We can use `next` to compute the size of the subtree.
// We can compute it layer by layer.
// The first layer are numbers in [next, next+1)
// The second layer are numbers in [10next, 10(next+1)), and so on.
// Note that we need to exclude the numbers greater than n.
// The loop ends when the range is empty (i.e. start value than n).
//
// Say the size subtree of `next` is t.
// If t < k, then the answer does not in this subtree.
// We then skip entire of the tree by substract k by t and increase `next`.
// If t >= k, then the answer is in this subtree.
// We traverse deep into this subtree by substract k by 1 and multiply `next` by 10.
// The substract means we consumes the `next` node.
//
// This algorithm ends when k = 1 (i.e. `next` is what we want).
class Solution3 {
  int prefixCount(int64_t n, int64_t root) {
    int64_t start = root, end = root + 1;  // count in range [start, end)
    int count = 0;
    while (start <= n) {
      count += min(n + 1, end) - start;
      start *= 10;
      end *= 10;
    }
    return count;
  }

 public:
  int findKthNumber(int64_t n, int64_t k) {
    // Guard
    if (k < 0 || n < k) return 0;

    int64_t next = 1;
    while (k > 1) {
      int count = prefixCount(n, next);
      if (count < k) {
        k -= count;  // consumes subtree of `next`
        ++next;
      } else {
        k--;  // consumes node `next`
        next *= 10;
      }
    }

    return next;
  }
};
