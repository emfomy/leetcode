// Source: https://leetcode.com/problems/soup-servings
// Title: Soup Servings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have two soups, **A** and **B**, each starting with `n` mL. On every turn, one of the following four serving operations is chosen at random, each with probability `0.25` **independent** of all previous turns:
//
// - pour 100 mL from type A and 0 mL from type B
// - pour 75 mL from type A and 25 mL from type B
// - pour 50 mL from type A and 50 mL from type B
// - pour 25 mL from type A and 75 mL from type B
//
// **Note:**
//
// - There is no operation that pours 0 mL from A and 100 mL from B.
// - The amounts from A and B are poured simultaneously during the turn.
// - If an operation asks you to pour **more than** you have left of a soup, pour all that remains of that soup.
//
// The process stops immediately after any turn in which one of the soups is used up.
//
// Return the probability that A is used up before B, plus half the probability that both soups are used up in the** same turn**. Answers within `10^-5` of the actual answer will be accepted.
//
// **Example 1:**
//
// ```
// Input: n = 50
// Output: 0.62500
// Explanation:
// If we perform either of the first two serving operations, soup A will become empty first.
// If we perform the third operation, A and B will become empty at the same time.
// If we perform the fourth operation, B will become empty first.
// So the total probability of A becoming empty first plus half the probability that A and B become empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 100
// Output: 0.71875
// Explanation:
// If we perform the first serving operation, soup A will become empty first.
// If we perform the second serving operations, A will become empty on performing operation [1, 2, 3], and both A and B become empty on performing operation 4.
// If we perform the third operation, A will become empty on performing operation [1, 2], and both A and B become empty on performing operation 3.
// If we perform the fourth operation, A will become empty on performing operation 1, and both A and B become empty on performing operation 2.
// So the total probability of A becoming empty first plus half the probability that A and B become empty at the same time, is 0.71875.
// ```
//
// **Constraints:**
//
// - `0 <= n <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <iostream>
#include <ostream>
#include <queue>
#include <unordered_map>

using namespace std;

// DP, MLE
class Solution {
 public:
  double soupServings(int n) {
    auto dp = unordered_map<int, unordered_map<int, double>>();

    double ansA = 0;
    // double ansB = 0;

    dp[n][n] = 1;
    for (auto a = n; a > -100; a -= 25) {
      for (auto [b, p] : dp[a]) {
        if (a <= 0 && b <= 0) {
          ansA += p / 2;
          // ansB += p / 2;
        } else if (a <= 0) {
          ansA += p;
        } else if (b <= 0) {
          // ansB += p;
        } else {
          dp[a - 25][b - 75] += p / 4;
          dp[a - 50][b - 50] += p / 4;
          dp[a - 75][b - 25] += p / 4;
          dp[a - 100][b - 0] += p / 4;
        }
      }
    }

    return ansA;
  }
};

// DP + Heap
class Solution2 {
 public:
  double soupServings(int n) {
    if (n >= 4800) return 1;

    auto prob = unordered_map<uint64_t, double>();
    auto visited = unordered_map<uint64_t, bool>();
    auto key = [](uint64_t a, uint64_t b) -> uint64_t { return (a << 32) + b; };

    double ansA = 0;
    // double ansB = 0;

    auto heap = priority_queue<pair<int, int>>();
    heap.push({n, n});
    prob[key(n, n)] = 1;

    while (heap.size() > 0) {
      auto [a, b] = heap.top();
      auto p = prob[key(a, b)];
      heap.pop();

      if (p < 1e-7) continue;  // too small
      if (visited[key(a, b)]) continue;
      visited[key(a, b)] = true;

      if (a <= 0 && b <= 0) {
        ansA += p / 2;
        // ansB += p / 2;
      } else if (a <= 0) {
        ansA += p;
      } else if (b <= 0) {
        // ansB += p;
      } else {
        prob[key(a - 25, b - 75)] += p / 4;
        heap.push({a - 25, b - 75});

        prob[key(a - 50, b - 50)] += p / 4;
        heap.push({a - 50, b - 50});

        prob[key(a - 75, b - 25)] += p / 4;
        heap.push({a - 75, b - 25});

        prob[key(a - 100, b - 0)] += p / 4;
        heap.push({a - 100, b - 0});
      }
    }

    return ansA;
  }
};

class Solution3 {
  const array<double, 192> ans = {
      0.5,      0.625,    0.625,    0.65625,  0.71875,  0.742188, 0.757812, 0.785156, 0.796875, 0.817871, 0.827637, 0.844849,
      0.852173, 0.866699, 0.872559, 0.884827, 0.889633, 0.900076, 0.904058, 0.913005, 0.916344, 0.924045, 0.92687,  0.933526,
      0.93593,  0.941703, 0.943762, 0.948783, 0.950555, 0.954934, 0.956464, 0.960291, 0.961618, 0.964968, 0.966121, 0.969061,
      0.970066, 0.972648, 0.973525, 0.975797, 0.976565, 0.978566, 0.979239, 0.981004, 0.981595, 0.983153, 0.983672, 0.985049,
      0.985506, 0.986724, 0.987127, 0.988204, 0.98856,  0.989514, 0.989829, 0.990675, 0.990952, 0.991703, 0.991948, 0.992614,
      0.992832, 0.993423, 0.993616, 0.994141, 0.994312, 0.994779, 0.99493,  0.995345, 0.99548,  0.995849, 0.995969, 0.996297,
      0.996404, 0.996696, 0.996791, 0.997051, 0.997135, 0.997368, 0.997442, 0.997649, 0.997716, 0.9979,   0.997959, 0.998124,
      0.998177, 0.998324, 0.998371, 0.998502, 0.998543, 0.99866,  0.998698, 0.998802, 0.998835, 0.998928, 0.998958, 0.999041,
      0.999068, 0.999142, 0.999166, 0.999232, 0.999253, 0.999313, 0.999332, 0.999385, 0.999402, 0.999449, 0.999464, 0.999507,
      0.99952,  0.999558, 0.99957,  0.999604, 0.999615, 0.999645, 0.999654, 0.999682, 0.99969,  0.999714, 0.999722, 0.999744,
      0.999751, 0.99977,  0.999776, 0.999794, 0.999799, 0.999815, 0.99982,  0.999834, 0.999838, 0.999851, 0.999854, 0.999866,
      0.999869, 0.999879, 0.999882, 0.999891, 0.999894, 0.999902, 0.999905, 0.999912, 0.999914, 0.999921, 0.999923, 0.999928,
      0.99993,  0.999935, 0.999937, 0.999942, 0.999943, 0.999947, 0.999948, 0.999952, 0.999953, 0.999957, 0.999958, 0.999961,
      0.999961, 0.999964, 0.999965, 0.999967, 0.999968, 0.99997,  0.999971, 0.999973, 0.999973, 0.999975, 0.999975, 0.999977,
      0.999977, 0.999979, 0.999979, 0.99998,  0.999981, 0.999982, 0.999982, 0.999983, 0.999983, 0.999984, 0.999984, 0.999985,
      0.999985, 0.999986, 0.999986, 0.999987, 0.999987, 0.999987, 0.999988, 0.999988, 0.999988, 0.999989, 0.999989, 0.999989,
  };

 public:
  double soupServings(int n) {
    auto idx = (n + 24) / 25;
    return idx < ans.size() ? ans[idx] : 1;
  }
};
