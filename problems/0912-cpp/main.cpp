// Source: https://leetcode.com/problems/sort-an-array
// Title: Sort an Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of integers `nums`, sort the array in ascending order and return it.
//
// You must solve the problem **without using any built-in** functions in `O(nlog(n))` time complexity and with the smallest space complexity possible.
//
// **Example 1:**
//
// ```
// Input: nums = [5,2,3,1]
// Output: [1,2,3,5]
// Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [5,1,1,2,0,0]
// Output: [0,0,1,1,2,5]
// Explanation: Note that the values of nums are not necessarily unique.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 5 * 10^4`
// - `-5 * 10^4 <= nums[i] <= 5 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Quick Sort (3-way)
class Solution {
 public:
  vector<int> sortArray(vector<int>& nums) {
    quickSort(nums, 0, nums.size());
    return nums;
  }

  void quickSort(vector<int>& nums, int lo, int hi) {
    if (lo >= hi) return;

    auto pivot = nums[lo];

    // [lo, l) < pivot, [l, i) = pivot, [i, r) unknown, [r, hi) > pivot
    auto l = lo;
    auto i = lo;
    auto r = hi;
    while (i < r) {
      if (nums[i] < pivot) {  // increase i since nums[l] is known as pivot
        swap(nums[l++], nums[i++]);
      } else if (nums[i] > pivot) {  // don't increase i since nums[r-1] is unknown
        swap(nums[i], nums[--r]);
      } else {
        ++i;
      }
    }

    quickSort(nums, lo, l);
    quickSort(nums, r, hi);
  }
};

// Merge Sort
class Solution2 {
 public:
  vector<int> sortArray(vector<int>& nums) {
    int n = nums.size();

    auto tmp = vector<int>(n);
    for (auto step = 1; step <= n; step *= 2) {
      for (auto lo = 0; lo < n; lo += step * 2) {
        auto mid = min(lo + step, n), hi = min(lo + step * 2, n);

        // Merge [lo, mid) & [mid, hi)
        auto i = lo, j = mid, k = lo;
        while (i < mid && j < hi) {
          if (nums[i] <= nums[j]) {
            tmp[k++] = nums[i++];
          } else {
            tmp[k++] = nums[j++];
          }
        }
        while (i < mid) {
          tmp[k++] = nums[i++];
        }
        while (j < hi) {
          tmp[k++] = nums[j++];
        }
      }
      swap(nums, tmp);
    }
    return nums;
  }
};

// Heap Sort
class Solution3 {
 public:
  vector<int> sortArray(vector<int>& nums) {
    int n = nums.size();

    // Heapify
    for (auto i = n / 2 - 1; i >= 0; --i) {  // loop from last parent
      heapify(nums, i, n);
    }

    // Sort
    for (auto i = n - 1; i >= 0; --i) {
      swap(nums[0], nums[i]);  // move largest to the end
      heapify(nums, 0, i);
    }

    return nums;
  }

  // Max heap
  void heapify(vector<int>& nums, int parent, int end) {
    auto child = parent * 2 + 1;
    while (child < end) {
      // Choose larger child
      if (child + 1 < end && nums[child] < nums[child + 1]) ++child;

      // Ensure parent if larger
      if (nums[parent] > nums[child]) break;

      swap(nums[parent], nums[child]);
      parent = child;
      child = parent * 2 + 1;
    }
  }
};
