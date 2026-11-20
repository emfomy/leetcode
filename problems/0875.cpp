// Source: https://leetcode.com/problems/split-array-largest-sum
// Title: Koko Eating Bananas
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Koko loves to eat bananas. There are `n` piles of bananas, the `i^th` pile has `piles[i]` bananas. The guards have gone and will come back in `h` hours.
//
// Koko can decide her bananas-per-hour eating speed of `k`. Each hour, she chooses some pile of bananas and eats `k` bananas from that pile. If the pile has less than `k` bananas, she eats all of them instead and will not eat any more bananas during this hour.
//
// Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
//
// Return the minimum integer `k` such that she can eat all the bananas within `h` hours.
//
// **Example 1:**
//
// ```
// Input: piles = [3,6,7,11], h = 8
// Output: 4
// ```
//
// **Example 2:**
//
// ```
// Input: piles = [30,11,23,4,20], h = 5
// Output: 30
// ```
//
// **Example 3:**
//
// ```
// Input: piles = [30,11,23,4,20], h = 6
// Output: 23
// ```
//
// **Constraints:**
//
// - `1 <= piles.length <= 10^4`
// - `piles.length <= h <= 10^9`
// - `1 <= piles[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Binary Search
//
// We first compute how long will Koko finish eating with speed k.
// The total time is sum(ceil(pile/k)) for all piles.
//
// We can apply binary to find the maximum k.
// Note the maximum solution is the largest pile (eat a pile per hour).
// Therefore the search range is [1, max(piles)].
class Solution {
 public:
  int minEatingSpeed(const vector<int>& piles, int h) {
    const int n = piles.size();
    if (n == 0 || h < n) return -1;

    const int maxPile = *max_element(piles.cbegin(), piles.cend());

    // Helper
    auto check = [&piles, h](int k) -> bool {
      int total = 0;
      for (int pile : piles) {
        total += (pile + k - 1) / k;  // ceil
      }
      return total <= h;
    };

    // Binary search
    // check(lo-1) = false, check(hi) = true
    int lo = 1, hi = maxPile;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    return hi;
  }
};
