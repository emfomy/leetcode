// Source: https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions
// Title: Find the Minimum Amount of Time to Brew Potions
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integer arrays, `skill` and `mana`, of length `n` and `m`, respectively.
//
// In a laboratory, `n` wizards must brew `m` potions in order. Each potion has a mana capacity `mana[j]` and **must** pass through **all** the wizards sequentially to be brewed properly. The time taken by the `i^th` wizard on the `j^th` potion is `time_ij = skill[i] * mana[j]`.
//
// Since the brewing process is delicate, a potion **must** be passed to the next wizard immediately after the current wizard completes their work. This means the timing must be synchronized so that each wizard begins working on a potion **exactly** when it arrives. ​
//
// Return the **minimum** amount of time required for the potions to be brewed properly.
//
// **Example 1:**
//
// ```
// Input: skill = [1,5,2,4], mana = [5,1,4,2]
// Output: 110
// Explanation:
// - Potion Number:     0   1   2   3
// - Start time:        0   52  53  86
// - Wizard 0 done by:  5   53  58  88
// - Wizard 1 done by:  30  58  78  98
// - Wizard 2 done by:  40  60  86  102
// - Wizard 3 done by:  60  64  102 110
// As an example for why wizard 0 cannot start working on the 1^st potion before time `t = 52`, consider the case where the wizards started preparing the 1^st potion at time `t = 50`. At time `t = 58`, wizard 2 is done with the 1^st potion, but wizard 3 will still be working on the 0^th potion till time `t = 60`.
// ```
//
// **Example 2:**
//
// ```
// Input: skill = [1,1,1], mana = [1,1,1]
// Output: 5
// Explanation:
// - Preparation of the 0^th potion begins at time `t = 0`, and is completed by time `t = 3`.
// - Preparation of the 1^st potion begins at time `t = 1`, and is completed by time `t = 4`.
// - Preparation of the 2^nd potion begins at time `t = 2`, and is completed by time `t = 5`.
// ```
//
// **Example 3:**
//
// ```
// Input: skill = [1,2,3,4], mana = [1,2]
// Output: 21
// ```
//
// **Constraints:**
//
// - `n == skill.length`
// - `m == mana.length`
// - `1 <= n, m <= 5000`
// - `1 <= mana[i], skill[i] <= 5000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// Brute-Force
class Solution {
 public:
  int64_t minTime(vector<int>& skill, vector<int>& mana) {
    int n = skill.size(), m = mana.size();

    // Prepare
    auto wizards = vector<int64_t>(n);
    auto cost = vector<int64_t>(n);

    // Brew potions
    for (auto j = 0; j < m; ++j) {
      // Compute cost
      for (auto i = 0; i < n; ++i) {
        cost[i] = skill[i] * mana[j];
      }

      // Pre-brew
      int64_t now = wizards[0];
      int64_t start = now;
      for (auto i = 0; i < n; ++i) {
        if (now < wizards[i]) {
          start += wizards[i] - now;
          now = wizards[i];
        }
        now += cost[i];
      }

      // Brew
      now = start;
      for (auto i = 0; i < n; ++i) {
        now += cost[i];
        wizards[i] = now;
      }
    }

    return wizards.back();
  }
};
