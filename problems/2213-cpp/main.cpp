// Source: https://leetcode.com/problems/longest-substring-of-one-repeating-character
// Title: Longest Substring of One Repeating Character
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** string `s`. You are also given a **0-indexed** string `queryCharacters` of length `k` and a **0-indexed** array of integer **indices** `queryIndices` of length `k`, both of which are used to describe `k` queries.
//
// The `i^th` query updates the character in `s` at index `queryIndices[i]` to the character `queryCharacters[i]`.
//
// Return an array `lengths` of length `k` where `lengths[i]` is the **length** of the **longest substring** of `s` consisting of **only one repeating** character **after** the `i^th` query is performed.
//
// **Example 1:**
//
// ```
// Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
// Output: [3,3,4]
// Explanation:
// - 1^st query updates s = "b**b**bacc". The longest substring consisting of one repeating character is "bbb" with length 3.
// - 2^nd query updates s = "bbb**c**cc".
//   The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
// - 3^rd query updates s = "bbb**b**cc". The longest substring consisting of one repeating character is "bbbb" with length 4.
// Thus, we return [3,3,4].
// ```
//
// **Example 2:**
//
// ```
// Input: s = "abyzz", queryCharacters = "aa", queryIndices = [2,1]
// Output: [2,3]
// Explanation:
// - 1^st query updates s = "ab**a**zz". The longest substring consisting of one repeating character is "zz" with length 2.
// - 2^nd query updates s = "a**a**azz". The longest substring consisting of one repeating character is "aaa" with length 3.
// Thus, we return [2,3].
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` consists of lowercase English letters.
// - `k == queryCharacters.length == queryIndices.length`
// - `1 <= k <= 10^5`
// - `queryCharacters` consists of lowercase English letters.
// - `0 <= queryIndices[i] < s.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

// Tree Map
//
// Use a tree set (sep indices) to encode the string into chunks with only repeating characters.
// Use another tree map (or multi-set) for the histogram of chunk length.
// For each query, find the chunk inside the tree map, and split/merge the chunks.
class Solution {
  struct Histogram {
    map<int, int> data;

    void insert(int val) {  //
      ++data[val];
    }

    void remove(int val) {  //
      if (--data[val] == 0) data.erase(val);
    }

    int max() {  //
      return data.rbegin()->first;
    }
  };

  struct Chunks {
    Histogram hist;
    set<int> seps;
    int n;

    Chunks(const string& s) {
      n = s.size();
      for (int i = 0; i < n;) {
        char ch = s[i];
        int i0 = i;
        while (++i < n && s[i] == ch);
        int len = i - i0;
        seps.insert(i0);
        hist.insert(len);
      }
      seps.insert(n);
    }

    // Split chunk at index
    void split(int idx) {
      auto it = --seps.upper_bound(idx);  // find chunk before or equal to idx
      int start = *it;
      int end = *next(it);

      if (idx == start) return;  // no-op

      seps.insert(idx);
      hist.remove(end - start);
      hist.insert(idx - start);
      hist.insert(end - idx);
    }

    // Merge chunk at index
    void merge(int idx) {
      if (idx == 0 || idx == n) return;  // no-op

      auto it = seps.find(idx);  // must exist
      int before = *prev(it);
      int after = *next(it);

      seps.erase(idx);
      hist.remove(idx - before);
      hist.remove(after - idx);
      hist.insert(after - before);
    }
  };

 public:
  vector<int> longestRepeating(string s, const string& queryCharacters, const vector<int>& queryIndices) {
    const int n = s.size();
    const int q = queryCharacters.size();

    auto chunks = Chunks(s);

    // Loop
    auto ans = vector<int>();
    ans.reserve(q);
    for (auto i = 0; i < q; ++i) {
      int idx = queryIndices[i];

      char beforeCh = s[idx];
      char afterCh = queryCharacters[i];

      // Skip no-op
      if (beforeCh != afterCh) {
        // Check left
        if (idx > 0) {
          if (s[idx - 1] == beforeCh) {  // insert sep
            chunks.split(idx);
          } else if (s[idx - 1] == afterCh) {  // remove sep
            chunks.merge(idx);
          }
        }

        // Check right
        if (idx < n) {
          if (s[idx + 1] == beforeCh) {  // insert sep
            chunks.split(idx + 1);
          } else if (s[idx + 1] == afterCh) {  // remove sep
            chunks.merge(idx + 1);
          }
        }

        // Update char
        s[idx] = afterCh;
      }

      ans.push_back(chunks.hist.max());
    }

    return ans;
  }
};
