// Source: https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations
// Title: Count Non-Decreasing Subarrays After K Operations
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `nums` of `n` integers and an integer `k`.
//
// For each subarray of `nums`, you can apply **up to** `k` operations on it. In each operation, you increment any element of the subarray by 1.
//
// **Note** that each subarray is considered independently, meaning changes made to one subarray do not persist to another.
//
// Return the number of subarrays that you can make **non-decreasing** after performing at most `k` operations.
//
// An array is said to be **non-decreasing** if each element is greater than or equal to its previous element, if it exists.
//
// **Example 1:**
//
// ```
// Input: nums = [6,3,1,2,4,4], k = 7
// Output: 17
// Explanation:
// Out of all 21 possible subarrays of `nums`, only the subarrays `[6, 3, 1]`, `[6, 3, 1, 2]`, `[6, 3, 1, 2, 4]` and `[6, 3, 1, 2, 4, 4]` cannot be made non-decreasing after applying up to k = 7 operations. Thus, the number of non-decreasing subarrays is `21 - 4 = 17`.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [6,3,1,3,6], k = 4
// Output: 12
// Explanation:
// The subarray `[3, 1, 3, 6]` along with all subarrays of `nums` with three or fewer elements, except `[6, 3, 1]`, can be made non-decreasing after `k` operations. There are 5 subarrays of a single element, 4 subarrays of two elements, and 2 subarrays of three elements except `[6, 3, 1]`, so there are `1 + 5 + 4 + 2 = 12` subarrays that can be made non-decreasing.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 10^5`
// - `1 <= nums[i] <= 10^9`
// - `1 <= k <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <deque>
#include <vector>

using namespace std;

// Sliding Window
//
// We convert the problem into several subproblems.
//
// 1. Find minimal ops for a single array:
// We loop the numbers in the array from right to left.
// For each number x,
// increase all number smaller to the right until a number greater than x.
// To do so, we use a decreasing monotonic stack.
// The element in the stack contains two info: the `num` and `cnt`.
// The cnt means how many numbers are covered by this number.
// For each number x, we pop the smaller numbers (y_num, y_cnt) from the stack,
// and requires (x-y_num)*y_cnt ops.
// Next we put x into the stack with x_cnt be the sum of the pop cnt add 1.
//
// 2. Find all valid subarrays:
// We can simply loop for all possible subarrays, but it is too slow.
// We first observe that, if a subarray is valid, all subarray of it are also valid.
// Therefore, instead of looping all subarrays,
// we use sliding window to find the longest subarray for each ending index.
// Now the problem becomes how to compute the ops when window moves.
//
// 3. Maintain the ops when window moves:
// Adding number x from the left:
// Use the idea from subproblem 1.
//
// Removing number x from the right:
// Say x is covered by the number y >= x, we decrease y-x ops, and decrease y_cnt by 1.
// Note that y is the bottom item in the monotonic stack.
// (Therefore we should use deque instead.)
class Solution {
  struct Item {
    int num;
    int cnt;
  };

 public:
  long long countNonDecreasingSubarrays(const vector<int>& nums, int k) {
    const int n = nums.size();
    auto que = deque<Item>();

    // window: [l, r]
    long long ans = 0, ops = 0;
    int r = n - 1;
    for (int l = n - 1; l >= 0; --l) {
      // Adding x from left
      int x = nums[l];
      int cnt = 1;
      while (!que.empty() && que.back().num <= x) {
        ops += (long long)(x - que.back().num) * que.back().cnt;
        cnt += que.back().cnt;
        que.pop_back();
      }
      que.push_back({x, cnt});

      // Removing from the right
      while (ops > k) {
        ops -= (que.front().num - nums[r]);
        if (--que.front().cnt == 0) que.pop_front();
        --r;
      }

      ans += (r - l + 1);
    }

    return ans;
  }
};
