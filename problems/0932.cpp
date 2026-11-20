// Source: https://leetcode.com/problems/beautiful-array
// Title: Beautiful Array
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An array `nums` of length `n` is **beautiful** if:
//
// - `nums` is a permutation of the integers in the range `[1, n]`.
// - For every `0 <= i < j < n`, there is no index `k` with `i < k < j` where `2 * nums[k] == nums[i] + nums[j]`.
//
// Given the integer `n`, return any **beautiful** array `nums` of length `n`. There will be at least one valid answer for the given `n`.
//
// **Example 1:**
//
// ```
// Input: n = 4
// Output: [2,1,4,3]
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5
// Output: [3,1,2,5,4]
// ```
//
// **Constraints:**
//
// - `1 <= n <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Divide and Conquer
//
// We try to split [1, n] into odd and even numbers.
// Say A are the even numbers and B are the odd numbers,
// We pick nums[i] in A and nums[j] in B, then nums[i]+nums[j] is odd.
// Therefore we know that any pair between A and B is valid.
// Now focus on the pairs within in A and B.
//
// If we add or multiply a fixed number to all numbers in the array,
// it won't break the beautifulness.
// Say we have a+b=2c, then (a+k)+(b+k)=2(c+k) and ka+kb+k=2kc.
//
// Using above two property, we can divide the even numbers by two.
// Similarly, we can add one the the odd numbers and then divide them by two.
// Now we only need to handle n/2 (or n/2+1).
//
// Let N(n) be the beautiful array of length n.
// Denote N(n) = A(n) + B(n) as evens and odds.
// A(n) = N(floor(n/2)) * 2
// B(n) = N(ceil(n/2)) * 2 - 1
// N(1) = [1]
class Solution {
 public:
  vector<int> beautifulArray(int n) {
    auto nums = vector<int>(n);
    generate(nums, n, 0, 1, 0);
    return nums;
  }

  void generate(vector<int> &nums, int n, int start, int multiply, int minus) {
    if (n == 1) {  // [1]
      nums[start] = 1 * multiply - minus;
      return;
    }

    auto even = n / 2;
    auto odd = n - even;
    generate(nums, even, start, multiply * 2, minus);                   // (*2)*k-l = *2k-l
    generate(nums, odd, start + even, multiply * 2, multiply + minus);  // (*2-1)*k-l = *2k-k-l
  }
};
