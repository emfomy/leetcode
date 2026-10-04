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
  struct Backtrack {
    vector<string> ans;

    // d:   parentheses depth.
    // k:   number of letter to fill.
    // str: current string.
    void run(int d, int k, string& str) {
      if (d == k) {
        ans.push_back(str + string(k, ')'));
        return;
      }

      str.push_back('(');
      run(d + 1, k - 1, str);
      str.pop_back();

      if (d == 0) return;
      str.push_back(')');
      run(d - 1, k - 1, str);
      str.pop_back();
    }
  };

 public:
  vector<string> generateParenthesis(int n) {
    string str = "";
    str.reserve(2 * n);

    Backtrack bt;
    bt.run(0, 2 * n, str);
    return bt.ans;
  }
};
