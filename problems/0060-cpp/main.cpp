// Source: https://leetcode.com/problems/permutation-sequence
// Title: Permutation Sequence
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The set `[1, 2, 3, ...,n]` contains a total of `n!` unique permutations.
//
// By listing and labeling all of the permutations in order, we get the following sequence for `n = 3`:
//
// - `"123"`
// - `"132"`
// - `"213"`
// - `"231"`
// - `"312"`
// - `"321"`
//
// Given `n` and `k`, return the `k^th` permutation sequence.
//
// **Example 1:**
//
// ```
// Input: n = 3, k = 3
// Output: "213"
// ```
//
// **Example 2:**
//
// ```
// Input: n = 4, k = 9
// Output: "2314"
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3, k = 1
// Output: "123"
// ```
//
// **Constraints:**
//
// - `1 <= n <= 9`
// - `1 <= k <= n!`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  string getPermutation(int n, int k) {
    auto seq = string(n, '0');
    iota(seq.begin(), seq.end(), '1');

    for (auto i = 1; i < k; ++i) {
      next_permutation(seq.begin(), seq.end());
    }

    return seq;
  }
};

class Solution2 {
  const int facts[9] = {
      1,
      1,
      1 * 2,
      1 * 2 * 3,
      1 * 2 * 3 * 4,
      1 * 2 * 3 * 4 * 5,
      1 * 2 * 3 * 4 * 5 * 6,
      1 * 2 * 3 * 4 * 5 * 6 * 7,
      1 * 2 * 3 * 4 * 5 * 6 * 7 * 8,
  };

 public:
  string getPermutation(int n, int k) {
    auto nums = list<char>(n);
    iota(nums.begin(), nums.end(), '1');

    string ans;
    --k;
    for (auto i = n - 1; i >= 0; --i) {
      auto d = k / facts[i];
      k %= facts[i];

      auto it = nums.begin();
      advance(it, d);

      ans += (*it);
      nums.erase(it);
    }

    return ans;
  }
};
