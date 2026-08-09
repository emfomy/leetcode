// Source: https://leetcode.com/problems/smallest-divisible-digit-product-ii
// Title: Smallest Divisible Digit Product II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `num` which represents a **positive** integer, and an integer `t`.
//
// A number is called **zero-free** if none of its digits are 0.
//
// Return a string representing the **smallest** **zero-free** number greater than or equal to `num` such that the **product of its digits** is divisible by `t`. If no such number exists, return `"-1"`.
//
// **Example 1:**
//
// Input: num = "1234", t = 256
//
// Output: "1488"
//
// Explanation:
//
// The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
//
// **Example 2:**
//
// Input: num = "12355", t = 50
//
// Output: "12355"
//
// Explanation:
//
// 12355 is already zero-free and has the product of its digits divisible by 50, with the product of its digits equal to 150.
//
// **Example 3:**
//
// Input: num = "11111", t = 26
//
// Output: "-1"
//
// Explanation:
//
// No number greater than 11111 has the product of its digits divisible by 26.
//
// **Constraints:**
//
// - `2 <= num.length <= 2 * 10^5`
// - `num` consists only of digits in the range `['0', '9']`.
// - `num` does not contain leading zeros.
// - `1 <= t <= 10^14`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

// Math + DPS + DP
//
// Prime factorize t.
// If the factorization contains numbers greater than 9, then it is impossible.
class Solution {
 public:
  string smallestNumber(string num, long long t) {
    const int n = num.length();

    // Factorize
    {
      long long tt = t;
      for (int d = 2; d <= 9; d++) {
        while (tt % d == 0) tt /= d;
      }
      if (tt > 1) return "-1";
    }

    // Greedy
    auto rem = vector<long long>(n + 1);
    rem[0] = t;
    int pos = n - 1;
    for (int i = 0; i < n; i++) {
      if (num[i] == '0') {
        pos = i;
        break;
      }
      rem[i + 1] = rem[i] / gcd(rem[i], num[i] - '0');
    }
    if (rem[n] == 1) {
      return num;
    }

    for (int i = pos; i >= 0; i--) {
      while (++num[i] <= '9') {
        long long tNow = rem[i] / gcd(rem[i], num[i] - '0');
        int k = 9;
        for (int j = n - 1; j > i; j--) {
          while (tNow % k) {
            k--;
          }
          tNow /= k;
          num[j] = '0' + k;
        }
        if (tNow == 1) {
          return num;
        }
      }
    }

    string ans;
    for (int i = 9; i > 1; i--) {
      while (t % i == 0) {
        ans += '0' + i;
        t /= i;
      }
    }
    ans += string(max(n + 1 - (int)ans.length(), 0), '1');

    reverse(ans.begin(), ans.end());
    return ans;
  }
};
