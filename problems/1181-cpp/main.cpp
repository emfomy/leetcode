// Source: https://leetcode.com/problems/before-and-after-puzzle
// Title: Before and After Puzzle
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a list of `phrases`, generate a list ofBefore and After puzzles.
//
// A phrase is a string that consists of lowercase English letters and spaces only. No space appears in the start or the end of a phrase. There areno consecutive spacesin a phrase.
//
// Before and After puzzles are phrases that are formed by merging two phrases where the **lastword of the firstphrase** is the same as the **first word of the second phrase**.
//
// Return theBefore and After puzzles that can be formed by every two phrases`phrases[i]`and`phrases[j]`where`i != j`. Note that the order of matching two phrases matters, we want to consider both orders.
//
// You should return a list of**distinct**strings **sorted lexicographically**.
//
// **Example 1:**
//
// ```
// Input: phrases = ["writing code","code rocks"]
// Output: ["writing code rocks"]
// ```
//
// **Example 2:**
//
// ```
// Input: phrases = ["mission statement",
//                   "a quick bite to eat",
//                  "a chip off the old block",
//                  "chocolate bar",
//                  "mission impossible",
//                  "a man on a mission",
//                  "block party",
//                  "eat my words",
//                  "bar of soap"]
// Output: ["a chip off the old block party",
//         "a man on a mission impossible",
//         "a man on a mission statement",
//         "a quick bite to eat my words",
//          "chocolate bar of soap"]
// ```
//
// **Example 3:**
//
// ```
// Input: phrases = ["a","b","a"]
// Output: ["a"]
// ```
//
// **Constraints:**
//
// - `1 <= phrases.length <= 100`
// - `1 <= phrases[i].length <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <set>
#include <string>
#include <vector>

using namespace std;

// Naive
class Solution {
 public:
  vector<string> beforeAndAfterPuzzles(vector<string>& phrases) {
    int n = phrases.size();

    // Helper
    auto getPrefix = [](string str) -> string {
      auto pos = str.find(' ');
      if (pos == string::npos) return str;
      return str.substr(0, pos);
    };
    auto getSuffix = [](string str) -> string {
      auto pos = str.rfind(' ');
      if (pos == string::npos) return str;
      return str.substr(pos + 1);
    };

    // Get answer
    auto ansSet = set<string>();
    for (auto i = 0; i < n; i++) {
      auto phrase1 = phrases[i];
      auto suffix1 = getSuffix(phrase1);
      auto prefix1 = phrase1.substr(0, phrase1.size() - suffix1.size());
      for (auto j = 0; j < n; j++) {
        if (i == j) continue;
        auto phrase2 = phrases[j];
        auto prefix2 = getPrefix(phrase2);
        if (suffix1 == prefix2) {
          ansSet.insert(prefix1 + phrase2);
        }
      }
    }

    // Convert set to vector
    auto ans = vector<string>();
    for (auto str : ansSet) {
      ans.push_back(str);
    }

    return ans;
  }
};
