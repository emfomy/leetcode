// Source: https://leetcode.com/problems/maximum-distance-between-a-pair-of-values
// Title: Maximum Distance Between a Pair of Values
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two **non-increasing 0-indexed **integer arrays `nums1` and `nums2`.
//
// A pair of indices `(i, j)`, where `0 <= i < nums1.length` and `0 <= j < nums2.length`, is **valid** if both `i <= j` and `nums1[i] <= nums2[j]`. The **distance** of the pair is `j - i`.
//
// Return the **maximum distance** of any **valid** pair `(i, j)`. If there are no valid pairs, return `0`.
//
// An array `arr` is **non-increasing** if `arr[i-1] >= arr[i]` for every `1 <= i < arr.length`.
//
// **Example 1:**
//
// ```
// Input: nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
// Output: 2
// Explanation: The valid pairs are (0,0), (2,2), (2,3), (2,4), (3,3), (3,4), and (4,4).
// The maximum distance is 2 with pair (2,4).
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [2,2,2], nums2 = [10,10,1]
// Output: 1
// Explanation: The valid pairs are (0,0), (0,1), and (1,1).
// The maximum distance is 1 with pair (0,1).
// ```
//
// **Example 3:**
//
// ```
// Input: nums1 = [30,29,19,5], nums2 = [25,25,25,25,25]
// Output: 2
// Explanation: The valid pairs are (2,2), (2,3), (2,4), (3,3), and (3,4).
// The maximum distance is 2 with pair (2,4).
// ```
//
// **Constraints:**
//
// - `1 <= nums1.length, nums2.length <= 10^5`
// - `1 <= nums1[i], nums2[j] <= 10^5`
// - Both `nums1` and `nums2` are **non-increasing**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Binary Search
//
// Loop for each i, binary search for rightmost j.
class Solution {
 public:
  int maxDistance(vector<int>& nums1, vector<int>& nums2) {
    const int n1 = nums1.size(), n2 = nums2.size();

    // Loop
    int maxDist = 0;
    for (int i = 0; i < n1; ++i) {
      int num1 = nums1[i];

      // Binary Search
      // check(lo-1) = true, check(hi) = false
      int lo = i, hi = n2;  // [i, n2) unknown
      while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (num1 <= nums2[mid]) {
          lo = mid + 1;
        } else {
          hi = mid;
        }
      }
      maxDist = max(maxDist, lo - 1 - i);
    }

    return maxDist;
  }
};

// Sliding Window
//
// Assume nums2[-1] = INF.
// Init i = 0 and j = -1.
// Loop i, move j to the right to find next valid.
class Solution2 {
 public:
  int maxDistance(vector<int>& nums1, vector<int>& nums2) {
    const int n1 = nums1.size(), n2 = nums2.size();

    // Loop
    int maxDist = 0, j = -1;
    for (int i = 0; i < n1; ++i) {
      while (j + 1 < n2 && nums1[i] <= nums2[j + 1]) ++j;
      maxDist = max(maxDist, j - i);
    }

    return maxDist;
  }
};
