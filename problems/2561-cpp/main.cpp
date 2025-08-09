// Source: https://leetcode.com/problems/rearranging-fruits
// Title: Rearranging Fruits
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have two fruit baskets containing `n` fruits each. You are given two **0-indexed** integer arrays `basket1` and `basket2` representing the cost of fruit in each basket. You want to make both baskets **equal**. To do so, you can use the following operation as many times as you want:
//
// - Chose two indices `i` and `j`, and swap the `i<font size="1">th`fruit of `basket1` with the `j<font size="1">th`fruit of `basket2`.
// - The cost of the swap is `min(basket1[i],basket2[j])`.
//
// Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.
//
// Return the minimum cost to make both the baskets equal or `-1` if impossible.
//
// **Example 1:**
//
// ```
// Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
// Output: 1
// Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2]. Rearranging both the arrays makes them equal.
// ```
//
// **Example 2:**
//
// ```
// Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
// Output: -1
// Explanation: It can be shown that it is impossible to make both the baskets equal.
// ```
//
// **Constraints:**
//
// - `basket1.length == basket2.length`
// - `1 <= basket1.length <= 10^5`
// - `1 <= basket1[i],basket2[i]<= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdlib>
#include <unordered_map>
#include <vector>

using namespace std;

// Use hash map & sort
//
// First count the number of each cost.
// Make the list to move.
//
// Note that we can use a cheap fruit to swap two expansive fruits.
// Say we want to swap b & c in [a, b] [c]. Assume a < b & a < c.
// swap(b, c) costs min(b, c).
// swap(a, c) & swap(a, b) costs 2*a.
class Solution {
 public:
  long long minCost(vector<int>& basket1, vector<int>& basket2) {
    // Count number
    unordered_map<int, int> counter;
    unordered_map<int, int> counter1;
    unordered_map<int, int> counter2;
    for (auto cost : basket1) {
      counter[cost]++;
      counter1[cost]++;
    }
    for (auto cost : basket2) {
      counter[cost]++;
      counter2[cost]++;
    }

    // Check odd
    for (auto item : counter) {
      if (item.second % 2 == 1) {
        return -1;
      }
    }

    // Find minimal cost
    int minCost = 1e9;
    for (auto cost : basket1) {
      minCost = min(minCost, cost);
    }
    for (auto cost : basket2) {
      minCost = min(minCost, cost);
    }

    // Make move list
    vector<int> move1;
    vector<int> move2;
    for (auto [cost, count] : counter) {
      auto count1 = counter1[cost];
      auto count2 = counter2[cost];
      auto countHalf = count / 2;

      if (count1 > countHalf) {
        for (auto i = 0; i < count1 - countHalf; i++) {
          move1.push_back(cost);
        }
      } else if (count2 > countHalf) {
        for (auto i = 0; i < count2 - countHalf; i++) {
          move2.push_back(cost);
        }
      }
    }

    // Sort move list
    sort(move1.begin(), move1.end());
    sort(move2.begin(), move2.end());

    // Move fruits
    long long ans = 0;
    auto n = move1.size();
    for (auto i = 0; i < n; i++) {
      auto cost1 = move1[i];
      auto cost2 = move2[n - i - 1];
      ans += min(min(cost1, cost2), 2 * minCost);
    }

    return ans;
  }
};

// Use hash map & sort
//
// First we need only one hash map, defined as counter1 - counter2.
//
// Same as above, but we don't need two move array.
// Note that there is not common item in move1 & move2.
// We can simply merge them into a single array.
class Solution2 {
 public:
  long long minCost(vector<int>& basket1, vector<int>& basket2) {
    // Count number
    unordered_map<int, int> counter;
    for (auto cost : basket1) {
      counter[cost]++;
    }
    for (auto cost : basket2) {
      counter[cost]--;
    }

    // Check odd
    for (auto [cost, count] : counter) {
      if (count % 2 == 1) {
        return -1;
      }
    }

    // Make move list
    vector<int> moves;
    for (auto [cost, count] : counter) {
      for (auto i = 0; i < abs(count) / 2; i++) {
        moves.push_back(cost);
      }
    }

    // Find minimal cost
    int minCost = 1e9;
    for (auto [cost, _] : counter) {
      minCost = min(minCost, cost);
    }

    // Sort move list (first half)
    auto n = moves.size() / 2;
    nth_element(moves.begin(), moves.begin() + n, moves.end());

    // Move fruits
    long long ans = 0;
    for (auto i = 0; i < n; i++) {
      ans += min(moves[i], 2 * minCost);
    }

    return ans;
  }
};
