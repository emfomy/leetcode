// Source: https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville
// Title: The Two Sneaky Numbers of Digitville
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In the town of Digitville, there was a list of numbers called `nums` containing integers from `0` to `n - 1`. Each number was supposed to appear **exactly once** in the list, however, **two** mischievous numbers sneaked in an additional time, making the list longer than usual.
//
// As the town detective, your task is to find these two sneaky numbers. Return an array of size **two** containing the two numbers (in any order), so peace can return to Digitville.
//
// **Example 1:**
//
// ```
// Input: nums = [0,1,1,0]
// Output: [0,1]
// Explanation:
// The numbers 0 and 1 each appear twice in the array.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [0,3,2,1,3,2]
// Output: [2,3]
// Explanation:
// The numbers 2 and 3 each appear twice in the array.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [7,1,5,4,3,4,6,0,9,5,8,2]
// Output: [4,5]
// Explanation:
// The numbers 4 and 5 each appear twice in the array.
// ```
//
// **Constraints:**
//
// * `2 <= n <= 100`
// * `nums.length == n + 2`
// * `0 <= nums[i] < n`
// * The input is generated such that `nums` contains **exactly** two repeated elements.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Hash Set
class Solution {
 public:
  vector<int> getSneakyNumbers(vector<int>& nums) {
    int n = nums.size() - 2;
    auto seen = vector<bool>(n);

    auto ans = vector<int>();
    for (auto num : nums) {
      if (seen[num]) ans.push_back(num);
      seen[num] = true;
    }

    return ans;
  }
};

// Math
//
// Say x, y are the duplicated numbers.
// 1   + 2   + ... + (n-1) = n(n-1)/2
// 1^2 + 2^2 + ... + (n-1)^2 = n(n-1)(2n-1)/2
// Use above sum to find x+y (=A) and x^2+y^2 (=B)
// => xy = (A^2-B)/2 = C => x^2 + xy = Ax
// => x^2 - Ax + C = 0 => A^2 - 4C = A^2 - 2A^2 + 2B = 2B - A^2
// => x = (A +- sqrt(2B - A^2))/2
class Solution2 {
 public:
  vector<int> getSneakyNumbers(vector<int>& nums) {
    int n = nums.size() - 2;
    auto sum1 = -n * (n - 1) / 2;
    auto sum2 = -n * (n - 1) * (n + n - 1) / 6;

    for (auto num : nums) {
      sum1 += num;
      sum2 += num * num;
    }

    auto delta = int(sqrt(2 * sum2 - sum1 * sum1));
    auto x = (sum1 + delta) / 2;
    auto y = (sum1 - delta) / 2;
    return {x, y};
  }
};
