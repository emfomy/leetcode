// Source: https://leetcode.com/problems/basic-calculator-iii
// Title: Basic Calculator III
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.
//
// **Note:** You are **not** allowed to use any built-in function which evaluates strings as mathematical expressions, such as `eval()`.
//
// **Example 1:**
//
// ```
// Input: s = "1 + 1"
// Output: 2
// ```
//
// **Example 2:**
//
// ```
// Input: s = " 2-1 + 2 "
// Output: 3
// ```
//
// **Example 3:**
//
// ```
// Input: s = "(1+(4+5+2)-3)+(6+8)"
// Output: 23
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 3 * 10^5`
// - `s` consists of digits, `'+'`, `'-'`, `'('`, `')'`, and `' '`.
// - `s` represents a valid expression.
// - `'+'` is **not** used as a unary operation (i.e., `"+1"` and `"+(2 + 3)"` is invalid).
// - `'-'` could be used as a unary operation (i.e., `"-1"` and `"-(2 + 3)"` is valid).
// - There will be no two consecutive operators in the input.
// - Every number and running calculation will fit in a signed 32-bit integer.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cctype>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

// Use Shunting Yard Algorithm
//
// Convert string to reverse Polish notation.
//
// Operator tiers: `unary -` > `*/` > `+-`.
//
// First split the string into tokens.
// For each token,
// if it is an number, push int into the number stack;
// if it is an operator, push it into the operator stack.
// Note that before pushing in to the operator stack,
// you should pop all operators with greater or equal tier.
// If the operator is `)`, pop all until (include) `(`.
class Solution {
  class Token {
   public:
    int num;
    char op;  // '#': number, 'p': unary plus sign, 'm': unary minus sign
  };

 public:
  unordered_map<char, int> tierMap = {
      {'p', 3}, {'m', 3}, {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1},
  };

  int calculate(string s) {
    // Tokenization
    int n = s.size();
    auto tokens = vector<Token>();
    auto prevOp = '\0';
    for (auto i = 0; i < n; i++) {
      if (s[i] == ' ') continue;

      // number
      if (isdigit(s[i])) {
        int num = s[i] - '0';
        while ((i + 1 < n) && isdigit(s[i + 1])) {
          i++;
          num *= 10;
          num += s[i] - '0';
        }
        tokens.push_back({num, '#'});
        prevOp = '#';
        continue;
      }

      // Convert unary plus/minus operators
      if (prevOp != '#' && prevOp != ')') {
        if (s[i] == '+') {
          s[i] = 'p';
        } else if (s[i] == '-') {
          s[i] = 'm';
        }
      }

      // operator
      tokens.push_back({0, s[i]});
      prevOp = s[i];
    }

    // Convert to reverse Polish notation.
    auto numops = vector<Token>();  // numbers & operators
    auto nums = stack<int>();       // only numbers
    auto ops = stack<char>();       // only operators
    ops.push('(');                  // avoid empty check
    for (auto &token : tokens) {
      if (token.op == '#') {
        numops.push_back(token);
        prevOp = 'n';
        continue;
      }

      switch (token.op) {
        case '(': {
          ops.push(token.op);
          break;
        }
        case 'p':
        case 'm': {
          while (tierMap[ops.top()] >= 3) {
            numops.push_back({0, ops.top()});
            ops.pop();
          }
          ops.push(token.op);
          break;
        }
        case '*':
        case '/': {
          while (tierMap[ops.top()] >= 2) {
            numops.push_back({0, ops.top()});
            ops.pop();
          }
          ops.push(token.op);
          break;
        }
        case '+':
        case '-': {
          while (tierMap[ops.top()] >= 1) {
            numops.push_back({0, ops.top()});
            ops.pop();
          }
          ops.push(token.op);
          break;
        }
        case ')': {
          while (ops.top() != '(') {
            numops.push_back({0, ops.top()});
            ops.pop();
          }
          ops.pop();  // Now top must be (
          // no need to push
          break;
        }
      }
      prevOp = token.op;
    }
    while (ops.size() > 1) {
      numops.push_back({0, ops.top()});
      ops.pop();
    }

    // Apply reverse polish notations
    for (auto &token : numops) {
      if (token.op == '#') {
        nums.push(token.num);
      } else {
        switch (token.op) {
          case 'p': {
            break;
          }
          case 'm': {
            auto num1 = nums.top();
            nums.pop();
            nums.push(-num1);
            break;
          }
          case '+': {
            auto num2 = nums.top();
            nums.pop();
            auto num1 = nums.top();
            nums.pop();
            nums.push(num1 + num2);
            break;
          }
          case '-': {
            auto num2 = nums.top();
            nums.pop();
            auto num1 = nums.top();
            nums.pop();
            nums.push(num1 - num2);
            break;
          }
          case '*': {
            auto num2 = nums.top();
            nums.pop();
            auto num1 = nums.top();
            nums.pop();
            nums.push(num1 * num2);
            break;
          }
          case '/': {
            auto num2 = nums.top();
            nums.pop();
            auto num1 = nums.top();
            nums.pop();
            nums.push(num1 / num2);
            break;
          }
        }
      }
    }

    return nums.top();
  }
};
