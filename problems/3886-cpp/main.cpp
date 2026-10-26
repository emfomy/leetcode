// Source: https://leetcode.com/problems/sum-of-sortable-integers
// Title: Sum of Sortable Integers
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` of length `n`.
//
// An integer `k` is called **sortable** if `k` **divides** `n` and you can sort `nums` in **non-decreasing** order by sequentially performing the following operations:
//
// - Partition `nums` into **consecutive <button>subarrays</button>** of length `k`.
// - **Cyclically rotate each subarray independently** any number of times to the left or to the right.
//
// Return an integer denoting the sum of all possible sortable integers `k`.
//
// **Example 1:**
//
// ```
// Input: nums = [3,1,2]
// Output: 3
// Explanation:
// - For `n = 3`, possible divisors are 1 and 3.
// - For `k = 1`: each subarray has one element. No rotation can sort the array.
// - For `k = 3`: the single subarray `[3, 1, 2]` can be rotated once to produce `[1, 2, 3]`, which is sorted.
// - Only `k = 3` is sortable. Hence, the answer is 3.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [7,6,5]
// Output: 0
// Explanation:
// - For `n = 3`, possible divisors are 1 and 3.
// - For `k = 1`: each subarray has one element. No rotation can sort the array.
// - For `k = 3`: the single subarray `[7, 6, 5]` cannot be rotated into non-decreasing order.
// - No `k` is sortable. Hence, the answer is 0.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [5,8]
// Output: 3
// Explanation:
// - For `n = 2`, possible divisors are 1 and 2.
// - Since `[5, 8]` is already sorted, every divisor is sortable. Hence, the answer is `1 + 2 = 3`.
// ```
//
// **Constraints:**
//
// - `1 <= n == nums.length <= 10^5`
// - `1 <= nums[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Brute-Force
//
// Loop for each k.
// For each subarray, partition into two sorted segment.
class Solution {
  using Iter = vector<int>::const_iterator;

 public:
  int sortableIntegers(const vector<int>& nums) {
    const int n = nums.size();

    int ans = 0;
    for (int k = 1; k * k <= n; ++k) {
      if (n % k != 0) continue;
      if (isSortable(nums, k)) ans += k;
      if (k != n / k && isSortable(nums, n / k)) ans += n / k;
    }

    return ans;
  }

  bool isSortable(const vector<int>& nums, int k) {
    const int n = nums.size();

    // k=1
    if (k == 1) {
      return is_sorted(nums.cbegin(), nums.cend());
    }

    // Loop
    int prevNum = 0;
    for (int i = 0; i < n / k; ++i) {
      if (!isCyclicSortable(nums.cbegin() + i * k, nums.cbegin() + i * k + k, prevNum)) return false;
    }

    return true;
  }

  bool isCyclicSortable(Iter begin, Iter end, int& prevNum) {
    // Partition into two sorted segment
    auto mid = is_sorted_until(begin, end);

    // Second segment is not sorted
    if (!is_sorted(mid, end)) return false;

    // Second segment is empty
    if (mid == end) {
      if (*begin < prevNum) return false;
      prevNum = *(end - 1);
      return true;
    }

    // Front of first segment is smaller than back of second segment.
    if (*begin < *(end - 1)) return false;

    // Compare to previous number
    if (*mid < prevNum) return false;
    prevNum = *(mid - 1);
    return true;
  }
};
