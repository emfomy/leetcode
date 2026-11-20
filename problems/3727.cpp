// Source: https://leetcode.com/problems/maximum-alternating-sum-of-squares
// Title: Maximum Alternating Sum of Squares
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array `nums`. You may **rearrange the elements** in any order.

// The **alternating score** of an array `arr` is defined as:

// - `score = arr[0]^2 - arr[1]^2 + arr[2]^2 - arr[3]^2 + ...`

// Return an integer denoting the **maximum possible alternating score** of `nums` after rearranging its elements.

// **Example 1:**

// ```
// Input: nums = [1,2,3]
// Output: 12
// Explanation:
// A possible rearrangement for `nums` is `[2,1,3]`, which gives the maximum alternating score among all possible rearrangements.
// The alternating score is calculated as:
// `score = 2^2 - 1^2 + 3^2 = 4 - 1 + 9 = 12`
// ```

// **Example 2:**

// ```
// Input: nums = [1,-1,2,-2,3,-3]
// Output: 16
// Explanation:
// A possible rearrangement for `nums` is `[-3,-1,-2,1,3,2]`, which gives the maximum alternating score among all possible rearrangements.
// The alternating score is calculated as:
// `score = (-3)^2 - (-1)^2 + (-2)^2 - (1)^2 + (3)^2 - (2)^2 = 9 - 1 + 4 - 1 + 9 - 4 = 16`
// ```

// **Constraints:**

// - `1 <= nums.length <= 10^5`
// - `-4 * 10^4 <= nums[i] <= 4 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// Sort
class Solution {
 public:
  long long maxAlternatingSum(vector<int>& nums) {
    const int n = nums.size();

    // Square
    for (int& num : nums) num *= num;

    // Sort
    sort(nums.begin(), nums.end());

    // Sum
    auto mid = nums.cbegin() + n / 2;
    return accumulate(mid, nums.cend(), 0LL) - accumulate(nums.cbegin(), mid, 0LL);
  }
};

// Sort
class Solution2 {
 public:
  long long maxAlternatingSum(vector<int>& nums) {
    const int n = nums.size();

    // Abs
    for (int& num : nums) num = abs(num);

    // Sort
    sort(nums.begin(), nums.end());

    // Sum
    long long sum = 0;
    for (int i = 0; i < n / 2; ++i) sum -= nums[i] * nums[i];
    for (int i = n / 2; i < n; ++i) sum += nums[i] * nums[i];

    return sum;
  }
};

// Sort
//
// We only need to sort half.
class Solution3 {
 public:
  long long maxAlternatingSum(vector<int>& nums) {
    const int n = nums.size();

    // Abs
    for (int& num : nums) num = abs(num);

    // Sort
    nth_element(nums.begin(), nums.begin() + n / 2, nums.end());

    // Sum
    long long sum = 0;
    for (int i = 0; i < n / 2; ++i) sum -= nums[i] * nums[i];
    for (int i = n / 2; i < n; ++i) sum += nums[i] * nums[i];

    return sum;
  }
};
