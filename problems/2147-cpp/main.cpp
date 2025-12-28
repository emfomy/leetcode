// Source: https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor
// Title: Number of Ways to Divide a Long Corridor
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Along a long library corridor, there is a line of seats and decorative plants. You are given a **0-indexed** string `corridor` of length `n` consisting of letters `'S'` and `'P'` where each `'S'` represents a seat and each `'P'` represents a plant.
//
// One room divider has **already** been installed to the left of index `0`, and **another** to the right of index `n - 1`. Additional room dividers can be installed. For each position between indices `i - 1` and `i` (`1 <= i <= n - 1`), at most one divider can be installed.
//
// Divide the corridor into non-overlapping sections, where each section has **exactly two seats** with any number of plants. There may be multiple ways to perform the division. Two ways are **different** if there is a position with a room divider installed in the first way but not in the second way.
//
// Return the number of ways to divide the corridor. Since the answer may be very large, return it **modulo** `10^9 + 7`. If there is no way, return `0`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/12/04/1.png
//
// ```
// Input: corridor = "SSPPSPS"
// Output: 3
// Explanation: There are 3 different ways to divide the corridor.
// The black bars in the above image indicate the two room dividers already installed.
// Note that in each of the ways, **each** section has exactly **two** seats.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/12/04/2.png
//
// ```
// Input: corridor = "PPSPSP"
// Output: 1
// Explanation: There is only 1 way to divide the corridor, by not installing any additional dividers.
// Installing any would create some section that does not have exactly two seats.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/12/12/3.png
//
// ```
// Input: corridor = "S"
// Output: 0
// Explanation: There is no way to divide the corridor because there will always be a section that does not have exactly two seats.
// ```
//
// **Constraints:**
//
// - `n == corridor.length`
// - `1 <= n <= 10^5`
// - `corridor[i]` is either `'S'` or `'P'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

// First count the number of seats. If the number is odd, then there is no way.
//
// Next find the distance `d` between seat i and i+1, where i is odd.
// The are exact `d` ways for this divider.
class Solution {
  constexpr static int modulo = 1e9 + 7;

 public:
  int numberOfWays(string corridor) {
    int n = corridor.size();

    // Find plants
    auto plants = vector<int>();
    for (auto i = 0; i < n; ++i) {
      if (corridor[i] == 'S') plants.push_back(i);
    }
    int m = plants.size();
    if (m == 0 || m % 2 != 0) return 0;

    // Find distances
    auto ans = 1LL;
    for (auto i = 2; i < m; i += 2) {
      ans *= (plants[i] - plants[i - 1]);
      ans %= modulo;
    }

    return ans;
  }
};
