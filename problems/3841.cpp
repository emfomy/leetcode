// Source: https://leetcode.com/problems/palindromic-path-queries-in-a-tree
// Title: Palindromic Path Queries in a Tree
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an undirected tree with `n` nodes labeled 0 to `n - 1`. This is represented by a 2D array `edges` of length `n - 1`, where `edges[i] = [u_i, v_i]` indicates an undirected edge between nodes `u_i` and `v_i`.
//
// You are also given a string `s` of length `n` consisting of lowercase English letters, where `s[i]` represents the character assigned to node `i`.
//
// You are also given a string array `queries`, where each `queries[i]` is either:
//
// - `"update u_i c"`: Change the character at node `u_i` to `c`. Formally, update `s[u_i] = c`.
// - `"query u_i v_i"`: Determine whether the string formed by the characters on the **unique** path from `u_i` to `v_i` (inclusive) can be **rearranged** into a **<button>palindrome</button>**.
//
// Return a boolean array `answer`, where `answer[j]` is `true` if the `j^th` query of type `"query u_i v_i"` can be rearranged into a **palindrome**, and `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: n = 3, edges = [[0,1],[1,2]], s = "aac", queries = ["query 0 2","update 1 b","query 0 2"]
// Output: [true,false]
// Explanation:
// - `"query 0 2"`: Path `0 → 1 → 2` gives `"aac"`, which can be rearranged to form `"aca"`, a palindrome. Thus, `answer[0] = true`.
// - `"update 1 b"`: Update node 1 to `'b'`, now `s = "abc"`.
// - `"query 0 2"`: Path characters are `"abc"`, which cannot be rearranged to form a palindrome. Thus, `answer[1] = false`.
// Thus, `answer = [true, false]`.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 4, edges = [[0,1],[0,2],[0,3]], s = "abca", queries = ["query 1 2","update 0 b","query 2 3","update 3 a","query 1 3"]
// Output: [false,false,true]
// Explanation:
// - `"query 1 2"`: Path `1 → 0 → 2` gives `"bac"`, which cannot be rearranged to form a palindrome. Thus, `answer[0] = false`.
// - `"update 0 b"`: Update node 0 to `'b'`, now `s = "bbca"`.
// - `"query 2 3"`: Path `2 → 0 → 3` gives `"cba"`, which cannot be rearranged to form a palindrome. Thus, `answer[1] = false`.
// - `"update 3 a"`: Update node 3 to `'a'`, `s = "bbca"`.
// - `"query 1 3"`: Path `1 → 0 → 3` gives `"bba"`, which can be rearranged to form `"bab"`, a palindrome. Thus, `answer[2] = true`.
// Thus, `answer = [false, false, true]`.
// ```
//
// **Constraints:**
//
// - `1 <= n == s.length <= 5 * 10^4`
// - `edges.length == n - 1`
// - `edges[i] = [u_i, v_i]`
// - `0 <= u_i, v_i <= n - 1`
// - `s` consists of lowercase English letters.
// - The input is generated such that `edges` represents a valid tree.
// - `1 <= queries.length <= 5 * 10^4`
// - `queries[i] = "update u_i c"` or
// - `queries[i] = "query u_i v_i"`
// - `0 <= u_i, v_i <= n - 1`
// - `c` is a lowercase English letter.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <bit>
#include <cstdint>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

// Fenwick Tree + Binary Lifting
//
// Convert the graph into a tree.
// For each node, compute the letter frequency of the path to the root.
// Note that we only need to know the parity of the frequency (for palindrome check).
// Therefore, we can use a 26bit-mask instead (denoted as mask[x]).
//
// For each query, say w is the LCA of u and v.
// mask[u] XOR mask[v] is almost the path, except w (w is canceled out).
// Therefore, the correct mask is mask[u] ^ mask[v] ^ bit(s[w]).
// A good path should contain at most 1 bit.
// Note that we use Binary Lifting to find the LCA.
//
// However, update is expensive.
// Therefore we use BIT instead
// We first use euler tour to find l/r for each node.
// We use preorder traverse.
// Say node l[u] = L, r[u] = R; that is, [L, R) is the subtree of u (including u).
// To update u, we need to update the mask for [L, R).
//
// Therefore, we need a BIT with range update and single query.
// We use the BIT to store the diff.

