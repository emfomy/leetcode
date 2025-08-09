// Source: https://leetcode.com/problems/substring-with-concatenation-of-all-words
// Title: Substring with Concatenation of All Words
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` and an array of strings `words`. All the strings of `words` are of **the same length**.
//
// A **concatenated string** is a string that exactly contains all the strings of any permutation of `words` concatenated.
//
// - For example, if `words = ["ab","cd","ef"]`, then `"abcdef"`, `"abefcd"`, `"cdabef"`, `"cdefab"`, `"efabcd"`, and `"efcdab"` are all concatenated strings. `"acdbef"` is not a concatenated string because it is not the concatenation of any permutation of `words`.
//
// Return an array of the starting indices of all the concatenated substrings in `s`. You can return the answer in **any order**.
//
// **Example 1:**
//
// ```
// Input: s = "barfoothefoobarman", words = ["foo","bar"]
//
// Output: [0,9]
//
// Explanation:
//
// The substring starting at 0 is `"barfoo"`. It is the concatenation of `["bar","foo"]` which is a permutation of `words`.<br>
// The substring starting at 9 is `"foobar"`. It is the concatenation of `["foo","bar"]` which is a permutation of `words`.
//
// **Example 2:**
//
// ```
// Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
// Output: []
// Explanation:
// There is no concatenated substring.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
// Output: [6,9,12]
// Explanation:
//   The substring starting at 6 is `"foobarthe"`. It is the concatenation of `["foo","bar","the"]`.<br>
//   The substring starting at 9 is `"barthefoo"`. It is the concatenation of `["bar","the","foo"]`.<br>
//   The substring starting at 12 is `"thefoobar"`. It is the concatenation of `["the","foo","bar"]`.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^4`
// - `1 <= words.length <= 5000`
// - `1 <= words[i].length <= 30`
// - `s` and `words[i]` consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Use Hash Map
class Solution {
 public:
  vector<int> findSubstring(string s, vector<string>& words) {
    int n = words.size();
    int l = words[0].size();
    int m = s.size();
    if (m - n * l < 0) {
      return {};
    }

    // Count words
    unordered_map<string, int> wordMap;
    vector<int> wordCounter(n + 1);
    auto wordCount = 1;  // reserve 0 for invalid word
    for (auto i = 0; i < n; i++) {
      auto& word = words[i];
      if (!wordMap.count(word)) {
        wordMap[word] = wordCount;
        wordCount++;
      }
      wordCounter[wordMap[word]]++;
    }

    // Check word in string
    vector<int> sIdx(m - l + 1);
    for (auto i = 0; i <= m - l; i++) {
      auto word = s.substr(i, l);
      if (wordMap.count(word)) {
        sIdx[i] = wordMap[word];
      }
    }

    // Find answer
    vector<int> ans;
    for (auto i = 0; i <= m - n * l; i++) {
      if (sIdx[i] == 0) {
        continue;
      }

      vector<int> counter(wordCounter);  // copy counter
      auto valid = true;
      for (auto j = i; j < i + n * l; j += l) {
        auto idx = sIdx[j];
        if (counter[idx] == 0) {
          valid = false;
          break;
        }
        counter[idx]--;
      }
      if (valid) {
        ans.push_back(i);
      }
    }

    return ans;
  }
};

// Use Hash Map + Sliding Window
//
// Let l be the length of the word.
// Use sliding window on each starting in [0, l).
class Solution2 {
 public:
  vector<int> findSubstring(string s, vector<string>& words) {
    int n = words.size();
    int l = words[0].size();
    int m = s.size();
    if (m - n * l < 0) {
      return {};
    }

    // Count words
    unordered_map<string, int> wordMap;
    vector<int> wordCounter(n + 1);
    auto wordCount = 1;  // reserve 0 for invalid word
    for (auto i = 0; i < n; i++) {
      auto& word = words[i];
      if (!wordMap.count(word)) {
        wordMap[word] = wordCount;
        wordCount++;
      }
      wordCounter[wordMap[word]]++;
    }

    // Check word in string
    vector<int> sIdx(m + 1);
    for (auto i = 0; i + l <= m; i++) {
      auto word = s.substr(i, l);
      if (wordMap.count(word)) {
        sIdx[i] = wordMap[word];
      }
    }

    // Sliding Window
    vector<int> ans;
    vector<int> ansCounter(wordCount);
    for (auto start = 0; start < l; start++) {
      fill(ansCounter.begin(), ansCounter.end(), 0);
      auto left = start;
      auto right = start + n * l;

      int valids = 1;  // invalid count is zero
      for (auto j = left; j < right; j += l) {
        auto idx = sIdx[j];

        if (ansCounter[idx] == wordCounter[idx]) valids--;
        ansCounter[idx]++;
        if (ansCounter[idx] == wordCounter[idx]) valids++;
      }

      while (right <= m) {
        if (valids == wordCount) {
          ans.push_back(left);
        }

        // remove left
        auto leftIdx = sIdx[left];
        if (ansCounter[leftIdx] == wordCounter[leftIdx]) valids--;
        ansCounter[leftIdx]--;
        if (ansCounter[leftIdx] == wordCounter[leftIdx]) valids++;

        // add right
        auto rightIdx = sIdx[right];
        if (ansCounter[rightIdx] == wordCounter[rightIdx]) valids--;
        ansCounter[rightIdx]++;
        if (ansCounter[rightIdx] == wordCounter[rightIdx]) valids++;

        // shift
        left += l;
        right += l;
      }
    }

    return ans;
  }
};
