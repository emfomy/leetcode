// Source: https://leetcode.com/problems/count-subarrays-with-majority-element-i
// Title: Count Subarrays With Majority Element I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums` and an integer `target`.
//
// Return the number of **<button>subarrays</button>** of `nums` in which `target` is the **majority element**.
//
// The **majority element** of a subarray is the element that appears **strictly** **more than half** of the times in that subarray.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,2,3], target = 2
// Output: 5
// Explanation:
// Valid subarrays with `target = 2` as the majority element:
// - `nums[1..1] = [2]`
// - `nums[2..2] = [2]`
// - `nums[1..2] = [2,2]`
// - `nums[0..2] = [1,2,2]`
// - `nums[1..3] = [2,2,3]`
// So there are 5 such subarrays.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,1,1,1], target = 1
// Output: 10
// Explanation:
// All 10 subarrays have 1 as the majority element.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3], target = 4
// Output: 0
// Explanation:
// `target = 4` does not appear in `nums` at all. Therefore, there cannot be any subarray where 4 is the majority element. Hence the answer is 0.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 1000`
// - `1 <= nums[i] <= 10^9`
// - `1 <= target <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix Count
//
// Prefix count the target element.
class Solution {
 public:
  int countMajoritySubarrays(const vector<int>& nums, int target) {
    const int n = nums.size();

    auto prefix = vector<int>(n + 1);
    for (int i = 0; i < n; ++i) {
      prefix[i + 1] = prefix[i] + (nums[i] == target);
    }

    int count = 0;
    for (int l = 0; l < n; ++l) {
      for (int r = l + 1; r <= n; ++r) {
        count += ((prefix[r] - prefix[l]) * 2 > (r - l));
      }
    }

    return count;
  }
};

// Prefix Sum
//
// Define a new array `arr`.
// arr[i] = 1  if nums[i] = target;
// arr[i] = -1 if nums[i] != target.
//
// A subarray [l, r) is our objective if sum of arr in [l, r) is positive.
// Use prefix sum on arr to speed up the computation.
class Solution2 {
 public:
  int countMajoritySubarrays(const vector<int>& nums, int target) {
    const int n = nums.size();

    auto prefix = vector<int>(n + 1);
    for (int i = 0; i < n; ++i) {
      prefix[i + 1] = prefix[i] + ((nums[i] == target) ? 1 : -1);
    }

    int count = 0;
    for (int l = 0; l < n; ++l) {
      for (int r = l + 1; r <= n; ++r) {
        count += prefix[l] < prefix[r];
      }
    }

    return count;
  }
};

// Prefix Sum + Fenwick Tree
//
// Define the `prefix` array as above.
// Note that we want to count the number of [l, r) with prefix[l] < prefix[r].
//
// Use Fenwick Tree on the prefix array.
// We use it to count the number of prefix[r],
// with given l < r and prefix[l] < prefix[r].
//
// To do so, we first index sort the prefix array.
// Start from the smallest prefix[r].
// Add 1 into the tree at index r.
// For each r, sum for l < r in the tree (i.e. number of l satisfy the condition).
//
// Since we want strictly less (prefix[l] < prefix[r]),
// if there are two r with the same value, we start from the right one.
class Solution3 {
  class FenwickTree {
    int n;
    vector<int> tree;  // tree[i] = sum of range [i-lowbit(i), i); length is lowbit(i)

   public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}

    // Update: O(logN); nums[idx] += delta
    void update(int idx, int delta) {
      // start at x+1 since x in [0, x+1)
      for (int i = idx + 1; i <= n; i += (i & -i)) {
        tree[i] += delta;
      }
    }

    // Query: O(logN); Sum of [0, r)
    int query(int r) const {
      int sum = 0;
      for (int i = r; i >= 1; i -= (i & -i)) {
        sum += tree[i];
      }
      return sum;
    }
  };

 public:
  int countMajoritySubarrays(const vector<int>& nums, int target) {
    const int n = nums.size();

    // Prefix sum
    auto prefix = vector<pair<int, int>>(n + 1);  // (prefix[i], -i), use -i for sorting
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += ((nums[i] == target) ? 1 : -1);
      prefix[i + 1] = {sum, -(i + 1)};
    }

    // Sort
    sort(prefix.begin(), prefix.end());

    // Count
    auto tree = FenwickTree(n);
    int count = 0;
    for (auto item : prefix) {
      int r = -item.second;
      count += tree.query(r);
      tree.update(r, 1);
    }

    return count;
  }
};

// Prefix Sum + Count
//
// Define the `prefix` array as above.
// Note that we want to count the number of [l, r) with prefix[l] < prefix[r].
//
// Loop r from 0 to n, and count the number of prefix values.
// Use a value for accumulation sum.
//
// If current prefix[r] increases (i.e. nums[r] == target),
// add the number of prefix[r] (not including this one) to the accumulation sum.
// If decreases, substract prefix[r-1] from the accumulation sum.
class Solution4 {
 public:
  int countMajoritySubarrays(const vector<int>& nums, int target) {
    const int n = nums.size();

    // Loop
    auto freqs = vector<int>(2 * n + 1);  // freq of prefix[i] of value [-n, ..., n]; offset by n
    freqs[n] = 1;
    int presum = n;     // prefix[r]
    int currCount = 0;  // valid l for this r
    int count = 0;      // valid subarrays
    for (int num : nums) {
      if (num == target) {
        currCount += freqs[presum];
        ++presum;
        ++freqs[presum];
      } else {
        --presum;
        currCount -= freqs[presum];
        ++freqs[presum];
      }
      count += currCount;
    }

    return count;
  }
};
