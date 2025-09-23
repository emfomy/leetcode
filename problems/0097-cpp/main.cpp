// Source: https://leetcode.com/problems/interleaving-string
// Title: Interleaving String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given strings `s1`, `s2`, and `s3`, find whether `s3` is formed by an **interleaving** of `s1` and `s2`.
//
// An **interleaving** of two strings `s` and `t` is a configuration where `s` and `t` are divided into `n` and `m` <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:r1m:" data-state="closed" class="">substrings</button> respectively, such that:
//
// - `s = s_1 + s_2 + ... + s_n`
// - `t = t_1 + t_2 + ... + t_m`
// - `|n - m| <= 1`
// - The **interleaving** is `s_1 + t_1 + s_2 + t_2 + s_3 + t_3 + ...` or `t_1 + s_1 + t_2 + s_2 + t_3 + s_3 + ...`
//
// **Note:** `a + b` is the concatenation of strings `a` and `b`.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/09/02/interleave.jpg
//
// ```
// Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
// Output: true
// Explanation: One way to obtain s3 is:
// Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
// Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac".
// Since s3 can be obtained by interleaving s1 and s2, we return true.
// ```
//
// **Example 2:**
//
// ```
// Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
// Output: false
// Explanation: Notice how it is impossible to interleave s2 with any other string to obtain s3.
// ```
//
// **Example 3:**
//
// ```
// Input: s1 = "", s2 = "", s3 = ""
// Output: true
// ```
//
// **Constraints:**
//
// - `0 <= s1.length, s2.length <= 100`
// - `0 <= s3.length <= 200`
// - `s1`, `s2`, and `s3` consist of lowercase English letters.
//
// **Follow up:** Could you solve it using only `O(s2.length)` additional memory space?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <string>
#include <vector>

using namespace std;

// Use DFS
//
// Note that we only need to store if a case is visited.
// Since if we found the solution, we can just leave the DFS.
class Solution {
 public:
  bool isInterleave(string s1, string s2, string s3) {
    int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
    if (n1 + n2 != n3) return false;

    auto visited = vector(n1 + 1, vector(n2 + 1, false));

    function<int(int, int)> dfs = [&](int i1, int i2) -> bool {
      auto i3 = i1 + i2;
      if (i3 == n3) return true;

      if (visited[i1][i2]) return false;
      visited[i1][i2] = true;

      if (i1 < n1 && s1[i1] == s3[i3]) {
        if (dfs(i1 + 1, i2)) return true;
      }
      if (i2 < n2 && s2[i2] == s3[i3]) {
        if (dfs(i1, i2 + 1)) return true;
      }

      return false;
    };

    return dfs(0, 0);
  }
};

// Use 2D-DP
//
// The problem is the same as find path from top-left to bottom-right.
//
// If s1[i1] == s3[i1+i2], then we can go down
// If s2[i2] == s3[i1+i2], then we can go right
class Solution2 {
 public:
  bool isInterleave(string s1, string s2, string s3) {
    int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
    if (n1 + n2 != n3) return false;

    auto dp = vector(n1 + 1, vector(n2 + 1, false));
    dp[0][0] = true;
    for (auto i1 = 0; i1 <= n1; ++i1) {
      for (auto i2 = 0; i2 <= n2; ++i2) {
        if (!dp[i1][i2]) continue;
        auto i3 = i1 + i2;
        if (i1 < n1 && s1[i1] == s3[i3]) dp[i1 + 1][i2] = true;
        if (i2 < n2 && s2[i2] == s3[i3]) dp[i1][i2 + 1] = true;
      }
    }

    return dp[n1][n2];
  }
};

// Use 2D-DP
//
// The problem is the same as find path from bottom-right to top-left.
//
// dp[i1][i2] = (dp[i1+1][i2] AND s1[i1] == s3[i1+i2]) OR (dp[i1][i2+1] AND s2[i2] == s3[i1+i2])
class Solution3 {
 public:
  bool isInterleave(string s1, string s2, string s3) {
    int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
    if (n1 + n2 != n3) return false;

    auto dp = vector(n1 + 1, vector(n2 + 1, false));
    for (auto i1 = n1; i1 >= 0; --i1) {
      for (auto i2 = n2; i2 >= 0; --i2) {
        auto i3 = i1 + i2;
        dp[i1][i2] = (i1 < n1 && dp[i1 + 1][i2] && s1[i1] == s3[i1 + i2]) ||  //
                     (i2 < n2 && dp[i1][i2 + 1] && s2[i2] == s3[i1 + i2]) ||  //
                     (i1 == n1 && i2 == n2);
      }
    }

    return dp[0][0];
  }
};

// Use 1D-DP
//
// The problem is the same as find path from bottom-right to top-left.
//
// dp[i1][i2] = (dp[i1+1][i2] AND s1[i1] == s3[i1+i2]) OR (dp[i1][i2+1] AND s2[i2] == s3[i1+i2])
class Solution4 {
 public:
  bool isInterleave(string s1, string s2, string s3) {
    int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
    if (n1 + n2 != n3) return false;

    auto curr = vector(n2 + 1, false);
    auto prev = vector(n2 + 1, false);
    curr[n2] = true;
    for (auto i1 = n1; i1 >= 0; --i1) {
      swap(curr, prev);
      for (auto i2 = n2; i2 >= 0; --i2) {
        auto i3 = i1 + i2;
        curr[i2] = (i1 < n1 && prev[i2] && s1[i1] == s3[i1 + i2]) ||      //
                   (i2 < n2 && curr[i2 + 1] && s2[i2] == s3[i1 + i2]) ||  //
                   (i1 == n1 && i2 == n2);
      }
    }

    return curr[0];
  }
};
