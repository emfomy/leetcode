// Source: https://leetcode.com/problems/remove-invalid-parentheses
// Title: Remove Invalid Parentheses
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.
//
// Return a list of **unique strings** that are valid with the minimum number of removals. You may return the answer in **any order**.
//
// **Example 1:**
//
// ```
// Input: s = "()())()"
// Output: ["(())()","()()()"]
// ```
//
// **Example 2:**
//
// ```
// Input: s = "(a)())()"
// Output: ["(a())()","(a)()()"]
// ```
//
// **Example 3:**
//
// ```
// Input: s = ")("
// Output: [""]
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 25`
// - `s` consists of lowercase English letters and parentheses `'('` and `')'`.
// - There will be at most `20` parentheses in `s`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// DP
class Solution {
  using Mask = unsigned int;

 public:
  vector<string> removeInvalidParentheses(const string &s) {
    const int n = s.size();
    const int m = 1 << n;

    // Edge case
    if (isValid(s)) return {s};

    // Loop
    auto ans = vector<string>();
    auto curr = unordered_set<string>();
    auto prev = unordered_set<string>();
    curr.insert(s);
    for (int l = n; l > 0; --l) {
      swap(curr, prev);
      curr.clear();

      // Remove ith letter
      for (const string &ss : prev) {
        for (int i = 0; i < l; ++i) {
          if (ss[i] == '(' || ss[i] == ')') {
            curr.insert(ss.substr(0, i) + ss.substr(i + 1));
          }
        }
      }

      // Check Valid
      for (const string &ss : curr) {
        if (isValid(ss)) {
          ans.push_back(ss);
        }
      }
      if (!ans.empty()) break;
    }

    return ans;
  }

  bool isValid(const string &ss) {
    int depth = 0;
    for (const char ch : ss) {
      if (ch == '(') {
        ++depth;
      } else if (ch == ')') {
        --depth;
      }
      if (depth < 0) return false;
    }
    return depth == 0;
  }
};
