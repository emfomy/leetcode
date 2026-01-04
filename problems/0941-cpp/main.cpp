// Source: https://leetcode.com/problems/valid-mountain-array
// Title: Valid Mountain Array
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `arr`, return `true` if and only if it is a valid mountain array.
//
// Recall that arr is a mountain array if and only if:
//
// - `arr.length >= 3`
// - There exists some `i` with `0 < i < arr.length - 1` such that:
//
// - `arr[0] < arr[1] < ... < arr[i - 1] < arr[i] `
// - `arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`
//
// https://assets.leetcode.com/uploads/2019/10/20/hint_valid_mountain_array.png
//
// **Example 1:**
//
// ```
// Input: arr = [2,1]
// Output: false
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [3,5,5]
// Output: false
// ```
//
// **Example 3:**
//
// ```
// Input: arr = [0,3,2,1]
// Output: true
// ```
//
// **Constraints:**
//
// - `1 <= arr.length <= 10^4`
// - `0 <= arr[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// One pass
class Solution {
 public:
  bool validMountainArray(vector<int>& arr) {
    int n = arr.size();
    if (n < 3) return false;

    int i = 0;

    // Check increasing
    while (i + 1 < n && arr[i] < arr[i + 1]) ++i;

    // Check position
    if (i == 0 || i == n - 1) return false;

    // Check decreasing
    while (i + 1 < n && arr[i] > arr[i + 1]) ++i;

    return i == n - 1;
  }
};
