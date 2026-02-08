// Source: https://leetcode.com/problems/decode-string
// Title: Decode String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an encoded string, return its decoded string.
//
// The encoding rule is: `k[encoded_string]`, where the `encoded_string` inside the square brackets is being repeated exactly `k` times. Note that `k` is guaranteed to be a positive integer.
//
// You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, `k`. For example, there will not be input like `3a` or `2[4]`.
//
// The test cases are generated so that the length of the output will never exceed `10^5`.
//
// **Example 1:**
//
// ```
// **Input:** s = "3[a]2[bc]"
// **Output:** "aaabcbc"
// ```
//
// **Example 2:**
//
// ```
// **Input:** s = "3[a2[c]]"
// **Output:** "accaccacc"
// ```
//
// **Example 3:**
//
// ```
// **Input:** s = "2[abc]3[cd]ef"
// **Output:** "abcabccdcdcdef"
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 30`
// - `s` consists of lowercase English letters, digits, and square brackets `'[]'`.
// - `s` is guaranteed to be **a valid** input.
// - All the integers in `s` are in the range `[1, 300]`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cctype>
#include <stack>
#include <string>

using namespace std;

// Tokenizer
class Solution {
 public:
  string decodeString(string s) {
    int n = s.size();

    // Tokenize
    auto tokens = stack<string>();
    tokens.push("1");  // convert to 1[s]
    for (int i = 0; i < n; ++i) {
      // Parse string
      if (isalpha(s[i])) {
        int start = i;
        for (; i < n && isalpha(s[i]); ++i);
        tokens.push(s.substr(start, i - start));
        --i;
        continue;
      }

      // Parse number
      if (isdigit(s[i])) {
        int start = i;
        for (; i < n && isdigit(s[i]); ++i);
        tokens.push(s.substr(start, i - start));
        --i;
        continue;
      }

      // Parse bracket
      if (s[i] == ']') tokens.push("]");
    }
    tokens.push("]");  // convert to 1[s]

    // Decode
    auto strs = stack<string>();
    while (!tokens.empty()) {
      string token = tokens.top();
      tokens.pop();

      // string
      if (!isdigit(token[0])) {
        strs.push(token);
        continue;
      }

      // number
      auto num = stoi(token);

      // pop until ]
      string str = "";
      while (strs.top() != "]") {
        str += strs.top();
        strs.pop();
      }
      strs.pop();

      // repeat
      string repeated = "";
      for (int i = 0; i < num; ++i) repeated += str;
      strs.push(repeated);
    }

    return strs.top();
  }
};

// Stack
//
// Store prefix number and string into the stack
class Solution2 {
 public:
  string decodeString(string s) {
    auto st = stack<pair<int, string>>();

    int currNum = 0;
    string currStr = "";

    for (char c : s) {
      if (isdigit(c)) {
        currNum = currNum * 10 + (c - '0');
        continue;
      }

      if (isalpha(c)) {
        currStr += c;
        continue;
      }

      if (c == '[') {
        st.emplace(currNum, currStr);
        currNum = 0, currStr = "";
        continue;
      }

      if (c == ']') {
        auto [parentNum, parentStr] = st.top();
        st.pop();

        // Repeat
        for (int i = 0; i < parentNum; ++i) parentStr += currStr;

        swap(currStr, parentStr);
        continue;
      }

      // won't reach here
    }

    return currStr;
  }
};
