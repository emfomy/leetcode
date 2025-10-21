// Source: https://leetcode.com/problems/remove-k-digits
// Title: Remove K Digits
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given string num representing a non-negative integer `num`, and an integer `k`, return the smallest possible integer after removing `k` digits from `num`.
//
// **Example 1:**
//
// ```
// Input: num = "1432219", k = 3
// Output: "1219"
// Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
// ```
//
// **Example 2:**
//
// ```
// Input: num = "10200", k = 1
// Output: "200"
// Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
// ```
//
// **Example 3:**
//
// ```
// Input: num = "10", k = 2
// Output: "0"
// Explanation: Remove all the digits from the number and it is left with nothing which is 0.
// ```
//
// **Constraints:**
//
// - `1 <= k <= num.length <= 10^5`
// - `num` consists of only digits.
// - `num` does not have any leading zeros except for the zero itself.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <deque>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// 2D-DP, TLE
//
// DP[i, j] be the minimal number with length i before idx j
// DP[i, i] = num[:i]
// DP[i, j] = min(DP[i, j-1], DP[i-1, j-1]*10+num[j-1])
class Solution {
 public:
  string removeKdigits(string num, int k) {
    int n = num.size();
    auto dp = vector(n - k + 1, vector<string>(n + 1));

    // Helper
    auto minStr = [](string a, string b) -> string {
      if (a.size() != b.size()) return a.size() < b.size() ? a : b;
      return a < b ? a : b;
    };

    // DP
    for (auto i = 1; i <= n - k; ++i) {
      dp[i][i] = dp[i - 1][i - 1] + num[i - 1];
      for (auto j = i + 1; j <= n; ++j) {
        dp[i][j] = minStr(dp[i][j - 1], dp[i - 1][j - 1] + num[j - 1]);
      }
    }

    // Remove leading zeros
    auto ans = dp[n - k][n];
    auto i = 0;  // first nonzero index
    while (i < ans.size() && ans[i] == '0') ++i;
    ans = ans.substr(i);

    return ans.empty() ? "0" : ans;
  }
};

// Greedy
//
// First make the number monotonic increasing by removing some numbers.
// If k is still positive, remove from the last
class Solution2 {
 public:
  string removeKdigits(string num, int k) {
    auto st = deque<char>();

    // Monotonic stack
    for (auto ch : num) {
      while (!st.empty() && st.back() > ch && k > 0) {
        st.pop_back();
        --k;
      }
      st.push_back(ch);
    }

    // Pop from last until k=0
    while (!st.empty() && k > 0) {
      st.pop_back();
      --k;
    }

    // Remove leading zeros
    while (!st.empty() && st.front() == '0') {
      st.pop_front();
    }

    // Zero case
    if (st.empty()) return "0";

    // Answer
    string ans;
    while (!st.empty()) {
      ans.push_back(st.front());
      st.pop_front();
    }

    return ans;
  }
};
