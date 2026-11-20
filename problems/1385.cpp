// Source: https://leetcode.com/problems/find-the-distance-value-between-two-arrays
// Title: Find the Distance Value Between Two Arrays
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integer arrays `arr1` and `arr2`, and the integer `d`, return the distance value between the two arrays.
//
// The distance value is defined as the number of elements `arr1[i]` such that there is not any element `arr2[j]` where `|arr1[i]-arr2[j]| <= d`.
//
// **Example 1:**
//
// ```
// Input: arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
// Output: 2
// Explanation:
// For arr1[0]=4 we have:
// |4-10|=6 > d=2
// |4-9|=5 > d=2
// |4-1|=3 > d=2
// |4-8|=4 > d=2
// For arr1[1]=5 we have:
// |5-10|=5 > d=2
// |5-9|=4 > d=2
// |5-1|=4 > d=2
// |5-8|=3 > d=2
// For arr1[2]=8 we have:
// **|8-10|=2 <= d=2**
// **|8-9|=1 <= d=2**
// |8-1|=7 > d=2
// **|8-8|=0 <= d=2**
// ```
//
// **Example 2:**
//
// ```
// Input: arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
// Output: 2
// ```
//
// **Example 3:**
//
// ```
// Input: arr1 = [2,1,100,3], arr2 = [-5,-2,10,-3,7], d = 6
// Output: 1
// ```
//
// **Constraints:**
//
// - `1 <= arr1.length, arr2.length <= 500`
// - `-1000 <= arr1[i], arr2[j] <= 1000`
// - `0 <= d <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Brute-Force
class Solution {
 public:
  int findTheDistanceValue(const vector<int>& arr1, const vector<int>& arr2, int d) {
    int ans = 0;
    for (int num1 : arr1) {
      bool valid = true;
      for (int num2 : arr2) {
        if (abs(num1 - num2) <= d) {
          valid = false;
          break;
        }
      }
      ans += valid;
    }

    return ans;
  }
};

// Binary Search
//
// First sort arr2.
// For each number x in arr1,
// check if there is no number in [x-d, x+d] using binary search.
class Solution2 {
 public:
  int findTheDistanceValue(const vector<int>& arr1, vector<int>& arr2, int d) {
    // Sort
    sort(arr2.begin(), arr2.end());

    // Loop
    int ans = 0;
    for (int x : arr1) {
      // x-d <= lo, first element in the range (if exist)
      auto lo = lower_bound(arr2.cbegin(), arr2.cend(), x - d);

      // not found or outside the range
      ans += (lo == arr2.cend()) || (*lo > x + d);
    }

    return ans;
  }
};