class Solution {
  using Mask = uint32_t;

  struct Tree {
    int n;
    int logn;
    vector<int> l;           // Euler tour (in)
    vector<int> r;           // Euler tour (out)
    vector<vector<int>> up;  // binary lifting, 2^k th ancestor
    int timer = 0;

    Tree(int n) : n(n), logn(bit_width(unsigned(n))), l(n), r(n), up(logn, vector<int>(n)) {}

    // Euler tour
    void build(const vector<vector<int>>& graph) {
      build(graph, 0, 0);

      buildUp();
    }
    void build(const vector<vector<int>>& graph, int u, int parent) {
      up[0][u] = parent;
      l[u] = timer++;
      for (int v : graph[u]) {
        if (v == parent) continue;
        build(graph, v, u);
      }
      r[u] = timer;
    }

    // Binary lifting
    void buildUp() {
      for (int k = 1; k < logn; ++k) {
        for (int u = 0; u < n; ++u) {
          int p = up[k - 1][u];  // 2^(k-1)th ancestor
          up[k][u] = up[k - 1][p];
        }
      }
    }

    int lca(int u, int v) const {
      if (l[u] > l[v]) swap(u, v);  // WLOG, l[u] <= l[v]

      if (l[v] < r[u]) return u;  // u is v's ancestor

      // Lift up
      for (int k = logn - 1; k >= 0; --k) {
        if (!(l[v] < r[up[k][u]])) {  // up[k][u] is not v's ancestor, we can lift up safely
          u = up[k][u];
        }
      }

      // Now parent of u is v's ancestor
      return up[0][u];
    }
  };

  // A is the data
  //
  // Let D be the diff array
  // D[t] = A[t] ^ A[t-1], A[-1] = 0 (here we use ^ not - since we need XOR)
  struct FenwickTree {
    int n;

    // tree[i] = sum of range [i-lowbit(i), i); length is lowbit(i)
    vector<Mask> tree;  // D[t]

    FenwickTree(int n) : n(n), tree(n + 1) {}

    // Update: O(logN); D[idx] ^= delta
    void updateOne(int idx, Mask delta) {
      // start at x+1 since x in [0, x+1)
      for (int i = idx + 1; i <= n; i += (i & -i)) {
        tree[i] ^= delta;
      }
    }

    // Range Update: O(logN); [l, r) ^= delta
    void update(int l, int r, Mask delta) {
      if (l >= r) return;
      updateOne(l, delta);
      updateOne(r, delta);
    }

    // Query: O(logN); Sum of D[0, r)
    Mask queryPrefix(int r) const {
      Mask sum = 0;
      for (int i = r; i >= 1; i -= (i & -i)) {
        sum ^= tree[i];
      }
      return sum;
    }

    // Query: O(logN); A[x] = Sum D[0, x]
    Mask query(int x) const {  //
      return queryPrefix(x + 1);
    }
  };

 public:
  vector<bool> palindromePath(int n, const vector<vector<int>>& edges, string& s, const vector<string>& queries) {
    // Build graph
    auto graph = vector<vector<int>>(n);
    for (auto& edge : edges) {
      int u = edge[0], v = edge[1];
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    // Build tree
    auto tree = Tree(n);
    tree.build(graph);
    const auto& l = tree.l;
    const auto& r = tree.r;

    // Build BIT
    auto bit = FenwickTree(n);
    for (int i = 0; i < n; ++i) {
      bit.update(l[i], r[i], 1 << (s[i] - 'a'));
    }

    // Query
    auto ans = vector<bool>();
    ans.reserve(queries.size());
    for (const auto& query : queries) {
      stringstream ss(query);
      string op;
      ss >> op;
      if (op == "update") {  // update
        int u;
        char c;
        ss >> u >> c;
        bit.update(l[u], r[u], (1 << (s[u] - 'a')) ^ (1 << (c - 'a')));
        s[u] = c;
      } else {  // query
        int u, v;
        ss >> u >> v;

        // Find LCA
        int w = tree.lca(u, v);

        Mask path = bit.query(l[u]) ^ bit.query(l[v]) ^ (1 << (s[w] - 'a'));
        ans.push_back(popcount(path) <= 1);
      }
    }

    return ans;
  }
};
