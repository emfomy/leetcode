// Source: https://leetcode.com/problems/restore-ip-addresses
// Title: Restore IP Addresses
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **valid IP address** consists of exactly four integers separated by single dots. Each integer is between `0` and `255` (**inclusive**) and cannot have leading zeros.
//
// - For example, `"0.1.2.201"` and `"192.168.1.1"` are **valid** IP addresses, but `"0.011.255.245"`, `"192.168.1.312"` and `"192.168@1.1"` are **invalid** IP addresses.
//
// Given a string `s` containing only digits, return all possible valid IP addresses that can be formed by inserting dots into `s`. You are **not** allowed to reorder or remove any digits in `s`. You may return the valid IP addresses in **any** order.
//
// **Example 1:**
//
// ```
// **Input:** s = "25525511135"
// **Output:** ["255.255.11.135","255.255.111.35"]
// ```
//
// **Example 2:**
//
// ```
// **Input:** s = "0000"
// **Output:** ["0.0.0.0"]
// ```
//
// **Example 3:**
//
// ```
// **Input:** s = "101023"
// **Output:** ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 20`
// - `s` consists of digits only.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <string_view>
#include <vector>

using namespace std;

// Backtracing
//
// We use 3 separator to separate the string into 4 numbers.
class Solution {
 public:
  vector<string> restoreIpAddresses(string s) {
    int n = s.size();

    if (n < 4 || n > 12) return {};  // always invalid

    // Helper
    auto checkNum = [&](int start, int end) -> bool {
      int l = end - start;

      // 0~9
      if (l == 1) {
        return true;
      }

      // 10~99
      if (l == 2) {
        return s[start + 0] != '0';
      }

      // 100~255
      if (l == 3) {
        return s[start + 0] == '1' ||                                                // 100~199
               (s[start + 0] == '2' && s[start + 1] < '5') ||                        // 200~249
               (s[start + 0] == '2' && s[start + 1] == '5' && s[start + 2] <= '5');  // 250~255
      }

      return false;
    };

    auto genIP = [&](int i1, int i2, int i3) -> string {
      string_view sv(s);
      string ip = "";
      ip.reserve(n + 3);

      ip += sv.substr(0, i1);
      ip += '.';
      ip += sv.substr(i1, i2 - i1);
      ip += '.';
      ip += sv.substr(i2, i3 - i2);
      ip += '.';
      ip += sv.substr(i3);

      return ip;
    };

    // Backtracking
    auto ans = vector<string>();
    for (auto i1 = 1; i1 < n; ++i1) {
      if (!checkNum(0, i1)) continue;

      for (auto i2 = i1 + 1; i2 < n; ++i2) {
        if (!checkNum(i1, i2)) continue;

        for (auto i3 = i2 + 1; i3 < n; ++i3) {
          if (!checkNum(i2, i3) || !checkNum(i3, n)) continue;

          ans.push_back(std::move(genIP(i1, i2, i3)));
        }
      }
    }

    return ans;
  }
};
