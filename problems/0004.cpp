// Source: https://leetcode.com/problems/median-of-two-sorted-arrays
// Title: Median of Two Sorted Arrays
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively, return **the median** of the two sorted arrays.
//
// The overall run time complexity should be `O(log (m+n))`.
//
// **Example 1:**
//
// ```
// Input: nums1 = [1,3], nums2 = [2]
// Output: 2.00000
// Explanation: merged array = [1,2,3] and median is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [1,2], nums2 = [3,4]
// Output: 2.50000
// Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
// ```
//
// **Constraints:**
//
// - `nums1.length == m`
// - `nums2.length == n`
// - `0 <= m <= 1000`
// - `0 <= n <= 1000`
// - `1 <= m + n <= 2000`
// - `-10^6 <= nums1[i], nums2[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;

// Merge, O(n)
class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int mn = nums1.size() + nums2.size();
    auto nums = vector<int>(mn);
    merge(nums1.cbegin(), nums1.cend(), nums2.cbegin(), nums2.cend(), nums.begin());
    return double(nums[(mn - 1) / 2] + nums[mn / 2]) / 2;
  }
};

// Binary search
//
// Denote the two arrays as A and B.
//
// Finding medium means to spit the array into two equal-sized partition,
// Where the maximum of the left part is less than the minimum of the right part.
//
// Use binary search on the shorter array (WLOG, say A).
// Say we split A at i, then B is automatically split at j = half - i.
// Denote A_l = A[i-1], A_r = A[i], B_l = B[j-1], B_r = B[j]. (Assign +-inf for out of bound values.)
// The partition is valid iff A_l <= B_r and B_l <= A_r.
//
// For final answer, if the array size is
// odd:  ans = max(A_l, B_l)
// even: ans = (max(A_l, B_l) + min(A_r, B_r)) / 2
class Solution2 {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    const int n = n1 + n2;
    const int half = (n + 1) / 2;  // ensure left part is larger

    // WLOG, assume n1 <= n2
    if (n1 > n2) {
      swap(n1, n2);
      swap(nums1, nums2);
    }

    // Binary search on split point of nums1
    int lo = 0, hi = n1 + 1;  // unknown range [0, n1]
    while (lo < hi) {
      // Split points
      int mid1 = lo + (hi - lo) / 2;
      int mid2 = half - mid1;

      // Values around split points
      int left1 = (mid1 == 0) ? INT_MIN : nums1[mid1 - 1];
      int left2 = (mid2 == 0) ? INT_MIN : nums2[mid2 - 1];
      int right1 = (mid1 == n1) ? INT_MAX : nums1[mid1];
      int right2 = (mid2 == n2) ? INT_MAX : nums2[mid2];

      // Found valid split
      if (left1 <= right2 && left2 <= right1) {
        if (n % 2) {  // Odd size
          return max(left1, left2);
        } else {  // Even size
          return (max(left1, left2) + min(right1, right2)) / 2.0;
        }
      }

      if (left1 > right2) {  // mid1 too right
        hi = mid1;
      } else {  // mid1 too left
        lo = mid1 + 1;
      }
    }

    return NAN;  // unreachable
  }
};
