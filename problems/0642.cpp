// Source: https://leetcode.com/problems/design-search-autocomplete-system
// Title: Design Search Autocomplete System
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a special character `'#'`).
//
// You are given a string array `sentences` and an integer array `times` both of length `n` where `sentences[i]` is a previously typed sentence and `times[i]` is the corresponding number of times the sentence was typed. For each input character except `'#'`, return the top `3` historical hot sentences that have the same prefix as the part of the sentence already typed.
//
// Here are the specific rules:
//
// - The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
// - The returned top `3` hot sentences should be sorted by hot degree (The first is the hottest one). If several sentences have the same hot degree, use ASCII-code order (smaller one appears first).
// - If less than `3` hot sentences exist, return as many as you can.
// - When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
//
// Implement the `AutocompleteSystem` class:
//
// - `AutocompleteSystem(String[] sentences, int[] times)` Initializes the object with the `sentences` and `times` arrays.
// - `List<String> input(char c)` This indicates that the user typed the character `c`.
//
// - Returns an empty array `[]` if `c == '#'` and stores the inputted sentence in the system.
// - Returns the top `3` historical hot sentences that have the same prefix as the part of the sentence already typed. If there are fewer than `3` matches, return them all.
//
// **Example 1:**
//
// ```
// Input
//
// ["AutocompleteSystem", "input", "input", "input", "input"]
// [[["i love you", "island", "iroman", "i love leetcode"], [5, 3, 2, 2]], ["i"], [" "], ["a"], ["#"]]
// Output
//
// [null, ["i love you", "island", "i love leetcode"], ["i love you", "i love leetcode"], [], []]
//
// Explanation
//
// AutocompleteSystem obj = new AutocompleteSystem(["i love you", "island", "iroman", "i love leetcode"], [5, 3, 2, 2]);
// obj.input("i"); // return ["i love you", "island", "i love leetcode"]. There are four sentences that have prefix "i". Among them, "ironman" and "i love leetcode" have same hot degree. Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman". Also we only need to output top 3 hot sentences, so "ironman" will be ignored.
// obj.input(" "); // return ["i love you", "i love leetcode"]. There are only two sentences that have prefix "i ".
// obj.input("a"); // return []. There are no sentences that have prefix "i a".
// obj.input("#"); // return []. The user finished the input, the sentence "i a" should be saved as a historical sentence in system. And the following input will be counted as a new search.
// ```
//
// **Constraints:**
//
// - `n == sentences.length`
// - `n == times.length`
// - `1 <= n <= 100`
// - `1 <= sentences[i].length <= 100`
// - `1 <= times[i] <= 50`
// - `c` is a lowercase English letter, a hash `'#'`, or space `' '`.
// - Each tested sentence will be a sequence of characters `c` that end with the character `'#'`.
// - Each tested sentence will have a length in the range `[1, 200]`.
// - The words in each input sentence are separated by single spaces.
// - At most `5000` calls will be made to `input`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>

using namespace std;

// Trie + Hast Set
//
// Use a hash set to count the occurrences.
// Use a trie to store the sentences.
// For each node in the trie, store the top 3 sentences.
class AutocompleteSystem {
  struct Node {
    Node* children[128];
    vector<string> tops;

    void normalize(const unordered_map<string, int>& counts) {
      // Sort
      auto comp = [&counts](const string& a, const string& b) {  //
        return counts.at(a) != counts.at(b) ? counts.at(a) > counts.at(b) : a < b;
      };
      sort(tops.begin(), tops.end(), comp);

      // Trim
      while (tops.size() > 3) tops.pop_back();
    }
  };

  unordered_map<string, int> counts;
  Node* trie;

  Node* currNode;
  string currStr;

 public:
  AutocompleteSystem(vector<string>& sentences, vector<int>& times) : trie(new Node()) {
    const int n = sentences.size();

    // Count
    counts.reserve(n);
    for (int i = 0; i < n; ++i) {
      counts[sentences[i]] = times[i];
    }

    // Build trie
    for (const string& sentence : sentences) {
      Node* node = trie;
      for (char c : sentence) {
        // Step
        auto& nextNode = node->children[c];
        if (nextNode == nullptr) nextNode = new Node();
        node = nextNode;

        // Insert
        node->tops.push_back(sentence);
        node->normalize(counts);
      }
    }

    currNode = trie;
    currStr = "";
  }

  vector<string> input(char c) {
    if (c == '#') {
      update();
      return {};
    }

    currStr.push_back(c);
    auto& nextNode = currNode->children[c];
    if (nextNode == nullptr) nextNode = new Node();
    currNode = nextNode;
    return currNode->tops;
  }

 private:
  void update() {
    // Insert
    ++counts[currStr];
    Node* node = trie;
    for (char c : currStr) {
      // Step
      node = node->children[c];

      // Insert
      if (find(node->tops.cbegin(), node->tops.cend(), currStr) == node->tops.cend()) {
        node->tops.push_back(currStr);
      }
      node->normalize(counts);
    }

    // Reset
    currNode = trie;
    currStr = "";
  }
};
