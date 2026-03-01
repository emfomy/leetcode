// Source: https://leetcode.com/problems/long-pressed-name
// Title: Long Pressed Name
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Your friend is typing his `name` into a keyboard. Sometimes, when typing a character `c`, the key might get long pressed, and the character will be typed 1 or more times.
//
// You examine the `typed` characters of the keyboard. Return `True` if it is possible that it was your friends name, with some characters (possibly none) being long pressed.
//
// **Example 1:**
//
// ```
// Input: name = "alex", typed = "aaleex"
// Output: true
// Explanation: 'a' and 'e' in 'alex' were long pressed.
// ```
//
// **Example 2:**
//
// ```
// Input: name = "saeed", typed = "ssaaedd"
// Output: false
// Explanation: 'e' must have been pressed twice, but it was not in the typed output.
// ```
//
// **Constraints:**
//
// - `1 <= name.length, typed.length <= 1000`
// - `name` and `typed` consist of only lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// Group same letters
class Solution {
 public:
  bool isLongPressedName(const string& name, const string& typed) {
    // Grouping
    const auto nameGroup = groupify(name);
    const auto typedGroup = groupify(typed);

    // Check size
    const int n = nameGroup.size();
    if (typedGroup.size() != n) return false;

    // Check groups
    for (int i = 0; i < n; ++i) {
      // Check letter
      if (nameGroup[i].first != typedGroup[i].first) return false;

      // Check count
      if (nameGroup[i].second > typedGroup[i].second) return false;
    }

    return true;
  }

 private:
  vector<pair<char, int>> groupify(const string& str) {
    auto groups = vector<pair<char, int>>();
    groups.reserve(str.size());

    int count = 0;
    char prevCh = '\0';
    for (char ch : str) {
      if (ch != prevCh) {
        if (prevCh != '\0') groups.emplace_back(prevCh, count);
        count = 0;
        prevCh = ch;
      }
      ++count;
    }
    if (prevCh != '\0') groups.emplace_back(prevCh, count);

    return groups;
  }
};

// Two Pointer
class Solution2 {
 public:
  bool isLongPressedName(const string& name, const string& typed) {
    const int nLen = name.size(), tLen = typed.size();

    // Trivial case
    if (nLen > tLen) return false;

    // Loop
    int nIdx = 0;
    for (int tIdx = 0; tIdx < tLen; ++tIdx) {
      // Check normal press
      if (nIdx < nLen && typed[tIdx] == name[nIdx]) {
        ++nIdx;
        continue;
      }

      // Check long press
      if (tIdx > 0 && typed[tIdx] == typed[tIdx - 1]) {
        continue;
      }

      // Invalid
      return false;
    }

    // Check if we used all letters
    return nIdx == nLen;
  }
};
