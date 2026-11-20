// Source: https://leetcode.com/problems/repeated-substring-pattern
// Title: Repeated Substring Pattern
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s`, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.
//
// **Example 1:**
//
// ```
// Input: s = "abab"
// Output: true
// Explanation: It is the substring "ab" twice.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "aba"
// Output: false
// ```
//
// **Example 3:**
//
// ```
// Input: s = "abcabcabcabc"
// Output: true
// Explanation: It is the substring "abc" four times or the substring "abcabc" twice.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^4`
// - `s` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <string_view>
#include <vector>

using namespace std;

// Brute-Force, O(N sqrt(N))
//
// Let n = len(s)
// For each prefix substring (with length k),
// * first check if l divides n (if not, skip)
// * check if this substring forms s
class Solution {
 public:
  bool repeatedSubstringPattern(const string_view s) {
    const int n = s.size();

    // Edge case
    if (n == 0) return true;

    // k is the size of prefix substring
    for (int k = 1; k < n; ++k) {
      if (n % k != 0) continue;

      // Check s[i, i+k) == s[0, k)
      bool valid = true;
      for (int i = k; i < n; i += k) {
        if (s.substr(0, k) != s.substr(i, k)) {
          valid = false;
          break;
        }
      }
      if (valid) return true;
    }

    return false;
  }
};

// Brute-Force, O(N sqrt(N))
//
// To check is substring forms s, we can check if s[0: n-k) == s[k: n) instead.
class Solution2 {
 public:
  bool repeatedSubstringPattern(const string_view s) {
    const int n = s.size();

    // Edge case
    if (n == 0) return true;

    // k is the size of prefix substring
    for (int k = 1; k < n; ++k) {
      if (n % k != 0) continue;

      // Check s[0, n-k) == s[k, n)
      if (s.substr(0, n - k) == s.substr(k, n - k)) return true;
    }

    return false;
  }
};

// Rabin-Karp, O(N)
//
// To check is substring forms s, we can check if s[0: n-k) == s[k: n) instead.
// We can precompute prefix hash, and check above identity in O(1).
//
// Here we use little endian hash:
// hash = s[0] + B s[1] + B^2 s[2] + ...
class Solution3 {
  constexpr static int64_t M1 = 1e9 + 7;  // modulo
  constexpr static int64_t M2 = 1e9 + 9;  // modulo

  constexpr static int64_t B1 = 131;    // base
  constexpr static int64_t B2 = 13331;  // base

  inline int64_t mod(int64_t x, int64_t m) {  //
    return ((x % m) + m) % m;
  }

 public:
  bool repeatedSubstringPattern(const string &s) {
    const int n = s.size();

    // Edge case
    if (n == 0) return true;

    // Prefix Hashs
    int64_t hash1 = 0, hash2 = 0;
    int64_t B1i = 1, B2i = 1;                 // B^i
    auto preHash1s = vector<int64_t>(n + 1);  // hash1 of [0, i)
    auto preHash2s = vector<int64_t>(n + 1);  // hash2 of [0, i)
    for (int i = 0; i < n; ++i) {
      preHash1s[i + 1] = mod(preHash1s[i] + s[i] * B1i, M1);
      preHash2s[i + 1] = mod(preHash2s[i] + s[i] * B2i, M2);
      B1i = mod(B1i * B1, M1);
      B2i = mod(B2i * B2, M2);
    }

    // k is the size of prefix substring
    int64_t B1k = 1, B2k = 1;  // B^k
    for (int k = 1; k < n; ++k) {
      B1k = mod(B1k * B1, M1);
      B2k = mod(B2k * B2, M2);
      if (n % k != 0) continue;

      // Check s[0, n-k) == s[k, n)
      // hash[0, n-k) = prefix[n-k].
      // hash[k, n) = (prefix[n] - prefix[k]) / base^k
      int64_t left1 = mod(preHash1s[n - k] * B1k, M1);
      int64_t left2 = mod(preHash2s[n - k] * B2k, M2);
      int64_t right1 = mod(preHash1s[n] - preHash1s[k], M1);
      int64_t right2 = mod(preHash2s[n] - preHash2s[k], M2);
      if (left1 == right1 && left2 == right2) return true;
    }

    return false;
  }
};

// Rabin-Karp, O(N)
//
// To check is substring forms s, we can check if s[0: n-k) == s[k: n) instead.
// We can use rolling hash to check above identity in O(1).
//
// Here we use little endian hash:
// hash = s[0] + B s[1] + B^2 s[2] + ...
class Solution4 {
  constexpr static int64_t M1 = 1e9 + 7;  // modulo
  constexpr static int64_t M2 = 1e9 + 9;  // modulo

  constexpr static int64_t B1 = 131;    // base
  constexpr static int64_t B2 = 13331;  // base

  inline int64_t mod(int64_t x, int64_t m) {  //
    return ((x % m) + m) % m;
  }

 public:
  bool repeatedSubstringPattern(const string &s) {
    const int n = s.size();

    // Edge case
    if (n == 0) return true;

    // Prefix Hashs, t = n-k-1
    int64_t B1t = 1, B2t = 1;        // B^t
    int64_t left1 = 0, left2 = 0;    // hash of [0, n-k)
    int64_t right1 = 0, right2 = 0;  // hash of [k, n)
    for (int k = n - 1; k >= 1; --k) {
      left1 = mod(left1 + s[n - k - 1] * B1t, M1);
      left2 = mod(left2 + s[n - k - 1] * B2t, M2);

      right1 = mod(right1 * B1 + s[k], M1);
      right2 = mod(right2 * B2 + s[k], M2);

      B1t = mod(B1t * B1, M1);
      B2t = mod(B2t * B2, M2);

      if (n % k == 0 && left1 == right1 && left2 == right2) return true;
    }

    return false;
  }
};

// Rotation String, O(N)
//
// Check if (s+s)[1, 2n-1) contains s.
class Solution5 {
 public:
  bool repeatedSubstringPattern(const string &s) {
    const int n = s.size();
    string ss = (s + s);
    string_view sv = ss;
    return sv.substr(1, 2 * n - 2).find(s) != string::npos;
  }
};
