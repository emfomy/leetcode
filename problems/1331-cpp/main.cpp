// Source: https://leetcode.com/problems/rank-transform-of-an-array
// Title: Rank Transform of an Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `arr`, replace each element with its rank.
//
// The rank represents how large the element is. The rank has the following rules:
//
// - Rank is an integer starting from 1.
// - The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
// - Rank should be as small as possible.
//
// **Example 1:**
//
// ```
// Input: arr = [40,10,20,30]
// Output: [4,1,2,3]
// Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.```
//
// **Example 2:**
//
// ```
// Input: arr = [100,100,100]
// Output: [1,1,1]
// Explanation: Same elements share the same rank.
// ```
//
// **Example 3:**
//
// ```
// Input: arr = [37,12,28,9,100,56,80,5,12]
// Output: [5,3,4,2,8,6,7,1,3]
// ```
//
// **Constraints:**
//
// - `0 <= arr.length <= 10^5`
// - `-10^9<= arr[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> arrayRankTransform(const vector<int>& arr) {
    const int n = arr.size();
    if (n == 0) return {};

    // Sort
    auto orders = vector<int>(n);  // orders[rank] = original_idx
    auto comp = [&arr](int i, int j) -> bool { return arr[i] < arr[j]; };
    iota(orders.begin(), orders.end(), 0);
    sort(orders.begin(), orders.end(), comp);

    // Rank
    auto ranks = vector<int>(n);  // ranks[original_idx] = order
    int rank = 1, prevNum = arr[orders[0]];
    for (int order : orders) {
      int num = arr[order];
      if (num > prevNum) ++rank;
      prevNum = num;

      ranks[order] = rank;
    }

    return ranks;
  }
};
