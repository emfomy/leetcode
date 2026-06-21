// Source: https://leetcode.com/problems/process-string-with-special-operations-ii
// Title: Process String with Special Operations II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` consisting of lowercase English letters and the special characters: `'*'`, `'#'`, and `'%'`.

// You are also given an integer `k`.

// Build a new string `result` by processing `s` according to the following rules from left to right:

// - If the letter is a **lowercase** English letter append it to `result`.
// - A `'*'` **removes** the last character from `result`, if it exists.
// - A `'#'` **duplicates** the current `result` and **appends** it to itself.
// - A `'%'` **reverses** the current `result`.

// Return the `k^th` character of the final string `result`. If `k` is out of the bounds of `result`, return `'.'`.

// **Example 1:**
//
// ```
// Input: s = "a#b%*", k = 1
// Output: "ba"
// Explanation:
//
// | i | s[i] | Operation                 | Current result |
// |---|----- |---------------------------|----------------|
// | 0 | 'a'  | Append 'a'                | "a"            |
// | 1 | '#'  | Duplicate result          | "aa"           |
// | 2 | 'b'  | Append 'b'                | "aab"          |
// | 3 | '%'  | Reverse result            | "baa"          |
// | 4 | '*'  | Remove the last character | "ba"           |
//
// The final result is "ba". The character at index k = 1 is 'a'.

// **Example 2:**

// Input: s = "cd%#*#", k = 3
// Output: "d"
// Explanation:
//
// | i | s[i] | Operation                 | Current result |
// |---|----- |---------------------------|----------------|
// | 0 | 'c'  | Append 'c'                | "c"            |
// | 1 | 'd'  | Append 'd'                | "cd"           |
// | 2 | '%'  | Reverse result            | "dc"           |
// | 3 | '#'  | Duplicate result          | "dcdc"         |
// | 4 | '*'  | Remove the last character | "dcd"          |
// | 4 | '#'  | Duplicate result          | "dcddcd"       |
//
// The final `result` is `"dcddcd"`. The character at index `k = 3` is `'d'`.
//
// **Example 3:**
//
// Input: s = "z*#", k = 0
// Output: "."
// Explanation:
//
// | i | s[i] | Operation                 | Current result |
// |---|----- |---------------------------|----------------|
// | 0 | 'z'  | Append 'z'                | "z"            |
// | 1 | '*'  | Remove the last character | ""             |
// | 2 | '#'  | Duplicate the string      | ""             |
//
// The final `result` is `""`. Since index `k = 0` is out of bounds, the output is `'.'`.

// **Constraints:**

// - `1 <= s.length <= 10^5`
// - `s` consists of only lowercase English letters and special characters `'*'`, `'#'`, and `'%'`.
// - `0 <= k <= 10^15`
// - The length of `result` after processing `s` will not exceed `10^15`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// First dry-run to get the length of the final result.
// Next loop from the back to find the character.
class Solution {
  using Bool = unsigned char;

 public:
  char processStr(string s, long long k) {
    const int n = s.size();

    // Compute length
    auto noops = vector<Bool>(n);  // used for '*'
    long long l = 0;
    for (int i = 0; i < n; ++i) {
      const char ch = s[i];
      switch (ch) {
        case '*': {
          if (l > 0) {
            --l;
          } else {
            noops[i] = true;
          }
          break;
        }
        case '#': {
          l *= 2;
          break;
        }
        case '%': {
          break;
        }
        default: {
          ++l;
          break;
        }
      }
    }

    // Out of bound
    if (k >= l) return '.';

    // Find character
    for (int i = n - 1; i >= 0; --i) {
      const char ch = s[i];
      switch (ch) {
        case '*': {
          if (!noops[i]) ++l;
          break;
        }
        case '#': {
          l /= 2;
          k %= l;
          break;
        }
        case '%': {
          k = l - k - 1;
          break;
        }
        default: {
          --l;
          if (k == l) return ch;
          break;
        }
      }
    }

    return '.';
  }
};

// First dry-run to get the length of the final result.
// Next loop from the back to find the character.
//
// Note that we don't need to check '*' in reverse.
// If the string is empty at '*',
// then the answer won't be the letter before it.
class Solution2 {
  using Bool = unsigned char;

 public:
  char processStr(string s, long long k) {
    const int n = s.size();

    // Compute length
    long long l = 0;
    for (const char ch : s) {
      switch (ch) {
        case '*': {
          if (l > 0) --l;
          break;
        }
        case '#': {
          l *= 2;
          break;
        }
        case '%': {
          break;
        }
        default: {
          ++l;
          break;
        }
      }
    }

    // Out of bound
    if (k >= l) return '.';

    // Find character
    for (int i = n - 1; i >= 0; --i) {
      const char ch = s[i];
      switch (ch) {
        case '*': {
          ++l;
          break;
        }
        case '#': {
          l /= 2;
          k %= l;
          break;
        }
        case '%': {
          k = l - k - 1;
          break;
        }
        default: {
          --l;
          if (k == l) return ch;
          break;
        }
      }
    }

    return '.';
  }
};
