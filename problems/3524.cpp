// Source: https://leetcode.com/problems/find-x-value-of-array-i
// Title: Find X Value of Array I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array of **positive** integers `nums`, and a **positive** integer `k`.
//
// You are allowed to perform an operation **once** on `nums`, where in each operation you can remove any **non-overlapping** prefix and suffix from `nums` such that `nums` remains **non-empty**.
//
// You need to find the **x-value** of `nums`, which is the number of ways to perform this operation so that the **product** of the remaining elements leaves a remainder of `x` when divided by `k`.
//
// Return an array `result` of size `k` where `result[x]` is the **x-value** of `nums` for `0 <= x <= k - 1`.
//
// A **prefix** of an array is a <button>subarray</button> that starts from the beginning of the array and extends to any point within it.
//
// A **suffix** of an array is a <button>subarray</button> that starts at any point within the array and extends to the end of the array.
//
// **Note** that the prefix and suffix to be chosen for the operation can be **empty**.
//
// **Example 1:**
//
// ```
// Input: nums = [1,2,3,4,5], k = 3
// Output: [9,2,4]
// Explanation:
// - For `x = 0`, the possible operations include all possible ways to remove non-overlapping prefix/suffix that do not remove `nums[2] == 3`.
// - For `x = 1`, the possible operations are:
//   - Remove the empty prefix and the suffix `[2, 3, 4, 5]`. `nums` becomes `[1]`.
//   - Remove the prefix `[1, 2, 3]` and the suffix `[5]`. `nums` becomes `[4]`.
// - For `x = 2`, the possible operations are:
//   - Remove the empty prefix and the suffix `[3, 4, 5]`. `nums` becomes `[1, 2]`.
//   - Remove the prefix `[1]` and the suffix `[3, 4, 5]`. `nums` becomes `[2]`.
//   - Remove the prefix `[1, 2, 3]` and the empty suffix. `nums` becomes `[4, 5]`.
//   - Remove the prefix `[1, 2, 3, 4]` and the empty suffix. `nums` becomes `[5]`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,4,8,16,32], k = 4
// Output: [18,1,2,0]
// Explanation:
// - For `x = 0`, the only operations that **do not** result in `x = 0` are:
//   - Remove the empty prefix and the suffix `[4, 8, 16, 32]`. `nums` becomes `[1, 2]`.
//   - Remove the empty prefix and the suffix `[2, 4, 8, 16, 32]`. `nums` becomes `[1]`.
//   - Remove the prefix `[1]` and the suffix `[4, 8, 16, 32]`. `nums` becomes `[2]`.
// - For `x = 1`, the only possible operation is:
//   - Remove the empty prefix and the suffix `[2, 4, 8, 16, 32]`. `nums` becomes `[1]`.
// - For `x = 2`, the possible operations are:
//   - Remove the empty prefix and the suffix `[4, 8, 16, 32]`. `nums` becomes `[1, 2]`.
//   - Remove the prefix `[1]` and the suffix `[4, 8, 16, 32]`. `nums` becomes `[2]`.
// - For `x = 3`, there is no possible way to perform the operation.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,1,2,1,1], k = 2
// Output: [9,6]
// ```
//
// **Constraints:**
//
// - `1 <= nums[i] <= 10^9`
// - `1 <= nums.length <= 10^5`
// - `1 <= k <= 5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <vector>

using namespace std;

// 2D-DP
//
// The problem is equal as follows:
// For all subarray of nums, count the number of the product reminder.
//
// Use DP to do so.
// Let DP[r, i] be the number of subarray end at i with reminder r.
class Solution {
 public:
  vector<long long> resultArray(const vector<int>& nums, int k) {
    const int n = nums.size();

    // DP
    auto dp = vector(k, vector<long long>(n + 1));
    for (int i = 0; i < n; ++i) {
      int num = nums[i] % k;
      dp[num][i + 1] = 1;  // new subarray
      for (int r = 0; r < k; ++r) {
        dp[(r * num) % k][i + 1] += dp[r][i];  // extend subarray
      }
    }

    // Answer
    auto ans = vector<long long>(k);
    for (int r = 0; r < k; ++r) {
      ans[r] = accumulate(dp[r].cbegin(), dp[r].cend(), 0LL);
    }

    return ans;
  }
};

// 1D-DP
class Solution2 {
 public:
  vector<long long> resultArray(const vector<int>& nums, int k) {
    const int n = nums.size();

    // DP
    auto ans = vector<long long>(k);
    auto curr = vector<long long>(k);
    auto prev = vector<long long>(k);
    for (int i = 0; i < n; ++i) {
      swap(curr, prev);
      fill(curr.begin(), curr.end(), 0LL);

      int num = nums[i] % k;
      curr[num] = 1;  // new subarray
      for (int r = 0; r < k; ++r) {
        curr[(r * num) % k] += prev[r];  // extend subarray
      }

      for (int r = 0; r < k; ++r) {
        ans[r] += curr[r];
      }
    }

    return ans;
  }
};
