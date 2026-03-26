// Source: https://leetcode.com/problems/longest-palindromic-substring
// Title: Longest Palindromic Substring
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, return the longest **palindromic substring** in `s`.
//
// A string is **palindromic** if it reads the same forward and backward.
// A **substring** is a contiguous non-empty sequence of characters within a string.
//
// **Example 1:**
//
// ```
// Input: s = "babad"
// Output: "bab"
// Explanation: "aba" is also a valid answer.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "cbbd"
// Output: "bb"
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 1000`
// - `s` consist of only digits and English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

// O(N^2)
//
// Try to find palindrome from all possible centers.
class Solution {
 public:
  string longestPalindrome(const string_view s) {
    const int n = s.size();
    if (n == 0) return "";

    // Find palindrome
    auto find = [n, &s](int j, int k) -> string_view {
      // Find first [j, k] not palindrome
      while (j >= 0 && k < n && s[j] == s[k]) --j, ++k;

      // (j, k) is palindrome
      return s.substr(j + 1, k - j - 1);
    };

    // Update maximum palindrome
    string_view maxSubstr = s.substr(0, 0);
    auto update = [&maxSubstr](string_view substr) {
      if (maxSubstr.size() < substr.size()) maxSubstr = substr;
    };

    // Loop
    for (int i = 0; i < n; ++i) {
      update(find(i - 1, i + 1));  // odd length palindromes
      update(find(i, i + 1));      // even length palindromes
    }

    return string(maxSubstr);
  }
};

// Rolling Hash + Binary Search, O(NlogN)
//
// Use rolling hash to check palindrome.
// We first compute the prefix hash for both direction.
// To check palindrome, we simply compare the hash for both direction.
//
// PreHash[0, i) = s[i-1] + s[i-2]B + s[i-3]B^2 + ...
// PreHash[i, j) = s[j-1] + ... + s[i]B^(j-i-1)
//               = PreHash[0, j) - PreHash[0, i) * B^(j-i)
//
// SufHash[i, n) = s[i] + s[i+1]B + s[i+2]B^2 + ...
// SufHash[i, j) = s[i] + ... + s[j-1]B^(j-i-1)
//               = SufHash[i, n) - SufHash[j, n) * B^(j-i)
//
// For each center position, use binary search to find the longest palindrome.
class Solution2 {
  constexpr static int64_t M = 1e9 + 7;  // modulo
  constexpr static int64_t B = 13331;    // base

  int64_t mod(int64_t x) {
    return ((x % M) + M) % M;  //
  }

 public:
  string longestPalindrome(const string_view s) {
    const int n = s.size();
    if (n == 0) return "";

    // Hash
    auto bPows = vector<int64_t>(n + 1, 0);     // B^i
    auto preHashs = vector<int64_t>(n + 1, 0);  // hash of [0, i)
    auto sufHashs = vector<int64_t>(n + 1, 0);  // hash of [i, n)
    bPows[0] = 1;
    for (int i = 0; i < n; ++i) {
      bPows[i + 1] = mod(bPows[i] * B);
    }
    for (int i = 0; i < n; ++i) {
      preHashs[i + 1] = mod(preHashs[i] * B + s[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
      sufHashs[i] = mod(sufHashs[i + 1] * B + s[i]);
    }

    // Find palindrome
    auto find = [&](int j0, int k0) -> string_view {
      // Expand [j0, k0) to find palindrome

      // Check if [j, k) is palindrome
      auto check = [&](int j, int k) -> bool {
        int64_t preHash = mod(preHashs[k] - preHashs[j] * bPows[k - j]);
        int64_t sufHash = mod(sufHashs[j] - sufHashs[k] * bPows[k - j]);
        return preHash == sufHash;
      };

      // Binary search on l = j0-j = k-k0
      // 0 <= l <= min(j0, n - k0)
      // lo-1: true; hi: false
      int lo = 0, hi = min(j0, n - k0) + 1;
      while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(j0 - mid, k0 + mid)) {
          lo = mid + 1;
        } else {
          hi = mid;
        }
      }

      // [j, k) is palindrome
      int j = j0 - lo + 1, k = k0 + lo - 1;
      return s.substr(j, k - j);
    };

    // Update maximum palindrome
    string_view maxSubstr = s.substr(0, 0);
    auto update = [&maxSubstr](string_view substr) {
      if (maxSubstr.size() < substr.size()) maxSubstr = substr;
    };

    // Loop
    for (int i = 0; i < n; ++i) {
      update(find(i, i + 1));  // odd length palindromes
      update(find(i, i + 2));  // even length palindromes
    }

    return string(maxSubstr);
  }
};

// Manacher's Algorithm, O(N)
//
// In the algorithm, r increases monotonically.
// The while loop only expands when i+radius[i] >= r.
// If i+radius[i] < r, the radius is determined exactly by its mirror,
// and the while loop exits immediately.
// Therefore, the while loop runs O(N) times in total, i.e. amortized O(1) per i.
class Solution3 {
 public:
  string longestPalindrome(const string_view s) {
    // Guard
    if (s.empty()) return "";

    // Preprocess
    string s2;
    s2.reserve(2 * s.size() + 3);
    s2.push_back('^');  // start sentinel
    s2.push_back('#');
    for (char ch : s) {
      s2.push_back(ch);
      s2.push_back('#');
    }
    s2.push_back('$');  // end sentinel

    // Prepare
    const int m = s2.size();
    auto radius = vector<int>(m, 0);  // Radius of palindrome centered at i
    int l = 0, r = 0;                 // [l, r] is the rightmost palindrome

    // Loop, skip sentinels
    for (int i = 1; i < m - 1; ++i) {
      // Mirror i around center (l+r)/2
      int mi = l + r - i;

      // Init radius[i] by mirror if within bounds
      // Not exceed r-i to avoid out of bounds
      if (i < r) {
        radius[i] = min(r - i, radius[mi]);
      }

      // Expand palindrome centered at i
      while (s2[i + radius[i] + 1] == s2[i - radius[i] - 1]) ++radius[i];

      // Update [l, r] if the palindrome expands beyond current r
      if (i + radius[i] > r) {
        l = i - radius[i];
        r = i + radius[i];
      }
    }

    // Build answer
    string_view maxSubstr = s.substr(0, 0);
    for (int i = 1; i < m - 1; ++i) {
      string_view substr = s.substr((i - radius[i]) / 2, radius[i]);
      if (maxSubstr.size() < substr.size()) maxSubstr = substr;
    }
    return string(maxSubstr);
  }
};
