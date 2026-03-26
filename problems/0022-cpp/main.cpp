// Source: https://leetcode.com/problems/generate-parentheses
// Title: Generate Parentheses
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given `n` pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
//
// **Example 1:**
//
// ```
// Input: n = 3
// Output: ["((()))","(()())","(())()","()(())","()()()"]
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1
// Output: ["()"]
// ```
//
// **Constraints:**
//
// - `1 <= n <= 8`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Backtracking
class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    auto ans = vector<string>();

    string str = "";
    str.reserve(2 * n);

    backtrack(0, 2 * n, str, ans);
    return ans;
  }

  // d   is the parentheses depth.
  // k   is the number of letter to fill.
  // str is the current string.
  void backtrack(int d, int k, string& str, vector<string>& ans) {
    if (d == k) {
      ans.push_back(str + string(k, ')'));
      return;
    }

    str.push_back('(');
    backtrack(d + 1, k - 1, str, ans);
    str.pop_back();

    if (d == 0) return;
    str.push_back(')');
    backtrack(d - 1, k - 1, str, ans);
    str.pop_back();
  }
};
