// Source: https://leetcode.com/problems/rearrange-string-k-distance-apart
// Title: Rearrange String k Distance Apart
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` and an integer `k`, rearrange `s` such that the same characters are **at least** distance `k` from each other. If it is not possible to rearrange the string, return an empty string `""`.
//
// **Example 1:**
//
// ```
// Input: s = "aabbcc", k = 3
// Output: "abcabc"
// Explanation: The same letters are at least a distance of 3 from each other.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aaabc", k = 3
// Output: ""
// Explanation: It is not possible to rearrange the string.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "aaadbbcc", k = 2
// Output: "abacabcd"
// Explanation: The same letters are at least a distance of 2 from each other.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 3 * 10^5`
// - `s` consists of only lowercase English letters.
// - `0 <= k <= s.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <queue>
#include <string>

using namespace std;

// Queue + Heap
//
// First count the letters.
// It is always better to pick the letter with more remaining.
//
// We use a queue to track the next possible index of each letter.
// If a letter is available, we put it into a heap, ordered by the remaining count.
class Solution {
  using QueueItem = pair<int, char>;  // index, letter
  using HeapItem = pair<int, char>;   // count, letter

 public:
  string rearrangeString(const string &s, const int k) {
    const int n = s.size();

    // Trivial case
    if (k <= 1) return s;

    // Count letters
    auto counter = array<int, 128>{};
    for (char c : s) ++counter[c];

    // Put non-zero letters into heap
    auto heap = priority_queue<HeapItem>();
    for (int c = 'a'; c <= 'z'; ++c) {  // only lowercases
      if (counter[c] > 0) heap.emplace(counter[c], c);
    }

    // Prepare queue
    auto que = queue<QueueItem>();

    // Simulation
    string ans;
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
      // Pop from queue
      // Note that this `while` could be `if` since we only push one letter per loop
      while (!que.empty() && que.front().first <= i) {
        char c = que.front().second;
        que.pop();
        heap.emplace(counter[c], c);
      }

      // Check availability
      if (heap.empty()) return "";

      // Pop from heap
      auto [_, c] = heap.top();
      heap.pop();
      ans += c;
      --counter[c];

      // Push into queue
      if (counter[c] > 0) {
        que.emplace(i + k, c);
      }
    }

    return ans;
  }
};

// Greedy
//
// Since there are at most 26 letters,
// we can simply scan all letters instead of using queue & heap.
class Solution2 {
 public:
  string rearrangeString(const string &s, const int k) {
    const int n = s.size();

    // Trivial case
    if (k <= 1) return s;

    // Count letters
    auto counter = array<int, 128>{};
    for (char c : s) ++counter[c];

    // Store next free index
    auto nextFree = array<int, 128>{};

    // Simulation
    string ans;
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
      // Find free letter with maximum count
      int maxCount = 0;
      char maxCh = -1;
      for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (nextFree[ch] <= i && counter[ch] > maxCount) {
          maxCount = counter[ch];
          maxCh = ch;
        }
      }

      // Check availability
      if (maxCh == -1) return "";

      // Use letter
      ans += maxCh;
      --counter[maxCh];
      nextFree[maxCh] = i + k;
    }

    return ans;
  }
};
