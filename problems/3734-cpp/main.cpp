// Source: https://leetcode.com/problems/path-existence-queries-in-a-graph-ii
// Title: Path Existence Queries in a Graph II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n` representing the number of nodes in a graph, labeled from 0 to `n - 1`.
//
// You are also given an integer array `nums` of length `n` and an integer `maxDiff`.
//
// An **undirected **edge exists between nodes `i` and `j` if the **absolute** difference between `nums[i]` and `nums[j]` is **at most** `maxDiff` (i.e., `|nums[i] - nums[j]| <= maxDiff`).
//
// You are also given a 2D integer array `queries`. For each `queries[i] = [u_i, v_i]`, find the **minimum** distance between nodes `u_i` and `v_i`_. If no path exists between the two nodes, return -1 for that query.
//
// Return an array `answer`, where `answer[i]` is the result of the `i^th` query.
//
// **Note:** The edges between the nodes are unweighted.
//
// **Example 1:**
//
// ```
// Input: n = 5, nums = [1,8,3,4,2], maxDiff = 3, queries = [[0,3],[2,4]]
// Output: [1,1]
// Explanation:
// The resulting graph is:
// https://assets.leetcode.com/uploads/2025/03/25/4149example1drawio.png
//
// | Query | Shortest Path | Minimum Distance |
// |-------|---------------|------------------|
// | [0,3] | 0 → 3         | 1                |
// | [2,4] | 2 → 4         | 1                |
//
// Thus, the output is `[1, 1]`.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5, nums = [5,3,1,9,10], maxDiff = 2, queries = [[0,1],[0,2],[2,3],[4,3]]
// Output: [1,2,-1,1]
// Explanation:
// The resulting graph is:
// https://assets.leetcode.com/uploads/2025/03/25/4149example2drawio.png
//
// | Query | Shortest Path | Minimum Distance |
// |-------|---------------|------------------|
// | [0,3] | 0 → 3         | 1                |
// | [2,4] | 2 → 4         | 1                |
//
// Thus, the output is `[1, 2, -1, 1]`.
//
// **Example 3:**
//
// ```
// Input: n = 3, nums = [3,6,1], maxDiff = 1, queries = [[0,0],[0,1],[1,2]]
// Output: [0,-1,-1]
// Explanation:
// There are no edges between any two nodes because:
// - Nodes 0 and 1: `|nums[0] - nums[1]| = |3 - 6| = 3 > 1`
// - Nodes 0 and 2: `|nums[0] - nums[2]| = |3 - 1| = 2 > 1`
// - Nodes 1 and 2: `|nums[1] - nums[2]| = |6 - 1| = 5 > 1`
// Thus, no node can reach any other node, and the output is `[0, -1, -1]`.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 10^5`
// - `0 <= nums[i] <= 10^5`
// - `0 <= maxDiff <= 10^5`
// - `1 <= queries.length <= 10^5`
// - `queries[i] == [u_i, v_i]`
// - `0 <= u_i, v_i < n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Sort + Sliding Window + Binary Lifting
//
// First sort the nodes. Find the gaps and group the nodes.
// Path exists iff. two node are in the same group.
//
// Next use sliding window to find the furthest reachable node (in one step) per node.
// The node int the window is always less than maxDiff.
// Before pushing new node, check if the head is too far.
// If so, pop the head node, and assign head.max_reach = tail.
// (Note that we must ensure that head != tail).
//
// Next use binary lifting to find the path length.
// For each node,
// we store the furthest node it can reach in 1, 2, 4, 8, ... steps.
//
// Let jump[u][k] be the node from u with 2^k steps.
// jump[u][0] is initialized from above sliding window.
// We can compute jump[u][k] from jump[u][k-1].
class Solution {
  struct Node {
    int rank;
    int num;
  };

 public:
  vector<int> pathExistenceQueries(       //
      const int n,                        //
      const vector<int>& nums,            //
      const int maxDiff,                  //
      const vector<vector<int>>& queries  //
  ) {
    // Sort by index
    auto orders = vector<int>(n);  // orders[rank] = original_idx
    iota(orders.begin(), orders.end(), 0);
    const auto comp = [&nums](int i, int j) -> bool { return nums[i] < nums[j]; };
    sort(orders.begin(), orders.end(), comp);

    auto ranks = vector<int>(n);  // ranks[original_idx] = order (i.e. sorted position)
    for (int r = 0; r < n; r++) {
      ranks[orders[r]] = r;
    }

    // Group
    auto groups = vector<int>(n);
    groups[0] = 0;
    for (int r = 0; r < n - 1; ++r) {
      if (nums[orders[r + 1]] - nums[orders[r]] <= maxDiff) {
        groups[r + 1] = groups[r];
      } else {
        groups[r + 1] = groups[r] + 1;
      }
    }

    // Sliding window
    int logn = bit_width(size_t(n));                           // floor(log(n)) + 1
    auto jump = vector<vector<int>>(n, vector<int>(logn, n));  // n as can't go
    int head = 0;
    for (int r = 0; r < n; ++r) {  // [head, r) is current window
      int num = nums[orders[r]];
      while (head < r && num - nums[orders[head]] > maxDiff) {
        if (head < r - 1) {  // r-1 = tail exist
          jump[head][0] = r - 1;
        }
        ++head;
      }
    }

    // Binary lifting
    for (int k = 1; k < logn; ++k) {
      for (int r = 0; r < n; ++r) {
        int nextR = jump[r][k - 1];
        if (nextR >= n) continue;
        jump[r][k] = jump[nextR][k - 1];
      }
    }

    // Query
    auto ans = vector<int>();
    ans.reserve(queries.size());
    for (const auto& query : queries) {
      int u = ranks[query[0]], v = ranks[query[1]];
      if (groups[u] != groups[v]) {
        ans.push_back(-1);
        continue;
      }
      if (u > v) swap(u, v);

      int curr = u, step = 0;
      for (int k = logn - 1; k >= 0; --k) {
        int next = jump[curr][k];
        if (next <= v) {  // reachable and not too far
          curr = next;
          step += (1 << k);
        }
      }
      if (curr < v) ++step;  // not reach v, add one extra step
      ans.push_back(step);
    }

    return ans;
  }
};
