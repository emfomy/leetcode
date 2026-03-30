// Source: https://leetcode.com/problems/find-the-string-with-lcp
// Title: Find the String with LCP
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// We define the `lcp` matrix of any **0-indexed** string `word` of `n` lowercase English letters as an `n x n` grid such that:
//
// - `lcp[i][j]` is equal to the length of the **longest common prefix** between the substrings `word[i,n-1]` and `word[j,n-1]`.
//
// Given an`n x n` matrix `lcp`, return the alphabetically smallest string `word` that corresponds to `lcp`. If there is no such string, return an empty string.
//
// A string `a` is lexicographically smaller than a string `b` (of the same length) if in the first position where `a` and `b` differ, string `a` has a letter that appears earlier in the alphabet than the corresponding letter in `b`. For example, `"aabd"` is lexicographically smaller than `"aaca"` because the first position they differ is at the third letter, and `'b'` comes before `'c'`.
//
// **Example 1:**
//
// ```
// Input: lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
// Output: "abab"
// Explanation: lcp corresponds to any 4 letter string with two alternating letters. The lexicographically smallest of them is "abab".
// ```
//
// **Example 2:**
//
// ```
// Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
// Output: "aaaa"
// Explanation: lcp corresponds to any 4 letter string with a single distinct letter. The lexicographically smallest of them is "aaaa".
// ```
//
// **Example 3:**
//
// ```
// Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
// Output: ""
// Explanation: lcp[3][3] cannot be equal to 3 since word[3,...,3] consists of only a single letter; Thus, no answer exists.
// ```
//
// **Constraints:**
//
// - `1 <= n ==``lcp.length == ``lcp[i].length``<= 1000`
// - `0 <= lcp[i][j] <= n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <bit>
#include <bitset>
#include <functional>
#include <map>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// Union-Find + Tree Map + Hash Set + Bit Mask
//
// The matrix must be symmetric.
// The main diagonal must be n, n-1, n-2, ..., 1.
// For other diagonal. If LCP[i][j] > 0, then LCP[i+1][j+1] must be LCP[i][j]-1.
//
// Next loop for each row.
// Focus on LCP[i, j] with i < j.
// If LCP[i, j] > 0, then s[i] == s[j]; Otherwise, s[i] != s[j].
//
// Use union find the group the letters.
// Next check if the inequality contradicts.
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> ranks;

    UnionFind(int n) : parents(n, 0), ranks(n, 0) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure rank(x) >= rank(y)
      if (ranks[x] < ranks[y]) swap(x, y);

      // Merge y into y
      if (ranks[x] == ranks[y]) ++ranks[x];
      parents[y] = x;
    }
  };

  struct Mask : bitset<26> {
    int low_zero() const {  // find lowest zero
      return countr_one(to_ulong());
    }
  };

 public:
  string findTheString(const vector<vector<int>>& lcp) {
    const int n = lcp.size();

    // Check symmetric
    for (int j = 0; j < n; ++j) {
      for (int i = 0; i < j; ++i) {
        if (lcp[i][j] != lcp[j][i]) return "";
      }
    }

    // Check main diagonal
    for (int j = 0; j < n; ++j) {
      if (lcp[j][j] != n - j) return "";
    }

    // Check other diagonal
    for (int j = 1; j < n; ++j) {
      for (int i = 0; i < j; ++i) {
        int k = lcp[i][j];
        if (k == 0) continue;

        int nextK = j + 1 < n ? lcp[i + 1][j + 1] : 0;  // out of range is 0
        if (k != nextK + 1) return "";
      }
    }

    // Check equality
    UnionFind uf(n);
    for (int j = 1; j < n; ++j) {
      for (int i = 0; i < j; ++i) {
        if (lcp[i][j]) uf.unite(i, j);
      }
    }

    // Check inequality
    auto ineqs = map<int, unordered_set<int>>();
    for (int j = 1; j < n; ++j) {
      for (int i = 0; i < j; ++i) {
        if (lcp[i][j]) continue;

        int x = uf.find(i), y = uf.find(j);
        if (x == y) return "";

        ineqs[x].insert(y);
        ineqs[y].insert(x);
      }
    }

    // Construct roots
    auto s = string(n, '\0');
    s[0] = 'a';
    for (auto [x, ys] : ineqs) {
      if (s[x]) continue;  // skip assigned
      Mask m;

      // Exclude by inequities
      for (int y : ys) {
        if (s[y]) m.set(s[y] - 'a');
      }

      // Find smallest valid letter
      int idx = m.low_zero();
      if (idx >= 26) return "";
      s[x] = 'a' + idx;
    }

    // Construct non-roots
    for (int i = 0; i < n; ++i) {
      int p = uf.find(i);
      s[i] = s[p];
    }

    return s;
  }
};

// Greedy + DP + Bit Mask
//
// Construct the string using greedy.
// For each j, loop from all i < j.
// If any LCP[i, j] > 0, then s[j] = s[i].
// Otherwise, select the smallest letter that is different from all s[i] with LCP[i][j] == 0.
//
// Next, use DP to reconstruct LCP again using the string,
// and check if the new LCP is equal to the old one.
class Solution2 {
  struct Mask : bitset<26> {
    int low_zero() const {  // find lowest zero
      return countr_one(to_ulong());
    }
  };

 public:
  string findTheString(const vector<vector<int>>& lcp) {
    const int n = lcp.size();

    // Greed
    string s;
    s.reserve(n);
    for (int j = 0; j < n; ++j) {
      const auto& row = lcp[j];
      // Find first nonzero i
      int i = distance(row.cbegin(), find_if(row.cbegin(), row.cbegin() + j, [](int x) { return x > 0; }));
      if (i < j) {
        s.push_back(s[i]);
        continue;
      }

      // Find smallest valid letter
      Mask m;
      for (int i = 0; i < j; ++i) {
        m.set(s[i] - 'a');
      }

      int idx = m.low_zero();
      if (idx >= 26) return "";
      s.push_back('a' + idx);
    }

    // Validate LCP
    for (int i = n - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        if (s[i] != s[j]) {
          if (lcp[i][j] != 0) return "";
        } else {
          int nextLCP = (i + 1 < n && j + 1 < n) ? lcp[i + 1][j + 1] : 0;
          if (lcp[i][j] != nextLCP + 1) return "";
        }
      }
    }

    return s;
  }
};

// Greedy + DP
//
// Instead of bit mask, track currently used letters.
// Note that in LCP, any pair of (i, j) must be either equal or inequal.
// There is no unknown pair.
//
// For for each index i.
// If it is not set, then pick the next unused letter,
// and set s[j] = s[i] for LCP[i][j] with j > i.
class Solution3 {
 public:
  string findTheString(const vector<vector<int>>& lcp) {
    const int n = lcp.size();

    // Greed
    string s(n, '\0');
    char unusedChar = 'a';
    for (int i = 0; i < n; ++i) {
      if (s[i]) continue;  // skip filled letter

      // Set letter
      s[i] = unusedChar++;
      if (s[i] > 'z') return "";  // out of range

      // Fill right
      for (int j = i + 1; j < n; ++j) {
        if (lcp[i][j]) s[j] = s[i];
      }
    }

    // Validate LCP
    for (int i = n - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        if (s[i] != s[j]) {
          if (lcp[i][j] != 0) return "";
        } else {
          int nextLCP = (i + 1 < n && j + 1 < n) ? lcp[i + 1][j + 1] : 0;
          if (lcp[i][j] != nextLCP + 1) return "";
        }
      }
    }

    return s;
  }
};
