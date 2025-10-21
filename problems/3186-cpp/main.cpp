// Source: https://leetcode.com/problems/maximum-total-damage-with-spell-casting
// Title: Maximum Total Damage With Spell Casting
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A magician has various spells.
//
// You are given an array `power`, where each element represents the damage of a spell. Multiple spells can have the same damage value.
//
// It is a known fact that if a magician decides to cast a spell with a damage of `power[i]`, they **cannot** cast any spell with a damage of `power[i] - 2`, `power[i] - 1`, `power[i] + 1`, or `power[i] + 2`.
//
// Each spell can be cast **only once**.
//
// Return the **maximum** possible total damage that a magician can cast.
//
// **Example 1:**
//
// ```
// Input: power = [1,1,3,4]
// Output: 6
// Explanation:
// The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.
// ```
//
// **Example 2:**
//
// ```
// Input: power = [7,1,6,6]
// Output: 13
// Explanation:
// The maximum possible damage of 13 is produced by casting spells 1, 2, 3 with damage 1, 6, 6.
// ```
//
// **Constraints:**
//
// - `1 <= power.length <= 10^5`
// - `1 <= power[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <vector>

using namespace std;

// Use DP + Array (TLE)
//
// We do DP from right to left.
// Let DP_N[i] be the maximum damage without casting the i-th spell.
// Let DP_Y[i] be the maximum damage with casting the i-th spell.
// DP_Y[i] = DP_N[i+2] + total[i]
// DP_N[i] = max(DP_N[i+1], DP_Y[i+1])
//
// Define DP[i] = max(DP_N[i], DP_Y[i]) (i.e. DP_N[i] = DP[i+1]) be the maximum damage until i.
// DP[i] = max(DP_N[i], DP_Y[i])
//       = max(DP[i+1], DP_N[i+2] + total[i])
//       = max(DP[i+1], DP[i+3] + total[i])
class Solution {
 public:
  int64_t maximumTotalDamage(vector<int>& powers) {
    auto minPower = *min_element(powers.cbegin(), powers.cend());
    auto maxPower = *max_element(powers.cbegin(), powers.cend());
    auto n = maxPower - minPower + 1;

    auto total = vector<int64_t>(n + 3);  // damage -> total damage (i.e. count * damage)
    auto dp = vector<int64_t>(n + 3);     // not cast this spell

    // Count
    for (auto power : powers) {
      total[power - minPower] += power;
    }

    // DP
    for (auto i = n - 1; i >= 0; --i) {
      dp[i] = max(dp[i + 1], dp[i + 3] + total[i]);
    }

    return dp[0];
  }
};

// Use DP + Hash Map + Sort
//
// We do DP from left to right.
// Let DP_N[i] be the maximum damage without casting the i-th spell.
// Let DP_Y[i] be the maximum damage with casting the i-th spell.
// DP_Y[i] = DP_N[i-2] + total[i]
// DP_N[i] = max(DP_N[i-1], DP_Y[i-1])
//
// Define DP[i] = max(DP_N[i], DP_Y[i]) (i.e. DP_N[i] = DP[i-1]) be the maximum damage until i.
// DP[i] = max(DP_N[i], DP_Y[i])
//       = max(DP[i-1], DP_N[i-2] + total[i])
//       = max(DP[i-1], DP[i-3] + total[i])
//
// Rewrite:
// Let dp0 = DP[i+0], dp1 = DP[i+1], ...
// dp3 = max(dp2, dp0 + total3)
//
// If total3 = 0
// dp3 = max(dp2, dp0) = dp2
// dp4 = max(dp3, dp1 + total4)
//
// If total3 = total4 = 0
// dp4 = dp3 = dp2
// dp5 = max(dp4, dp2 + total5) = dp2 + total5
class Solution2 {
 public:
  int64_t maximumTotalDamage(vector<int>& powers) {
    // Count
    auto total = unordered_map<int, int64_t>();  // damage -> total damage (i.e. count * damage)
    for (auto power : powers) {
      total[power] += power;
    }

    // Sort
    auto spells = vector<int>();
    for (auto [power, _] : total) {
      spells.push_back(power);
    }
    sort(spells.begin(), spells.end());

    // DP
    auto prevSpell = -10;
    int64_t dp0 = 0, dp1 = 0, dp2 = 0;
    for (auto spell : spells) {
      if (spell - prevSpell == 1) {
        auto dp3 = max(dp2, dp0 + total[spell]);
        dp0 = dp1;
        dp1 = dp2;
        dp2 = dp3;
      } else if (spell - prevSpell == 2) {
        // dp3 = dp2
        auto dp4 = max(dp2, dp1 + total[spell]);
        dp0 = dp2;
        dp1 = dp2;
        dp2 = dp4;
      } else {
        // dp4 = dp3 = dp2
        auto dp5 = dp2 + total[spell];
        dp0 = dp2;
        dp1 = dp2;
        dp2 = dp5;
      }
      prevSpell = spell;
    }

    return max({dp0, dp1, dp2});
  }
};
