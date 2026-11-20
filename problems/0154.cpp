// Source: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii
// Title: Find Minimum in Rotated Sorted Array II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:
//
// 	[4,5,6,7,0,1,4] if it was rotated 4 times.
// 	[0,1,4,4,5,6,7] if it was rotated 7 times.
//
// Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
//
// Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.
//
// You must decrease the overall operation steps as much as possible.
//
// Example 1:
//
// ```
// Input: nums = [1,3,5]
// Output: 1
// ```
//
// Example 2:
//
// ```
// Input: nums = [2,2,2,0,1]
// Output: 0
// ```
//
// Constraints:
//
// 	n == nums.length
// 	1 <= n <= 5000
// 	-5000 <= nums[i] <= 5000
// 	nums is sorted and rotated between 1 and n times.
//
// Follow up: This problem is similar to Find Minimum in Rotated Sorted Array, but nums may contain duplicates. Would this affect the runtime complexity? How and why?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Linear Search
class Solution {
 public:
  int findMin(const vector<int>& nums) {  //
    return *min_element(nums.cbegin(), nums.cend());
  }
};

// Binary Search
//
// Pick the last number x.
// Assume that the first number is not x.
// Mark all number with val >  x as LEFT,
// Mark all number with val <= x as RIGHT.
// Use binary search to find first RIGHT.
//
// However, if the first is also equal,
// we linear scan from the right to find the first non-x number.
// Use that number as the new x, and apply the same algorithm.
class Solution2 {
 public:
  int findMin(const vector<int>& nums) {
    const int n = nums.size();

    const int back = nums.back();

    // Check first element
    const auto comp = [back](int num) { return num != back; };
    int lo = find_if(nums.cbegin(), nums.cend(), comp) - nums.cbegin();
    if (lo == n) return back;  // all equal

    // Binary Search
    // lo-1=LEFT, hi=RIGHT
    int hi = n;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (nums[mid] > back) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return nums[hi];
  }
};

// Binary Search (STL)
class Solution3 {
 public:
  int findMin(const vector<int>& nums) {
    const int n = nums.size();

    const int back = nums.back();

    // Check first element
    const auto comp = [back](int num) { return num != back; };
    auto begin = find_if(nums.cbegin(), nums.cend(), comp);
    if (begin == nums.cend()) return back;  // all equal

    // Binary search
    const auto comp2 = [back](int a, int b) {  //
      return int(a <= back) < int(b <= back);
    };

    return *lower_bound(begin, nums.cend(), back, comp2);
  }
};
