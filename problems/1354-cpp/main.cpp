// Source: https://leetcode.com/problems/construct-target-array-with-multiple-sums
// Title: Construct Target Array With Multiple Sums
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `target` of n integers. From a starting array `arr` consisting of `n` 1's, you may perform the following procedure :
//
// - let `x` be the sum of all elements currently in your array.
// - choose index `i`, such that `0 <= i < n` and set the value of `arr` at index `i` to `x`.
// - You may repeat this procedure as many times as needed.
//
// Return `true` if it is possible to construct the `target` array from `arr`, otherwise, return `false`.
//
// **Example 1:**
//
// ```
// Input: target = [9,3,5]
// Output: true
// Explanation: Start with arr = [1, 1, 1]
// [1, 1, 1], sum = 3 choose index 1
// [1, 3, 1], sum = 5 choose index 2
// [1, 3, 5], sum = 9 choose index 0
// [9, 3, 5] Done
// ```
//
// **Example 2:**
//
// ```
// Input: target = [1,1,1,2]
// Output: false
// Explanation: Impossible to create target array from [1,1,1,1].
// ```
//
// **Example 3:**
//
// ```
// Input: target = [8,5]
// Output: true
// ```
//
// **Constraints:**
//
// - `n == target.length`
// - `1 <= n <= 5 * 10^4`
// - `1 <= target[i] <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// We may do the process backward.
// Start from arr = target.
// For each loop, choose the largest number.
// Substract the number by the sum of other numbers.
// Keep doing until the arr becomes all ones.
class Solution {
 public:
  bool isPossible(vector<int>& target) {
    auto sum = accumulate(target.cbegin(), target.cend(), 0LL);
    auto heap = priority_queue(less(), std::move(target));  // max-heap

    // Edge case, n = 1
    if (heap.size() == 1) return heap.top() == 1;

    // Loop
    while (heap.top() > 1) {
      auto num = heap.top();
      heap.pop();

      sum -= num;

      if (sum == 1) return true;  // Edge case, n = 2

      if (num <= sum) return false;
      num %= sum;

      if (num == 0) return false;
      sum += num;

      heap.push(num);
    }

    return true;
  }
};
