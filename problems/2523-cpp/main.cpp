// Source: https://leetcode.com/problems/closest-prime-numbers-in-range
// Title: Closest Prime Numbers in Range
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two positive integers `left` and `right`, find the two integers `num1` and `num2` such that:
//
// - `left <= num1 < num2 <= right `.
// - Both `num1` and `num2` are <button>prime numbers</button>.
// - `num2 - num1` is the **minimum** amongst all other pairs satisfying the above conditions.
//
// Return the positive integer array `ans = [num1, num2]`. If there are multiple pairs satisfying these conditions, return the one with the **smallest** `num1` value. If no such numbers exist, return `[-1, -1]`.
//
// **Example 1:**
//
// ```
// Input: left = 10, right = 19
// Output: [11,13]
// Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
// The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
// Since 11 is smaller than 17, we return the first pair.
// ```
//
// **Example 2:**
//
// ```
// Input: left = 4, right = 6
// Output: [-1,-1]
// Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.
// ```
//
// **Constraints:**
//
// - `1 <= left <= right <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <vector>

using namespace std;

// Find all primes below right.
class Solution {
  using Bool = unsigned char;

 public:
  vector<int> closestPrimes(int left, int right) {
    // Compute primes
    auto primes = vector<Bool>(right + 1, true);
    primes[0] = false;
    primes[1] = false;
    for (int i = 2; i * i <= right; ++i) {
      if (!primes[i]) continue;
      for (int j = i * i; j <= right; j += i) {
        primes[j] = false;
      }
    }

    // Find nearest primes
    int minDist = INT_MAX;
    int minPrime1 = -1;
    int minPrime2 = -1;

    int prevPrime = -1;
    for (int prime = left; prime <= right; ++prime) {
      if (!primes[prime]) continue;
      int dist = prime - prevPrime;
      if (prevPrime != -1 && dist < minDist) {
        minPrime1 = prevPrime;
        minPrime2 = prime;
        minDist = dist;
      }
      prevPrime = prime;
    }

    return {minPrime1, minPrime2};
  }
};
