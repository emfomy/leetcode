// Source: https://leetcode.com/problems/count-primes
// Title: Count Primes
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, return the number of prime numbers that are strictly less than `n`.

// **Example 1:**

// ```
// Input: n = 10
// Output: 4
// Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
// ```

// **Example 2:**

// ```
// Input: n = 0
// Output: 0
// ```

// **Example 3:**

// ```
// Input: n = 1
// Output: 0
// ```

// **Constraints:**

// - `0 <= n <= 5 * 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  int countPrimes(int n) {
    if (n <= 1) return 0;

    auto primes = vector<bool>(n, true);
    primes[0] = false;
    primes[1] = false;

    for (auto i = 2; i * i < n; ++i) {
      if (!primes[i]) continue;
      for (auto j = i * i; j < n; j += i) {
        primes[j] = false;
      }
    }

    return accumulate(primes.cbegin(), primes.cend(), 0);
  }
};
