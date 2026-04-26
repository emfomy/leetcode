// Source: https://leetcode.com/problems/words-within-two-edits-of-dictionary
// Title: Words Within Two Edits of Dictionary
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two string arrays, `queries` and `dictionary`. All words in each array comprise of lowercase English letters and have the same length.
//
// In one **edit** you can take a word from `queries`, and change any letter in it to any other letter. Find all words from `queries` that, after a **maximum** of two edits, equal some word from `dictionary`.
//
// Return a list of all words from `queries`, that match with some word from `dictionary` after a maximum of **two edits**. Return the words in the **same order** they appear in `queries`.
//
// **Example 1:**
//
// ```
// Input: queries = ["word","note","ants","wood"], dictionary = ["wood","joke","moat"]
// Output: ["word","note","wood"]
// Explanation:
// - Changing the 'r' in "word" to 'o' allows it to equal the dictionary word "wood".
// - Changing the 'n' to 'j' and the 't' to 'k' in "note" changes it to "joke".
// - It would take more than 2 edits for "ants" to equal a dictionary word.
// - "wood" can remain unchanged (0 edits) and match the corresponding dictionary word.
// Thus, we return ["word","note","wood"].
// ```
//
// **Example 2:**
//
// ```
// Input: queries = ["yes"], dictionary = ["not"]
// Output: []
// Explanation:
// Applying any two edits to "yes" cannot make it equal to "not". Thus, we return an empty array.
// ```
//
// **Constraints:**
//
// - `1 <= queries.length, dictionary.length <= 100`
// - `n == queries[i].length == dictionary[j].length`
// - `1 <= n <= 100`
// - All `queries[i]` and `dictionary[j]` are composed of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_set>
#include <vector>

using namespace std;

// Hash Set
//
// For each word in dictionary, convert a single letter and put into the hash set.
//
// Next loop for each queries, do the same operation and find in the hash set.
class Solution {
 public:
  vector<string> twoEditWords(const vector<string>& queries, const vector<string>& dictionary) {
    // Trivial Case
    if (queries.empty()) return {};

    // Get sizes
    const int n = queries.size(), m = dictionary.size(), l = queries.front().size();

    // Convert to hash set
    auto dictSet = unordered_set<string>();
    dictSet.reserve(m * l);
    for (const string& word : dictionary) {
      for (int i = 0; i < l; ++i) {
        string edited = word;  // copy
        for (char c = 'a'; c <= 'z'; ++c) {
          edited[i] = c;
          dictSet.insert(edited);
        }
      }
    }

    // Helper
    const auto check = [l, &dictSet](const string& word) -> bool {
      for (int i = 0; i < l; ++i) {
        string edited = word;  // copy
        for (char c = 'a'; c <= 'z'; ++c) {
          edited[i] = c;
          if (dictSet.contains(edited)) return true;
        }
      }

      return false;
    };

    // Loop
    auto ans = vector<string>();
    ans.reserve(n);
    for (const string& query : queries) {
      if (check(query)) ans.push_back(query);
    }

    return ans;
  }
};

// Brute-Force
//
// Compare each query to dictionary word and check if the edit distance is less than 2.
class Solution2 {
 public:
  vector<string> twoEditWords(const vector<string>& queries, const vector<string>& dictionary) {
    // Helper
    const auto checkDist = [](const string& query, const string& target) -> bool {
      int d = 0;
      for (int i = 0; i < query.size(); ++i) {
        d += (query[i] != target[i]);
        if (d > 2) return false;
      }
      return true;
    };

    const auto check = [&checkDist, &dictionary](const string& query) -> bool {
      for (const string& target : dictionary) {
        if (checkDist(query, target)) return true;
      }
      return false;
    };

    // Loop
    auto ans = vector<string>();
    ans.reserve(queries.size());
    for (const string& query : queries) {
      if (check(query)) ans.push_back(query);
    }

    return ans;
  }
};
