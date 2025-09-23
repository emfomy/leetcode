// Source: https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero
// Title: Find N Unique Integers Sum up to Zero
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, return **any** array containing `n` **unique** integers such that they add up to `0`.
//
// **Example 1:**
//
// ```
// Input: n = 5
// Output: [-7,-1,1,3,4]
// Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3
// Output: [-1,0,1]
// ```
//
// **Example 3:**
//
// ```
// Input: n = 1
// Output: [0]
// ```
//
// **Constraints:**
//
// - `1 <= n <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// [-n(n-1)/2, 1, 2, 3, ..., n-1]
class Solution {
 public:
  vector<int> sumZero(int n) {
    auto ans = vector<int>(n, 0);
    iota(ans.begin(), ans.end(), 0);
    ans[0] = -n * (n - 1) / 2;
    return ans;
  }
};
