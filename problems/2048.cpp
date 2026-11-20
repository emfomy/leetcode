// Source: https://leetcode.com/problems/next-greater-numerically-balanced-number
// Title: Next Greater Numerically Balanced Number
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An integer `x` is **numerically balanced** if for every digit `d` in the number `x`, there are **exactly** `d` occurrences of that digit in `x`.
//
// Given an integer `n`, return the **smallest numerically balanced** number **strictly greater** than `n`.
//
// **Example 1:**
//
// ```
// Input: n = 1
// Output: 22
// Explanation:
// 22 is numerically balanced since:
// - The digit 2 occurs 2 times.
// It is also the smallest numerically balanced number strictly greater than 1.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1000
// Output: 1333
// Explanation:
// 1333 is numerically balanced since:
// - The digit 1 occurs 1 time.
// - The digit 3 occurs 3 times.
// It is also the smallest numerically balanced number strictly greater than 1000.
// Note that 1022 cannot be the answer because 0 appeared more than 0 times.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3000
// Output: 3133
// Explanation:
// 3133 is numerically balanced since:
// - The digit 1 occurs 1 time.
// - The digit 3 occurs 3 times.
// It is also the smallest numerically balanced number strictly greater than 3000.
// ```
//
// **Constraints:**
//
// - `0 <= n <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>

using namespace std;

// Brute-Force
//
// Check each number until finding next beautiful number.
class Solution {
 public:
  int nextBeautifulNumber(int n) {
    ++n;
    while (!isBeautiful(n)) ++n;
    return n;
  }

 private:
  bool isBeautiful(int n) {
    auto count = array<int, 10>();
    while (n > 0) {
      ++count[n % 10];
      n /= 10;
    }
    for (auto i = 0; i <= 9; ++i) {
      if (count[i] > 0 && count[i] != i) return false;
    }
    return true;
  }
};

// Generate + Binary Search
//
// Pre-generate all possible beautiful numbers
class Solution2 {
 public:
  int nextBeautifulNumber(int n) {
    static vector<int> nums = generate();
    return *upper_bound(nums.cbegin(), nums.cend(), n);
  }

 private:
  vector<int> generate() {
    auto nums = vector<int>();
    for (uint mask = 1; mask < (1 << 6); ++mask) {  // bit masks of each digit
      bitset<6> bits(mask);

      // Check length
      auto size = 0;
      for (auto d = 1; d <= 6; ++d) {  // check bit
        if (bits.test(d - 1)) size += d;
      }
      if (size == 0 || size > 7) continue;

      // Prepare digits
      auto digits = vector<int>();
      for (auto d = 1; d <= 6; ++d) {  // check bit
        if (bits.test(d - 1)) {
          for (auto i = 0; i < d; ++i) digits.push_back(d);  // insert d copies of d
        }
      }

      // Try all permutation
      do {
        auto num = 0;
        for (auto d : digits) {
          num *= 10;
          num += d;
        }
        nums.push_back(num);
      } while (next_permutation(digits.begin(), digits.end()));
    }

    // Sort numbers
    sort(nums.begin(), nums.end());
    return nums;
  }
};

// Generate + Binary Search
//
// Pre-generate all possible beautiful numbers
class Solution3 {
 public:
  int nextBeautifulNumber(int n) {
    static vector<int> nums = generate();
    return *upper_bound(nums.cbegin(), nums.cend(), n);
  }

 private:
  vector<int> generate() {
    auto nums = vector<int>();

    // All possible digit combinations
    auto digitss = vector<vector<int>>({
        {1},
        {2, 2},
        {1, 2, 2},
        {3, 3, 3},
        {1, 3, 3, 3},
        {4, 4, 4, 4},
        {1, 4, 4, 4, 4},
        {2, 2, 3, 3, 3},
        {5, 5, 5, 5, 5},
        {1, 2, 2, 3, 3, 3},
        {1, 5, 5, 5, 5, 5},
        {2, 2, 4, 4, 4, 4},
        {6, 6, 6, 6, 6, 6},
    });

    // Try all permutation
    for (auto digits : digitss) {
      do {
        auto num = 0;
        for (auto d : digits) {
          num *= 10;
          num += d;
        }
        nums.push_back(num);
      } while (next_permutation(digits.begin(), digits.end()));
    }

    // Sort numbers
    sort(nums.begin(), nums.end());
    nums.push_back(1224444);
    return nums;
  }
};

// Binary Search
class Solution4 {
 public:
  int nextBeautifulNumber(int n) {
    static vector<int> nums = {
        1,      22,     122,    212,    221,    333,    1333,   3133,   3313,   3331,   4444,   14444,  22333,  23233,
        23323,  23332,  32233,  32323,  32332,  33223,  33232,  33322,  41444,  44144,  44414,  44441,  55555,  122333,
        123233, 123323, 123332, 132233, 132323, 132332, 133223, 133232, 133322, 155555, 212333, 213233, 213323, 213332,
        221333, 223133, 223313, 223331, 224444, 231233, 231323, 231332, 232133, 232313, 232331, 233123, 233132, 233213,
        233231, 233312, 233321, 242444, 244244, 244424, 244442, 312233, 312323, 312332, 313223, 313232, 313322, 321233,
        321323, 321332, 322133, 322313, 322331, 323123, 323132, 323213, 323231, 323312, 323321, 331223, 331232, 331322,
        332123, 332132, 332213, 332231, 332312, 332321, 333122, 333212, 333221, 422444, 424244, 424424, 424442, 442244,
        442424, 442442, 444224, 444242, 444422, 515555, 551555, 555155, 555515, 555551, 666666, 1224444};
    return *upper_bound(nums.cbegin(), nums.cend(), n);
  }
};
