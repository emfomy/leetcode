// Source: https://leetcode.com/problems/vowel-spellchecker
// Title: Vowel Spellchecker
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a `wordlist`, we want to implement a spellchecker that converts a query word into a correct word.
//
// For a given `query` word, the spell checker handles two categories of spelling mistakes:
//
// - Capitalization: If the query matches a word in the wordlist (**case-insensitive**), then the query word is returned with the same case as the case in the wordlist.
//
// - Example: `wordlist = ["yellow"]`, `query = "YellOw"`: `correct = "yellow"`
// - Example: `wordlist = ["Yellow"]`, `query = "yellow"`: `correct = "Yellow"`
// - Example: `wordlist = ["yellow"]`, `query = "yellow"`: `correct = "yellow"`
//
// - Vowel Errors: If after replacing the vowels `('a', 'e', 'i', 'o', 'u')` of the query word with any vowel individually, it matches a word in the wordlist (**case-insensitive**), then the query word is returned with the same case as the match in the wordlist.
//
// - Example: `wordlist = ["YellOw"]`, `query = "yollow"`: `correct = "YellOw"`
// - Example: `wordlist = ["YellOw"]`, `query = "yeellow"`: `correct = ""` (no match)
// - Example: `wordlist = ["YellOw"]`, `query = "yllw"`: `correct = ""` (no match)
//
// In addition, the spell checker operates under the following precedence rules:
//
// - When the query exactly matches a word in the wordlist (**case-sensitive**), you should return the same word back.
// - When the query matches a word up to capitlization, you should return the first such match in the wordlist.
// - When the query matches a word up to vowel errors, you should return the first such match in the wordlist.
// - If the query has no matches in the wordlist, you should return the empty string.
//
// Given some `queries`, return a list of words `answer`, where `answer[i]` is the correct word for `query = queries[i]`.
//
// **Example 1:**
//
// ```
// Input: wordlist = ["KiTe","kite","hare","Hare"], queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
// Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
// ```
//
// **Example 2:**
//
// ```
// Input: wordlist = ["yellow"], queries = ["YellOw"]
// Output: ["yellow"]
// ```
//
// **Constraints:**
//
// - `1 <= wordlist.length, queries.length <= 5000`
// - `1 <= wordlist[i].length, queries[i].length <= 7`
// - `wordlist[i]` and `queries[i]` consist only of only English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cctype>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
    auto wordSet = unordered_set<string>();
    auto lowerMap = unordered_map<string, string>();
    auto errorMap = unordered_map<string, string>();

    // Helper
    auto toLower = [](string s) -> string {  //
      for (auto& ch : s) {
        ch |= 0x20;
      }
      return s;
    };
    auto toError = [](string s) -> string {  //
      for (auto& ch : s) {
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
          ch = '*';
        }
      }
      return s;
    };

    // Maps
    for (auto it = wordlist.crbegin(); it != wordlist.crend(); ++it) {
      auto& word = *it;
      auto lower = toLower(word);
      auto error = toError(lower);
      wordSet.insert(word);
      lowerMap[lower] = word;
      errorMap[error] = word;
    }

    // Queries
    auto ans = vector<string>();
    for (auto& query : queries) {
      if (wordSet.contains(query)) {
        ans.push_back(query);
        continue;
      }

      auto lower = toLower(query);
      auto lowerIt = lowerMap.find(lower);
      if (lowerIt != lowerMap.cend()) {
        ans.push_back(lowerIt->second);
        continue;
      }

      auto error = toError(lower);
      auto errorIt = errorMap.find(error);
      if (errorIt != errorMap.cend()) {
        ans.push_back(errorIt->second);
        continue;
      }

      ans.push_back("");
    }

    return ans;
  }
};
