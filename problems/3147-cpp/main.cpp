// Source: https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon
// Title: Taking Maximum Energy From the Mystic Dungeon
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In a mystic dungeon, `n` magicians are standing in a line. Each magician has an attribute that gives you energy. Some magicians can give you negative energy, which means taking energy from you.
//
// You have been cursed in such a way that after absorbing energy from magician `i`, you will be instantly transported to magician `(i + k)`. This process will be repeated until you reach the magician where `(i + k)` does not exist.
//
// In other words, you will choose a starting point and then teleport with `k` jumps until you reach the end of the magicians' sequence, **absorbing all the energy** during the journey.
//
// You are given an array `energy` and an integer `k`. Return the **maximum** possible energy you can gain.
//
// **Note** that when you are reach a magician, you must take energy from them, whether it is negative or positive energy.
//
// **Example 1:**
//
// ```
// Input:  energy = [5,2,-10,-5,1], k = 3
// Output: 3
// Explanation: We can gain a total energy of 3 by starting from magician 1 absorbing 2 + 1 = 3.
// ```
//
// **Example 2:**
//
// ```
// Input: energy = [-2,-3,-1], k = 2
// Output: -1
// Explanation: We can gain a total energy of -1 by starting from magician 2.
// ```
//
// **Constraints:**
//
// - `1 <= energy.length <= 10^5`
// - `-1000 <= energy[i] <= 1000`
// - `1 <= k <= energy.length - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// DP (left to right)
class Solution {
 public:
  int maximumEnergy(vector<int>& energy, int k) {
    int n = energy.size();

    auto dp = vector<int>(n);
    for (auto i = 0; i < n; ++i) {
      dp[i] = 0;
      if (i >= k) {
        dp[i] = max(dp[i], dp[i - k]);
      }
      dp[i] += energy[i];
    }

    int ans = -1e9;
    for (auto i = max(n - k, 0); i < n; ++i) {
      ans = max(ans, dp[i]);
    }

    return ans;
  }
};

// DP (right to left)
class Solution2 {
 public:
  int maximumEnergy(vector<int>& energy, int k) {
    int n = energy.size();

    auto dp = vector<int>(n + k);
    for (auto i = n - 1; i >= 0; --i) {
      dp[i] = dp[i + k] + energy[i];
    }

    return *max_element(dp.cbegin(), dp.cend());
  }
};

// DP (inplace)
class Solution3 {
 public:
  int maximumEnergy(vector<int>& energy, int k) {
    int n = energy.size();

    for (auto i = n - k - 1; i >= 0; --i) {
      energy[i] += energy[i + k];
    }

    return *max_element(energy.cbegin(), energy.cend());
  }
};
