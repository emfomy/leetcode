// Source: https://leetcode.com/problems/ways-to-make-a-fair-array
// Title: Ways to Make a Fair Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array`nums`. You can choose **exactly one** index (**0-indexed**) and remove the element. Notice that the index of the elements may change after the removal.
//
// For example, if `nums = [6,1,7,4,1]`:
//
// - Choosing to remove index `1` results in `nums = [6,7,4,1]`.
// - Choosing to remove index `2` results in `nums = [6,1,4,1]`.
// - Choosing to remove index `4` results in `nums = [6,1,7,4]`.
//
// An array is **fair** if the sum of the odd-indexed values equals the sum of the even-indexed values.
//
// Return the **number** of indices that you could choose such that after the removal, `nums` is **fair**.
//
// **Example 1:**
//
// ```
// Input: nums = [2,1,6,4]
// Output: 1
// Explanation:
// Remove index 0: [1,6,4] -> Even sum: 1 + 4 = 5. Odd sum: 6. Not fair.
// Remove index 1: [2,6,4] -> Even sum: 2 + 4 = 6. Odd sum: 6. Fair.
// Remove index 2: [2,1,4] -> Even sum: 2 + 4 = 6. Odd sum: 1. Not fair.
// Remove index 3: [2,1,6] -> Even sum: 2 + 6 = 8. Odd sum: 1. Not fair.
// There is 1 index that you can remove to make nums fair.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,1,1]
// Output: 3
// Explanation:You can remove any index and the remaining array is fair.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [1,2,3]
// Output: 0
// Explanation:You cannot make a fair array after removing any index.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Prefix sum
//
// We first compute the prefix/suffix odd/even sum.
// Next loop for each element and check if its fair.
//
// Let pre[i] = i-1 + i-3 + ... (excluding)
// Let suf[i] = i   + i+2 + ... (including)
//
// Say we remove the i-th element.
// The odd and even sums are pre[i] + suf[i+2] and pre[i+1] + suf[i+3].
class Solution {
 public:
  int waysToMakeFair(vector<int>& nums) {
    int n = nums.size();
    auto prefixs = vector<int>(n + 1);
    auto suffixs = vector<int>(n + 1);

    // Prefix
    prefixs[0] = 0;
    prefixs[1] = nums[0];
    for (auto i = 2; i <= n; ++i) {
      prefixs[i] = prefixs[i - 2] + nums[i - 1];
    }

    // Suffix
    suffixs[n] = 0;
    suffixs[n - 1] = nums[n - 1];
    for (auto i = n - 2; i >= 0; --i) {
      suffixs[i] = suffixs[i + 2] + nums[i];
    }

    // Answer
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      auto left = ((i == 0) ? 0 : prefixs[i - 1]) + suffixs[i + 1];
      auto right = prefixs[i] + (i == n - 1 ? 0 : suffixs[i + 2]);
      if (left == right) ++ans;
    }
    return ans;
  }
};

// Let left[0]  and left[1]  be the even/odd elements before i.
// Let right[0] and right[1] be the even/odd elements after i.
//
// At first, right[0] = A[0] + A[2] + ..., right[1] = A[1] + A[3] + ...
//
// For each step,
// we remove A[i] from right[0] if i is even, from right[1] if i is odd;
// and insert A[i-1] to left[1] if i is even, to left[0] if i is odd.
// Next compare left[1]+right[0] and left[0]+right[1].
//
// Note that we don't need to insert for i = 0.
// Therefore, we can change the order of above algorithm:
// - remove A[i] from right[i%2];
// - compare left[1]+right[0] and left[0]+right[1];
// - insert A[i] to left[i%2].
class Solution2 {
 public:
  int waysToMakeFair(vector<int>& nums) {
    int n = nums.size();

    // Initialize
    int left[2] = {}, right[2] = {};
    for (auto i = 0; i < n; ++i) {
      right[i % 2] += nums[i];
    }

    // Loop
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      right[i % 2] -= nums[i];
      if (left[1] + right[0] == left[0] + right[1]) ++ans;
      left[i % 2] += nums[i];
    }

    return ans;
  }
};

// In solution2, we can define
// sum[0] = left[1]+right[0] and sum[1]=left[0]+right[1]
//
// Then the algorithm becomes:
// - remove A[i] from sum[i%2];
// - compare sum[0] and sum[1];
// - insert A[i] to sum[(i+1)%2].
class Solution3 {
 public:
  int waysToMakeFair(vector<int>& nums) {
    int n = nums.size();

    // Initialize
    auto even = 0, odd = 0;
    for (auto i = 0; i < n; ++i) {
      if (i % 2 == 0) {
        even += nums[i];
      } else {
        odd += nums[i];
      }
    }

    // Loop
    auto ans = 0;
    for (auto i = 0; i < n; ++i) {
      even -= nums[i];
      if (even == odd) ++ans;
      odd += nums[i];
      swap(even, odd);
    }

    return ans;
  }
};
