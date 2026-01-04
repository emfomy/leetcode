// Source: https://leetcode.com/problems/four-divisors
// Title: Four Divisors
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, return the sum of divisors of the integers in that array that have exactly four divisors. If there is no such integer in the array, return `0`.
//
// **Example 1:**
//
// ```
// Input: nums = [21,4,7]
// Output: 32
// Explanation:
// 21 has 4 divisors: 1, 3, 7, 21
// 4 has 3 divisors: 1, 2, 4
// 7 has 2 divisors: 1, 7
// The answer is the sum of divisors of 21 only.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [21,21]
// Output: 64
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3,4,5]
// Output: 0
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^4`
// - `1 <= nums[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <iterator>
#include <vector>

using namespace std;

class Solution {
 public:
  int sumFourDivisors(vector<int>& nums) {
    auto ans = 0;
    for (auto num : nums) {
      auto count = 2;
      auto sum = 1 + num;

      for (auto a = 2; a * a <= num; ++a) {
        if (num % a == 0) {
          auto b = num / a;
          ++count;
          sum += a;
          if (b != a) {
            ++count;
            sum += b;
          }
        }
        if (count > 4) break;
      }

      if (count == 4) ans += sum;
    }

    return ans;
  }
};

// Math
//
// The only solutions are x = p^3 or x = pq, where p, q are primes.
//
// Now for any number x, find a prime divisor in [2, sqrt(n)].
// Say x = py.
// If y = p^2 (i.e. x = p^3) or y is a prime other than p (i.e. x = pq).

// All primes below sqrt(1e5)
constexpr static int primes[] = {
    2,   3,   5,   7,   11,  13,  17,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,
    79,  83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191,
    193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
};

class Solution2 {
  int getPrimeDivisor(int x) {
    int sqrtx = sqrt(x) + 0.5;  // add 0.5 to avoid floating point precision issue
    for (auto p : primes) {
      if (p > sqrtx) break;
      if (x % p == 0) return p;
    }
    return -1;  // x is prime
  }

  int sum4Div(int x) {
    if (x == 1) return 0;

    // Fine p
    auto p = getPrimeDivisor(x);
    if (p == -1) return 0;  // x is prime

    // Check q
    auto q = x / p;
    if (q == 1 || q == p) return 0;                                    // x = p or p^2
    if (q == p * p || getPrimeDivisor(q) == -1) return 1 + p + q + x;  // x = p^3 or x = p*q

    return 0;
  }

 public:
  int sumFourDivisors(vector<int>& nums) {
    auto ans = 0;
    for (auto num : nums) ans += sum4Div(num);
    return ans;
  }
};
