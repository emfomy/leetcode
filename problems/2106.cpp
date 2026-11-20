// Source: https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps
// Title: Maximum Fruits Harvested After at Most K Steps
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fruits are available at some positions on an infinite x-axis. You are given a 2D integer array `fruits` where `fruits[i] = [position_i, amount_i]` depicts `amount_i` fruits at the position `position_i`. `fruits` is already **sorted** by `position_i` in **ascending order**, and each `position_i` is **unique**.
//
// You are also given an integer `startPos` and an integer `k`. Initially, you are at the position `startPos`. From any position, you can either walk to the **left or right**. It takes **one step** to move **one unit** on the x-axis, and you can walk **at most** `k` steps in total. For every position you reach, you harvest all the fruits at that position, and the fruits will disappear from that position.
//
// Return the **maximum total number** of fruits you can harvest.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/11/21/1.png
//
// ```
// Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
// Output: 9
// Explanation:
// The optimal way is to:
// - Move right to position 6 and harvest 3 fruits
// - Move right to position 8 and harvest 6 fruits
// You moved 3 steps and harvested 3 + 6 = 9 fruits in total.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/11/21/2.png
//
// ```
// Input: fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
// Output: 14
// Explanation:
// You can move at most k = 4 steps, so you cannot reach position 0 nor 10.
// The optimal way is to:
// - Harvest the 7 fruits at the starting position 5
// - Move left to position 4 and harvest 1 fruit
// - Move right to position 6 and harvest 2 fruits
// - Move right to position 7 and harvest 4 fruits
// You moved 1 + 3 = 4 steps and harvested 7 + 1 + 2 + 4 = 14 fruits in total.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/11/21/3.png
//
// ```
// Input: fruits = [[0,3],[6,4],[8,5]], startPos = 3, k = 2
// Output: 0
// Explanation:
// You can move at most k = 2 steps and cannot reach any position with fruits.
// ```
//
// **Constraints:**
//
// - `1 <= fruits.length <= 10^5`
// - `fruits[i].length == 2`
// - `0 <= startPos, position_i <= 2 * 10^5`
// - `position_i-1 < position_i` for any `i > 0`(**0-indexed**)
// - `1 <= amount_i <= 10^4`
// - `0 <= k <= 2 * 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// TLE
//
// If you go right first, you may go `r` steps right and then `r+l` steps left. 2r+l = k.
// If you go left first, you may go `l` steps left and then `r+l` steps right. r+2l = k.
//
// We can use prefix sum to compute all fruits at left.
// And loop thought all possible way to go as described above.
class Solution {
 public:
  int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
    auto n = fruits.size();
    auto maxPos = fruits[n - 1][0];
    vector<int> prefix(maxPos + 2);
    {
      auto i = 0;
      auto& fruit = fruits[i];
      for (auto p = 0; p <= maxPos; p++) {
        prefix[p + 1] = prefix[p];
        if (p == fruit[0]) {
          prefix[p + 1] += fruit[1];
          if (i < n) {
            i++;
            fruit = fruits[i];
          }
        }
      }
    }

    auto ans = 0;
    auto score = [&](int left, int right) -> int {  // [left, right]
      return prefix[min(right + 1, maxPos + 1)] - prefix[max(0, left)];
    };

    // Go right only
    ans = max(ans, score(startPos, startPos + k));

    // Go left only
    ans = max(ans, score(startPos - k, startPos));

    // Go right then left
    for (auto r = 1; r <= k / 2; r++) {
      auto l = k - 2 * r;
      ans = max(ans, score(startPos - l, startPos + r));
    }

    // Go left then right
    for (auto l = 1; l <= k / 2; l++) {
      auto r = k - 2 * l;
      ans = max(ans, score(startPos - l, startPos + r));
    }

    return ans;
  }
};

// Prefix Sum + Binary Search (to find index)
class Solution2 {
 public:
  int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
    int n = fruits.size();

    vector<int> poss(n);         // pos of fruit(i-1)
    vector<int> prefixs(n + 1);  // sum in [0, pos(i))
    {
      for (auto i = 0; i < n; i++) {
        prefixs[i + 1] = prefixs[i] + fruits[i][1];
        poss[i] = fruits[i][0];
      }
    }

    // Find answer
    auto ans = 0;

    // Go right then left (include left only)
    for (auto r = 0; r <= k / 2; r++) {
      auto l = k - 2 * r;

      auto leftPos = startPos - l;
      auto rightPos = startPos + r;

      auto left = lower_bound(poss.cbegin(), poss.cend(), leftPos) - poss.cbegin();
      auto right = upper_bound(poss.cbegin(), poss.cend(), rightPos) - poss.cbegin();

      ans = max(ans, prefixs[right] - prefixs[left]);
    }

    // Go left then right (include right only)
    for (auto l = 0; l <= k / 2; l++) {
      auto r = k - 2 * l;

      auto leftPos = startPos - l;
      auto rightPos = startPos + r;

      auto left = lower_bound(poss.cbegin(), poss.cend(), leftPos) - poss.cbegin();
      auto right = upper_bound(poss.cbegin(), poss.cend(), rightPos) - poss.cbegin();

      ans = max(ans, prefixs[right] - prefixs[left]);
    }

    return ans;
  }
};

// Prefix Sum + Sliding window
class Solution3 {
 public:
  int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
    int n = fruits.size();

    auto ans = 0;
    auto sum = 0;

    // Check step
    auto step = [&](int left, int right) -> int {
      if (fruits[right][0] <= startPos) {  // left only
        return startPos - fruits[left][0];
      }

      if (fruits[left][0] >= startPos) {  // right only
        return fruits[right][0] - startPos;
      }

      auto r = fruits[right][0] - startPos;
      auto l = startPos - fruits[left][0];
      return r + l + min(r, l);
    };

    // Sliding window
    auto left = 0;
    for (auto right = 0; right < n; right++) {
      sum += fruits[right][1];

      // Move left boundary
      while (left <= right && step(left, right) > k) {
        sum -= fruits[left][1];
        left++;
      }

      ans = max(ans, sum);
    }

    return ans;
  }
};
