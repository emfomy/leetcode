// Source: https://leetcode.com/problems/special-binary-string
// Title: Special Binary String
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// **Special binary strings** are binary strings with the following two properties:
//
// - The number of `0`'s is equal to the number of `1`'s.
// - Every prefix of the binary string has at least as many `1`'s as `0`'s.
//
// You are given a **special binary** string `s`.
//
// A move consists of choosing two consecutive, non-empty, special substrings of `s`, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.
//
// Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.
//
// **Example 1:**
//
// ```
// Input: s = "11011000"
// Output: "11100100"
// Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
// This is the lexicographically largest string possible after some number of swaps.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "10"
// Output: "10"
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 50`
// - `s[i]` is either `'0'` or `'1'`.
// - `s` is a special binary string.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

// Divide & Conquer
//
// Treat binary strings as paths in the 2D plane,
// where x is the number of prefix 1s, and y is the number of prefix 0s.
// A special string is a path starting from (0, 0) and end with (t, t),
// where all points in the path are below the x-y line.
// A special substring is a subpath with the slope of from start to end is 1,
// and all points in the subpath are below that slope.
//
// Now we assign a number z=x-y to each points in the paths.
// A subpath is special if the z-value of start and end are the same,
// and the points between them have greater z-values.
//
// We first split the string by the points with z=0.
// For each substring `ss`, we first run the same algorithm on `ss[1:-1]`.
// Next we sort all them new substrings and concatenate them.
//
// --------
//
// Time Complexity:
//
// In each recursion, we need O(N) to find the zeros and substrings.
//
// If the string is nested (e.g. 111...000),
// then it takes O(N), O(N-2), ..., O(2) for the subproblems.
// That is O(N^2).
//
// If the string is flat (e.g. 1010...1010),
// then it takes (N/2) * O(2) for subproblems, and O(N log N) to sort the substrings,
// That is O(N log N).
//
// Hence in the worst case, it cost O(N^2).
//
// --------
//
// Space Complexity:
// In each recursion, we need O(N) to store the substrings.
//
// If the string is nested (e.g. 111...000),
// then it takes O(N), O(N-2), ..., O(2) for the subproblems.
// However, the outer space only allocate after inner loop ends.
// Therefore its only O(N).
//
// If the string is flat (e.g. 1010...1010),
// Then it takes only O(2) to to store each subproblem,
//
// Hence in the worst case, it cost O(N^2).
class Solution {
 public:
  string makeLargestSpecial(const string_view s) {
    const int n = s.size();
    if (n == 0) return "";

    // Divide & Conquer
    // We skip the vector reserve here since we don't know the substrings yet.
    // Reserve will cause the space complexity to be O(N^2).
    auto substrs = vector<string>();
    int z = 0, prevIdx = 0;
    for (int idx = 1; idx <= n; ++idx) {
      z += (s[idx - 1] == '1') ? 1 : -1;
      if (z == 0) {
        // remove leading 1 and trailing 0
        auto substr = s.substr(prevIdx + 1, idx - prevIdx - 2);
        substrs.push_back("1" + makeLargestSpecial(substr) + "0");
        prevIdx = idx;
      }
    }

    // Sort substrings
    sort(substrs.begin(), substrs.end(), greater());

    // Concatenation
    string ans = "";
    ans.reserve(n);
    for (auto& substr : substrs) {
      ans += substr;
    }

    return ans;
  }
};
