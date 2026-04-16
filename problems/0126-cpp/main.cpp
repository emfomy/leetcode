// Source: https://leetcode.com/problems/word-ladder
// Title: Word Ladder
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **transformation sequence** from word `beginWord` to word `endWord` using a dictionary `wordList` is a sequence of words `beginWord -> s_1 -> s_2 -> ... -> s_k` such that:
//
// - Every adjacent pair of words differs by a single letter.
// - Every `s_i` for `1 <= i <= k` is in `wordList`. Note that `beginWord` does not need to be in `wordList`.
// - `s_k == endWord`
//
// Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return the **number of words** in the **shortest transformation sequence** from `beginWord` to `endWord`, or `0` if no such sequence exists.
//
// **Example 1:**
//
// ```
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: 5
// Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
// ```
//
// **Example 2:**
//
// ```
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
// Output: 0
// Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
// ```
//
// **Constraints:**
//
// - `1 <= beginWord.length <= 10`
// - `endWord.length == beginWord.length`
// - `1 <= wordList.length <= 5000`
// - `wordList[i].length == beginWord.length`
// - `beginWord`, `endWord`, and `wordList[i]` consist of lowercase English letters.
// - `beginWord != endWord`
// - All the words in `wordList` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// BFS
//
// Say we have a word abc.
// We create wildcards *bc, a*c, ab*, and add edge between abc and these wildcards.
// Now apply BFS on beginWord and find the distance to endWord.
// The ladder length is half of the distance + 1.
class Solution {
  struct State {
    const string &word;
    int len;
  };

 public:
  int ladderLength(const string &beginWord, const string &endWord, const vector<string> &wordList) {
    const int n = wordList.size(), l = beginWord.size();

    // Trivial case
    if (beginWord == endWord) return 1;
    if (find(wordList.cbegin(), wordList.cend(), endWord) == wordList.cend()) return 0;

    // Build graph
    auto word2wild = unordered_map<string, vector<string>>();
    auto wild2word = unordered_map<string, vector<string>>();
    for (int i = 0; i < l; ++i) {  // being word might not in the list
      string wild = beginWord;     // copy
      wild[i] = '*';
      word2wild[beginWord].push_back(wild);
    }
    for (const string &word : wordList) {
      for (int i = 0; i < l; ++i) {
        string wild = word;  // copy
        wild[i] = '*';
        word2wild[word].push_back(wild);
        wild2word[wild].push_back(word);
      }
    }
    const int m = wild2word.size();

    // BFS
    auto wordSeen = unordered_set<string>();
    auto wildSeen = unordered_set<string>();
    auto que = queue<State>();
    wordSeen.reserve(n);
    wildSeen.reserve(m);

    wordSeen.insert(beginWord);
    que.push(State{beginWord, 1});

    while (!que.empty()) {
      const auto [word, len] = que.front();
      que.pop();

      // Traversal
      for (const string &wild : word2wild[word]) {
        if (wildSeen.contains(wild)) continue;  // relax
        wildSeen.insert(wild);

        for (const string &next : wild2word[wild]) {
          if (wordSeen.contains(next)) continue;  // relax

          // Found
          if (next == endWord) return len + 1;

          wordSeen.insert(next);
          que.push(State{next, len + 1});
        }
      }
    }

    return 0;
  }
};
