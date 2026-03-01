// Source: https://leetcode.com/problems/add-to-array-form-of-integer
// Title: Add to Array-Form of Integer
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The **array-form** of an integer `num` is an array representing its digits in left to right order.
//
// - For example, for `num = 1321`, the array form is `[1,3,2,1]`.
//
// Given `num`, the **array-form** of an integer, and an integer `k`, return the **array-form** of the integer `num + k`.
//
// **Example 1:**
//
// ```
// Input: num = [1,2,0,0], k = 34
// Output: [1,2,3,4]
// Explanation: 1200 + 34 = 1234
// ```
//
// **Example 2:**
//
// ```
// Input: num = [2,7,4], k = 181
// Output: [4,5,5]
// Explanation: 274 + 181 = 455
// ```
//
// **Example 3:**
//
// ```
// Input: num = [2,1,5], k = 806
// Output: [1,0,2,1]
// Explanation: 215 + 806 = 1021
// ```
//
// **Constraints:**
//
// - `1 <= num.length <= 10^4`
// - `0 <= num[i] <= 9`
// - `num` does not contain any leading zeros except for the zero itself.
// - `1 <= k <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Do addition from low-digit to high-digit.
// We put the result in right to left order since there might be carrying.
// We reverse the result at the end.
class Solution {
 public:
  vector<int> addToArrayForm(const vector<int>& num, int k) {
    const int n = num.size();

    auto result = vector<int>();
    result.reserve(n);

    // Addition
    int i = n - 1;  // index for num
    int carry = 0;
    while (i >= 0 || k > 0) {
      // Get digit
      int numDigit = (i >= 0) ? num[i] : 0;
      int kDigit = k % 10;
      int resDigit = numDigit + kDigit + carry;

      result.push_back(resDigit % 10);
      carry = resDigit / 10;

      // Next iteration
      --i;
      k /= 10;
    }

    // Handle last carry
    if (carry) {
      result.push_back(carry);
    }

    // Reverse result
    reverse(result.begin(), result.end());

    return result;
  }
};

// Do addition from low-digit to high-digit.
// We put the result in right to left order since there might be carrying.
// We reverse the result at the end.
//
// We can use k for carrying.
class Solution2 {
 public:
  vector<int> addToArrayForm(const vector<int>& num, const int k) {
    const int n = num.size();

    auto result = vector<int>();
    result.reserve(max(n, 5) + 1);

    // Addition
    int i = n - 1;  // index for num
    int curr = k;
    while (i >= 0 || curr > 0) {
      // Add current digit
      curr += (i >= 0) ? num[i] : 0;

      // Push digit into result
      result.push_back(curr % 10);

      // Next iteration
      --i;
      curr /= 10;
    }

    // Reverse result
    reverse(result.begin(), result.end());

    return result;
  }
};
