// Source: https://leetcode.com/problems/unique-3-digit-even-numbers
// Title: Unique 3-Digit Even Numbers
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of digits called `digits`. Your task is to determine the number of **distinct** three-digit even numbers that can be formed using these digits.
//
// **Note**: Each copy of a digit can only be used **once per number**, and there may **not** be leading zeros.
//
// **Example 1:**
//
// ```
// Input: digits = [1,2,3,4]
// Output: 12
// Explanation: The 12 distinct 3-digit even numbers that can be formed are 124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, and 432. Note that 222 cannot be formed because there is only 1 copy of the digit 2.
// ```
//
// **Example 2:**
//
// ```
// Input: digits = [0,2,2]
// Output: 2
// Explanation: The only 3-digit even numbers that can be formed are 202 and 220. Note that the digit 2 can be used twice because it appears twice in the array.
// ```
//
// **Example 3:**
//
// ```
// Input: digits = [6,6,6]
// Output: 1
// Explanation: Only 666 can be formed.
// ```
//
// **Example 4:**
//
// ```
// Input: digits = [1,3,5]
// Output: 0
// Explanation: No even 3-digit numbers can be formed.
// ```
//
// **Constraints:**
//
// - `3 <= digits.length <= 10`
// - `0 <= digits[i] <= 9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <vector>

using namespace std;

// The possible numbers are 100~999.
// Just loop through all of them.
class Solution {
  struct Freqs : array<int, 10> {
    bool operator<=(const Freqs& other) const {
      for (int d = 0; d <= 9; ++d) {
        if (!((*this)[d] <= other[d])) return false;
      }
      return true;
    }
  };

 public:
  int totalNumbers(const vector<int>& digits) {
    // Count freq
    Freqs freqs = {};
    for (int d : digits) {
      ++freqs[d];
    }

    // Loop
    int ans = 0;
    for (int n = 100; n <= 999; n += 2) {
      Freqs f = {};
      ++f[n / 100];
      ++f[(n / 10) % 10];
      ++f[n % 10];

      ans += (f <= freqs);
    }

    return ans;
  }
};

// The possible numbers are 100~999.
// Just loop through all of them.
class Solution2 {
 public:
  int totalNumbers(const vector<int>& digits) {
    // Count freq
    array<int, 10> freqs = {};
    for (int d : digits) {
      ++freqs[d];
    }

    // Loop
    int ans = 0;
    for (int i = 1; i < 10; ++i) {
      if (freqs[i] <= 0) continue;
      --freqs[i];
      for (int j = 0; j < 10; ++j) {
        if (freqs[j] <= 0) continue;
        --freqs[j];
        for (int k = 0; k < 10; k += 2) {
          if (freqs[k] <= 0) continue;
          ++ans;
        }
        ++freqs[j];
      }
      ++freqs[i];
    }

    return ans;
  }
};
