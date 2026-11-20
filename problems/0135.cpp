// Source: https://leetcode.com/problems/candy
// Title: Candy
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.
//
// You are giving candies to these children subjected to the following requirements:
//
// - Each child must have at least one candy.
// - Children with a higher rating get more candies than their neighbors.
//
// Return the minimum number of candies you need to have to distribute the candies to the children.
//
// **Example 1:**
//
// ```
// Input: ratings = [1,0,2]
// Output: 5
// Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
// ```
//
// **Example 2:**
//
// ```
// Input: ratings = [1,2,2]
// Output: 4
// Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
// The third child gets 1 candy because it satisfies the above two conditions.
// ```
//
// **Constraints:**
//
// - `n == ratings.length`
// - `1 <= n <= 2 * 10^4`
// - `0 <= ratings[i] <= 2 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// Greedy + Sort
//
// Sort the ratings and loop from the lowest.
// For each child, give him/her a little bit more candies then his/her neighbor.
class Solution {
 public:
  int candy(const vector<int>& ratings) {
    const int n = ratings.size();

    // Sort ratings
    auto idxs = vector<int>(n);
    auto comp = [&ratings](int i, int j) -> bool { return ratings[i] < ratings[j]; };
    iota(idxs.begin(), idxs.end(), 0);
    sort(idxs.begin(), idxs.end(), comp);

    // Greedy
    auto candies = vector<int>(n);
    for (int idx : idxs) {
      if (idx > 0 && ratings[idx] > ratings[idx - 1]) candies[idx] = max(candies[idx], candies[idx - 1] + 1);
      if (idx < n - 1 && ratings[idx] > ratings[idx + 1]) candies[idx] = max(candies[idx], candies[idx + 1] + 1);
    }

    return accumulate(candies.cbegin(), candies.cend(), 0);
  }
};

// Traverse both direction
//
// First scan from left to right, and apply the constraint to the left.
// Next scan from right to left, and apply the constraint to the right.
class Solution2 {
 public:
  int candy(const vector<int>& ratings) {
    const int n = ratings.size();

    auto candies = vector<int>(n, 1);

    // Left to right
    for (int i = 1; i < n; ++i) {
      if (ratings[i] > ratings[i - 1]) candies[i] = max(candies[i], candies[i - 1] + 1);
    }

    // Right to left
    for (int i = n - 2; i >= 0; --i) {
      if (ratings[i] > ratings[i + 1]) candies[i] = max(candies[i], candies[i + 1] + 1);
    }

    return accumulate(candies.cbegin(), candies.cend(), 0);
  }
};
