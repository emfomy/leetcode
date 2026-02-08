// Source: https://leetcode.com/problems/unique-substrings-with-equal-digit-frequency
// Title: Unique Substrings With Equal Digit Frequency
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a digit string `s`, return the number of **unique substrings **of `s` where every digit appears the same number of times.
//
// **Example 1:**
//
// ```
// **Input:** s = "1212"
// **Output:** 5
// **Explanation:** The substrings that meet the requirements are "1", "2", "12", "21", "1212".
// Note that although the substring "12" appears twice, it is only counted once.
// ```
//
// **Example 2:**
//
// ```
// **Input:** s = "12321"
// **Output:** 9
// **Explanation:** The substrings that meet the requirements are "1", "2", "3", "12", "23", "32", "21", "123", "321".
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 1000`
// - `s` consists of digits.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <string>
#include <unordered_set>

using namespace std;

// Rolling Hash + Hash Set
//
// Loop through all substring and check if it fits the condition.
// Use rolling hash to deduplicate the substrings.
class Solution {
  constexpr static int64_t M1 = 1e9 + 7;
  constexpr static int64_t M2 = 1e9 + 9;

  constexpr static int64_t B1 = 131;
  constexpr static int64_t B2 = 13331;

 public:
  int equalDigitFrequency(string s) {
    int n = s.size();

    // Helper
    auto check = [](array<int, 10> &counts) -> bool {
      int commonCount = 0;  // common count
      for (auto c : counts) {
        if (c > 0 && commonCount > 0 && c != commonCount) return false;
        commonCount = max(commonCount, c);
      }
      return true;
    };

    // We concat two hashs since the value range of each hash is only 32-bit
    auto ansSet = unordered_set<int64_t>();

    // Loop all substrings
    array<int, 10> counts;
    for (int i = 0; i < n; ++i) {
      fill(counts.begin(), counts.end(), 0);  // reset

      // substring [i, j]
      int64_t hash1 = 0, hash2 = 0;
      for (int j = i; j < n; ++j) {
        counts[s[j] - '0']++;
        hash1 = (hash1 * B1 + s[j]) % M1;
        hash2 = (hash2 * B2 + s[j]) % M2;

        if (check(counts)) {
          ansSet.insert(hash1 << 32 | hash2);
        }
      }
    }

    return ansSet.size();
  }
};

// Rolling Hash + Hash Set
//
// Loop through all substring and check if it fits the condition.
// Use rolling hash to deduplicate the substrings.
//
// To check if all count are the same, we maintain the following variables:
// counts[d]: the count of digit d.
// maxCount: the maximum count.
// uniqueDigit: the unique digits count (i.e. nonzero of counts[]).
//
// If maxCount * uniqueDigit == substring length, then all counts must be the same.
class Solution2 {
  constexpr static int64_t M1 = 1e9 + 7;
  constexpr static int64_t M2 = 1e9 + 9;

  constexpr static int64_t B1 = 131;
  constexpr static int64_t B2 = 13331;

 public:
  int equalDigitFrequency(string s) {
    int n = s.size();

    // We concat two hashs since the value range of each hash is only 32-bit
    auto ansSet = unordered_set<int64_t>();

    // Loop all substrings
    array<int, 10> counts;
    for (int i = 0; i < n; ++i) {
      fill(counts.begin(), counts.end(), 0);  // reset
      int maxCount = 0, uniqueDigit = 0;

      // substring [i, j]
      int64_t hash1 = 0, hash2 = 0;
      for (int j = i; j < n; ++j) {
        hash1 = (hash1 * B1 + s[j]) % M1;
        hash2 = (hash2 * B2 + s[j]) % M2;

        // Update counts
        counts[s[j] - '0']++;
        maxCount = max(maxCount, counts[s[j] - '0']);
        if (counts[s[j] - '0'] == 1) ++uniqueDigit;

        // Check if all digit are the same count
        if (maxCount * uniqueDigit == (j - i + 1)) {
          ansSet.insert(hash1 << 32 | hash2);
        }
      }
    }

    return ansSet.size();
  }
};
