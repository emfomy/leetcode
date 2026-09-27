// Source: https://leetcode.com/problems/brace-expansion-ii
// Title: Brace Expansion II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Under the grammar given below, strings can represent a set of lowercase words. Let`R(expr)`denote the set of words the expression represents.
//
// The grammar can best be understood through simple examples:
//
// - Single letters represent a singleton set containing that word.
//
//   - `R("a") = {"a"}`
//   - `R("w") = {"w"}`
//
// - When we take a comma-delimited list of two or more expressions, we take the union of possibilities.
//
//   - `R("{a,b,c}") = {"a","b","c"}`
//   - `R("{{a,b},{b,c}}") = {"a","b","c"}` (notice the final set only contains each word at most once)
//
// - When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
//
//   - `R("{a,b}{c,d}") = {"ac","ad","bc","bd"}`
//   - `R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}`
//
// Formally, the three rules for our grammar:
//
// - For every lowercase letter `x`, we have `R(x) = {x}`.
// - For expressions `e_1, e_2, ... , e_k` with `k >= 2`, we have `R({e_1, e_2, ...}) = R(e_1) ∪ R(e_2) ∪ ...`
// - For expressions `e_1` and `e_2`, we have `R(e_1 + e_2) = {a + b for (a, b) in R(e_1) × R(e_2)}`, where `+` denotes concatenation, and `×` denotes the cartesian product.
//
// Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.
//
// **Example 1:**
//
// ```
// Input: expression = "{a,b}{c,{d,e}}"
// Output: ["ac","ad","ae","bc","bd","be"]
// ```
//
// **Example 2:**
//
// ```
// Input: expression = "{{a,z},a{b,c},{ab,z}}"
// Output: ["a","ab","ac","z"]
// Explanation: Each distinct word is written only once in the final answer.
// ```
//
// **Constraints:**
//
// - `1 <= expression.length <= 60`
// - `expression[i]` consists of `'{'`, `'}'`, `','`or lowercase English letters.
// - The given`expression`represents a set of words based on the grammar given in the description.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution {
  using Result = set<string>;

  class Parser {
    const string &src;
    int idx;

   public:
    Parser(const string &src) : src(src), idx(0) {};
    Result parse() { return expr(); }

   private:
    // item -> letter | { expr }
    Result item() {
      Result res;
      if (src[idx] == '{') {
        ++idx;
        res = expr();
      } else {
        res.insert(string(1, src[idx]));
      }
      ++idx;

      return res;
    }

    // term -> item | item term
    Result term() {
      const int n = src.size();
      Result res = {""};

      while (idx < n && src[idx] != '}' && src[idx] != ',') {
        auto sub = item();  // parse next item
        Result tmp;
        for (const string &left : res) {
          for (const string &right : sub) {
            tmp.insert(left + right);
          }
        }
        res = std::move(tmp);
      }

      return res;
    }

    // expr -> term | term, expr
    Result expr() {
      const int n = src.size();
      Result res = {};

      while (true) {
        res.merge(term());  // parse next term

        if (idx < n && src[idx] == ',') {
          ++idx;
          continue;
        } else {
          break;
        }
      }

      return res;
    }
  };

 public:
  vector<string> braceExpansionII(const string &expr) {
    auto res = Parser(expr).parse();

    return vector<string>(res.cbegin(), res.cend());
  }
};
