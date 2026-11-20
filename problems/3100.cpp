// Source: https://leetcode.com/problems/water-bottles-ii
// Title: Water Bottles II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integers `numBottles` and `numExchange`.
//
// `numBottles` represents the number of full water bottles that you initially have. In one operation, you can perform one of the following operations:
//
// - Drink any number of full water bottles turning them into empty bottles.
// - Exchange `numExchange` empty bottles with one full water bottle. Then, increase `numExchange` by one.
//
// Note that you cannot exchange multiple batches of empty bottles for the same value of `numExchange`. For example, if `numBottles == 3` and `numExchange == 1`, you cannot exchange `3` empty water bottles for `3` full bottles.
//
// Return the **maximum** number of water bottles you can drink.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2024/01/28/exampleone1.png
//
// ```
// Input: numBottles = 13, numExchange = 6
// Output: 15
// Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and the number of bottles drunk.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2024/01/28/example231.png
//
// ```
// Input: numBottles = 10, numExchange = 3
// Output: 13
// Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and the number of bottles drunk.
// ```
//
// **Constraints:**
//
// - `1 <= numBottles <= 100 `
// - `1 <= numExchange <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
using namespace std;

// Simulation
class Solution {
 public:
  int maxBottlesDrunk(int numBottles, int numExchange) {
    auto ans = numBottles;
    while (numBottles >= numExchange) {
      ++ans;
      numBottles -= numExchange;
      ++numBottles;
      ++numExchange;
    }
    return ans;
  }
};

// Simulation (For Loop)
class Solution2 {
 public:
  int maxBottlesDrunk(int numBottles, int numExchange) {
    auto ans = numBottles;
    for (auto numEmpty = numBottles; numEmpty >= numExchange; ++numExchange) {
      ++ans;
      numEmpty -= numExchange - 1;
    }
    return ans;
  }
};

// Math
//
// Let B = `numBottles`, E = `numExchange`.
// Say we changed t times, given X bottles, drunk total T bottles.
//
// First, we have X < T = B + t
// Note that here we use inquality since the last bottle is not exchangeable.
//
// Next, we have X = sum_[i=0~(t-1)] (E+i) = Et + t(t-1) / 2
// Combining two equations:
// B + t >= Et + t(t-1) / 2
// t^2 + (2E-3)t - 2B <= 0
// t < floor(-b + sqrt(b^2 + c)), where b = E-1.5 and c = 2B
class Solution3 {
 public:
  int maxBottlesDrunk(int numBottles, int numExchange) {  //
    double b = numExchange - 1.5, c = 2 * numBottles;
    double t = -b + sqrt(b * b + c);
    return numBottles + int(ceil(t - 1));
  }
};
