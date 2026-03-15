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
// Input: s = "3[a]2[bc]"
// Output: "aaabcbc"
// ```
//
// **Example 2:**
//
// ```
// Input: s = "3[a2[c]]"
// Output: "accaccacc"
// ```
//
// **Example 3:**
//
// ```
// Input: s = "2[abc]3[cd]ef"
// Output: "abcabccdcdcdef"
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

#include <cassert>
#include <cctype>
#include <charconv>
#include <cstddef>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

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

// Tokenize + Parser + AST
//
// expr   := str | repeat
// group  := expr*
// repeat := num '[' group ']'
//
class Solution3 {
  struct Token {
    enum Type { NONE, STR, NUM, LBRACK, RBRACK };

    Type type;
    int start, end;
  };

  class Lexer {
   public:
    vector<Token> lex(const string_view s) const {
      const int n = s.size();
      auto tokens = vector<Token>();
      Token token{Token::NONE, 0};

      for (int i = 0; i <= n; ++i) {
        char ch = s[i];

        // Parse type
        Token::Type type = Token::NONE;
        bool forceNew = false;
        if (i < n) {
          if (isalpha(ch)) {
            type = Token::STR;
          } else if (isdigit(ch)) {
            type = Token::NUM;
          } else if (ch == '[') {
            type = Token::LBRACK;
            forceNew = true;
          } else if (ch == ']') {
            type = Token::RBRACK;
            forceNew = true;
          }
        }

        // Push token
        if (type != token.type || forceNew) {
          if (token.type != Token::NONE) {
            token.end = i;
            tokens.push_back(token);
          }
          token.type = type;
          token.start = i;
        }
      }
      return tokens;
    }
  };

  struct Node {
    virtual ~Node() = default;
    virtual string decode(const string_view s) const = 0;
  };

  struct ExprNode : Node {};

  struct StrNode : ExprNode {
    int start, end;

    StrNode(int start, int end) : start(start), end(end) {}

    string decode(const string_view s) const override {
      return string(s.substr(start, end - start));  //
    }
  };

  struct NumNode : Node {
    int num;

    NumNode(const string_view s, int start, int end) {
      from_chars(&s[start], &s[end], num);  //
    }

    string decode(const string_view s) const override {
      return "";  // num should not be decoded
    }
  };

  struct GroupNode : Node {
    vector<ExprNode*> children;

    ~GroupNode() {
      for (auto node : children) {
        delete node;
      }
    }

    string decode(const string_view s) const override {
      string out;
      for (auto* child : children) out += child->decode(s);
      return out;
    }
  };

  struct RepeatNode : ExprNode {
    NumNode* num;
    GroupNode* body;

    ~RepeatNode() {
      delete num;
      delete body;
    }

    string decode(const string_view s) const override {
      string out;
      string sub = body->decode(s);
      for (int i = 0; i < num->num; ++i) out += sub;
      return out;
    }
  };

  struct Parser {
   public:
    GroupNode* parse(const string_view s, vector<Token>& tokens) const {
      int i = 0;
      auto root = parseGroup(s, tokens, i);
      assert(i == tokens.size());
      return root;
    }

   private:
    GroupNode* parseGroup(const string_view s, vector<Token>& tokens, int& i) const {
      auto group = new GroupNode();
      while (i < tokens.size() && tokens[i].type != Token::RBRACK) {
        group->children.push_back(parseExpr(s, tokens, i));
      }
      return group;
    }

    ExprNode* parseExpr(const string_view s, vector<Token>& tokens, int& i) const {
      assert(i < tokens.size());

      if (tokens[i].type == Token::STR) {
        auto node = new StrNode(tokens[i].start, tokens[i].end);
        ++i;
        return node;
      }

      if (tokens[i].type == Token::NUM) {
        auto repeat = new RepeatNode();
        repeat->num = new NumNode(s, tokens[i].start, tokens[i].end);
        ++i;
        assert(tokens[i].type == Token::LBRACK);
        ++i;
        repeat->body = parseGroup(s, tokens, i);
        assert(tokens[i].type == Token::RBRACK);
        ++i;
        return repeat;
      }

      assert(false);
      return nullptr;
    }
  };

  Lexer lexer;
  Parser parser;

 public:
  string decodeString(const string s) {
    int n = s.size();

    auto tokens = lexer.lex(s);
    auto tree = parser.parse(s, tokens);
    auto out = tree->decode(s);
    delete tree;

    return out;
  }
};
