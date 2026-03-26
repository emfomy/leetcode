// Source: https://leetcode.com/problems/count-paths-that-can-form-a-palindrome-in-a-tree
// Title: Count Paths That Can Form a Palindrome in a Tree
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **tree** (i.e. a connected, undirected graph that has no cycles) **rooted** at node `0` consisting of `n` nodes numbered from `0` to `n - 1`. The tree is represented by a **0-indexed** array `parent` of size `n`, where `parent[i]` is the parent of node `i`. Since node `0` is the root, `parent[0] == -1`.
//
// You are also given a string `s` of length `n`, where `s[i]` is the character assigned to the edge between `i` and `parent[i]`. `s[0]` can be ignored.
//
// Return the number of pairs of nodes `(u, v)` such that `u < v` and the characters assigned to edges on the path from `u` to `v` can be **rearranged** to form a **palindrome**.
//
// A string is a **palindrome** when it reads the same backwards as forwards.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2023/07/15/treedrawio-8drawio.png
//
// ```
// Input: parent = [-1,0,0,1,1,2], s = "acaabc"
// Output: 8
// Explanation: The valid pairs are:
// - All the pairs (0,1), (0,2), (1,3), (1,4) and (2,5) result in one character which is always a palindrome.
// - The pair (2,3) result in the string "aca" which is a palindrome.
// - The pair (1,5) result in the string "cac" which is a palindrome.
// - The pair (3,5) result in the string "acac" which can be rearranged into the palindrome "acca".
// ```
//
// **Example 2:**
//
// ```
// Input: parent = [-1,0,0,0,0], s = "aaaaa"
// Output: 10
// Explanation: Any pair of nodes (u,v) where u < v is valid.
// ```
//
// **Constraints:**
//
// - `n == parent.length == s.length`
// - `1 <= n <= 10^5`
// - `0 <= parent[i] <= n - 1` for all `i >= 1`
// - `parent[0] == -1`
// - `parent` represents a valid tree.
// - `s` consists of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bitset>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// DFS + Hash Map
//
// Since we are finding palindromes with arrangement,
// we only care about parity of each character.
// A palindrome can only contain one letter with odd count.
// We can use a bitset to represent the parity of a path.
//
// We find all paths from root, and store the parity into a hash map (with counts).
// We also include the empty path (0 to 0).
// Any pair of two paths from root forms the all possible paths in the tree.
// Note the overlapping segment is cancelled out (due to the parity is even).
// To merge two paths, we use XOR on their parity.
//
// Instead of looping all pairs,
// we try to flip each bit of path1 to get path2 (ensure bitcount(path1 ^ path2) = 1).
// Note that we divide the 2 at the end (since path + path2 = path2 + path1).
class Solution {
  using Path = bitset<26>;
  using PathMap = unordered_map<Path, long long>;
  using Graph = vector<vector<int>>;

  struct Ctx {
    const string& s;
    const Graph& graph;
    PathMap& pathMap;
  };

 public:
  long long countPalindromePaths(const vector<int>& parent, const string& s) {
    const int n = parent.size();

    // Init graph
    auto graph = Graph(n);  // parent -> child
    for (int i = 1; i < n; ++i) {
      graph[parent[i]].push_back(i);
    }

    // DFS
    auto pathMap = PathMap();
    Ctx ctx{s, graph, pathMap};
    dfs(ctx, 0, 0);

    // Compute all possible paths
    long long ans = 0;
    for (const auto [path1, count1] : pathMap) {
      // path1 + path1
      ans += count1 * (count1 - 1);  // exclude self merge

      // path1 + path2
      for (int bit = 0; bit < 26; ++bit) {
        const auto path2 = Path{path1}.flip(bit);
        auto it2 = pathMap.find(path2);
        if (it2 != pathMap.cend()) {
          ans += count1 * it2->second;
        }
      }
    }

    return ans / 2;
  }

  void dfs(Ctx& ctx, const int node, const Path path) {
    ++ctx.pathMap[path];

    for (int child : ctx.graph[node]) {
      dfs(ctx, child, Path{path}.flip(ctx.s[child] - 'a'));  // copy path
    }
  }
};
