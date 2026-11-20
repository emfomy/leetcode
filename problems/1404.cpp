// Source: https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one
// Title: Number of Steps to Reduce a Number in Binary Representation to One
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the binary representation of an integer as a string `s`, return the number of steps to reduce it to `1` under the following rules:
//
// - If the current number is even, you have to divide it by `2`.
// - If the current number is odd, you have to add `1` to it.
//
// It is guaranteed that you can always reach one for all test cases.
//
// **Example 1:**
//
// ```
// Input: s = "1101"
// Output: 6
// Explanation: "1101" corressponds to number 13 in their decimal representation.
// Step 1) 13 is odd, add 1 and obtain 14.
// Step 2) 14 is even, divide by 2 and obtain 7.
// Step 3) 7 is odd, add 1 and obtain 8.
// Step 4) 8 is even, divide by 2 and obtain 4.
// Step 5) 4 is even, divide by 2 and obtain 2.
// Step 6) 2 is even, divide by 2 and obtain 1.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "10"
// Output: 1
// Explanation: "10" corresponds to number 2 in their decimal representation.
// Step 1) 2 is even, divide by 2 and obtain 1.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "1"
// Output: 0
// ```
//
// **Constraints:**
//
// - `1 <= s.length<= 500`
// - `s` consists of characters '0' or '1'
// - `s[0] == '1'`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// Simulation
//
// Just like bit addition
class Solution {
 public:
  int numSteps(const string &s) {
    const int n = s.size();

    // Check all bits except the highset one
    int ans = 0;
    int carry = 0;
    for (int i = n - 1; i >= 1; --i) {
      carry += (s[i] & 1);
      if (carry & 1) {
        ans += 2;  // odd-op & even-op
        ++carry;
      } else {
        ans += 1;  // even-op
      }
      carry /= 2;
    }

    // Highest bit
    carry += (s[0] & 1);
    if (carry == 2) ans += 1;

    return ans;
  }
};

// Simulation
//
// We define a variable `carry` (same as bit addition).
//
// That there are total 4 cases in the loop:
// digit=0, carry=0 => sum=0  => even-op          => new_sum = 0  (new_carry = 0);
// digit=0, carry=1 => sum=1  => even-op & odd-op => new_sum = 10 (new_carry = 1);
// digit=1, carry=0 => sum=1  => even-op & odd-op => new_sum = 10 (new_carry = 1);
// digit=1, carry=1 => sum=10 => even-op          => new_sum = 10 (new_carry = 1).
//
// We conclude that:
// if sum is even, then apply even operation, and keep the carry value);
// if sum is odd, then apply both operations, and set carry = 1.
//
// Note that the highest digit is different. The digit could not be 0.
// carry=0 => sum=1  => no ops;
// carry=1 => sum=10 => even-op.
//
// Note that there is at least one operation for each step (except the highest digit),
// we can update the algorithm as follow:
// Initallsize carry=0 and ops=len(s)-1.
// For normal bits, if sum=1, then set ops++ and carry=1.
// For highest bits, if carry=1, then ops++ (i.e. ops += carry).
class Solution2 {
 public:
  int numSteps(const string &s) {
    const int n = s.size();

    // Normal digits
    int ops = n - 1;
    int carry = 0;
    for (int i = n - 1; i > 0; --i) {
      if (int digit = carry + (s[i] & 1); digit & 1) {
        ++ops;
        carry = 1;
      }
    }

    // Highest digit
    ops += carry;

    return ops;
  }
};
