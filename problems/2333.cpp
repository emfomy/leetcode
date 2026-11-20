// Source: https://leetcode.com/problems/minimum-sum-of-squared-difference
// Title: Minimum Sum of Squared Difference
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two positive **0-indexed** integer arrays `nums1` and `nums2`, both of length `n`.
//
// The **sum of squared difference** of arrays `nums1` and `nums2` is defined as the **sum** of `(nums1[i] - nums2[i])^2` for each `0 <= i < n`.
//
// You are also given two positive integers `k1` and `k2`. You can modify any of the elements of `nums1` by `+1` or `-1` at most `k1` times. Similarly, you can modify any of the elements of `nums2` by `+1` or `-1` at most `k2` times.
//
// Return the minimum **sum of squared difference** after modifying array `nums1` at most `k1` times and modifying array `nums2` at most `k2` times.
//
// **Note**: You are allowed to modify the array elements to become **negative** integers.
//
// **Example 1:**
//
// ```
// Input: nums1 = [1,2,3,4], nums2 = [2,10,20,19], k1 = 0, k2 = 0
// Output: 579
// Explanation: The elements in nums1 and nums2 cannot be modified because k1 = 0 and k2 = 0.
// The sum of square difference will be: (1 - 2)^2 + (2 - 10)^2 + (3 - 20)^2 + (4 - 19)^2= 579.
// ```
//
// **Example 2:**
//
// ```
// Input: nums1 = [1,4,10,12], nums2 = [5,8,6,9], k1 = 1, k2 = 1
// Output: 43
// Explanation: One way to obtain the minimum sum of square difference is:
// - Increase nums1[0] once.
// - Increase nums2[2] once.
// The minimum of the sum of square difference will be:
// (2 - 5)^2 + (4 - 8)^2 + (10 - 7)^2 + (12 - 9)^2= 43.
// Note that, there are other ways to obtain the minimum of the sum of square difference, but there is no way to obtain a sum smaller than 43.```
//
// **Constraints:**
//
// - `n == nums1.length == nums2.length`
// - `1 <= n <= 10^5`
// - `0 <= nums1[i], nums2[i] <= 10^5`
// - `0 <= k1, k2 <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

using namespace std;

// Greedy + Sort
//
// It is always better to modify the larger diffs.
// Therefore, we can use greedy to find threshold (i.e. max diff after modify).
//
// Let d[i] be the diff. First sort it from large to small.
// For each step, we modify every element before down to current on (if there is enough k).
class Solution {
 public:
  long long minSumSquareDiff(vector<int>& nums1, const vector<int>& nums2, int k1, int k2) {
    const int n = nums1.size();
    long long k = (long long)(k1) + k2;

    // Get diffs
    auto& diff = nums1;  // reuse nums1
    for (int i = 0; i < n; ++i) {
      diff[i] = abs(nums1[i] - nums2[i]);
    }

    // Trivial, total sum is smaller than k
    if (accumulate(diff.cbegin(), diff.cend(), 0LL) <= k) return 0;

    // Sort
    sort(diff.begin(), diff.end(), greater<>());
    diff.push_back(0);  // avoid boundary check

    // Modify
    for (int i = 1; i <= n; ++i) {
      long long cost = (long long)(diff[i - 1] - diff[i]) * i;  // reduce all before to diff[i]

      if (cost > k) {                    // not enough k
        long long q = k / i, r = k % i;  // last r will be smaller
        long long hi = diff[i - 1] - q;
        long long lo = hi - 1;
        long long ans = hi * hi * (i - r) + lo * lo * r;
        for (int j = i; j < n; ++j) {
          ans += (long long)(diff[j]) * diff[j];
        }
        return ans;
      } else {
        k -= cost;
      }
    }

    return 0;
  }
};
