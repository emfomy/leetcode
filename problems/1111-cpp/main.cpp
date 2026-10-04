// Source: https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings
// Title: Maximum Nesting Depth of Two Valid Parentheses Strings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A string is a valid parentheses string(denoted VPS) if and only if it consists of `"("` and `")"` characters only, and:
//
// - It is the empty string, or
// - It can be written as`AB`(`A`concatenated with`B`), where`A`and`B`are VPS's, or
// - It can be written as`(A)`, where`A`is a VPS.
//
// We cansimilarly define the nesting depth `depth(S)` of any VPS `S` as follows:
//
// - `depth("") = 0`
// - `depth(A + B) = max(depth(A), depth(B))`, where `A` and `B` are VPS's
// - `depth("(" + A + ")") = 1 + depth(A)`, where `A` is a VPS.
//
// For example, `""`,`"()()"`, and`"()(()())"`are VPS's (with nesting depths 0, 1, and 2), and `")("` and `"(()"` are not VPS's.
// Given a VPS seq, split it into two disjoint subsequences `A` and `B`, such that`A` and `B` are VPS's (and`A.length + B.length = seq.length`). The subsequences may not necessarily be contiguous.
// For example, for the sequence `123456789`, one possible split is:
// - `A = {1, 3, 5, 7, 9}`,
// - `B = {2, 4, 6, 8}`.
// This corresponds to the output `[0, 1, 0, 1, 0, 1, 0, 1, 0]` where 0 indicates membership in`A`and 1 indicates membership in`B`.
// Now choose **any** such `A` and `B` such that`max(depth(A), depth(B))` is the minimum possible value.
// Return an `answer` array (of length `seq.length`) that encodes such achoice of `A` and `B`: `answer[i] = 0` if `seq[i]` is part of `A`, else `answer[i] = 1`. Note that even though multiple answers may exist, you may return any of them.
//
// **Example 1:**
//
// ```
// Input: seq = "(()())"
// Output: [0,1,1,1,1,0]
// ```
//
// **Example 2:**
//
// ```
// Input: seq = "()(())()"
// Output: [0,0,0,1,1,0,1,1]
// ```
//
// **Constraints:**
//
// - `1 <= seq.size <= 10000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// Greedy
//
// The depth of a VPS is equal to the max depth of the parentheses.
// To minimize the split, we first compute the depth of each parentheses.
// We split the VPS using the parity of the parentheses depth.
class Solution {
 public:
  vector<int> maxDepthAfterSplit(const string &seq) {
    const int n = seq.size();

    auto ans = vector<int>();
    ans.reserve(n);

    int depth = 0;
    for (const char ch : seq) {
      if (ch == '(') {
        ++depth;
        ans.push_back(depth % 2);
      } else {
        ans.push_back(depth % 2);
        --depth;
      }
    }

    return ans;
  }
};

// Greedy
class Solution2 {
 public:
  vector<int> maxDepthAfterSplit(const string &seq) {
    const int n = seq.size();

    auto ans = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      ans[i] = (i & 1) ^ (seq[i] == '(');
    }

    return ans;
  }
};
