// Source: https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence
// Title: Can Make Arithmetic Progression From Sequence
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A sequence of numbers is called an **arithmetic progression** if the difference between any two consecutive elements is the same.
//
// Given an array of numbers `arr`, return `true` if the array can be rearranged to form an **arithmetic progression**. Otherwise, return `false`.
//
// **Example 1:**
//
// ```
// Input: arr = [3,5,1]
// Output: true
// Explanation: We can reorder the elements as [1,3,5] or [5,3,1] with differences 2 and -2 respectively, between each consecutive elements.
// ```
//
// **Example 2:**
//
// ```
// Input: arr = [1,2,4]
// Output: false
// Explanation: There is no way to reorder the elements to obtain an arithmetic progression.
// ```
//
// **Constraints:**
//
// - `2 <= arr.length <= 1000`
// - `-10^6 <= arr[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Sort
class Solution {
 public:
  bool canMakeArithmeticProgression(vector<int>& arr) {
    // Trivial
    const int n = arr.size();
    if (n <= 2) return true;

    // Sort
    sort(arr.begin(), arr.end());

    // Check
    const int diff = arr[1] - arr[0];
    for (int i = 2; i < n; ++i) {
      if (arr[i] - arr[i - 1] != diff) return false;
    }
    return true;
  }
};

// Array
//
// Find the maximum and the minimum number.
// The difference is equal to (max-min)/(n-1).
// Use an array of boolean to check if every term exists.
class Solution2 {
  using Bool = unsigned char;

 public:
  bool canMakeArithmeticProgression(const vector<int>& arr) {
    // Trivial
    const int n = arr.size();
    if (n <= 2) return true;

    // Count
    const auto [minIt, maxIt] = minmax_element(arr.cbegin(), arr.cend());
    const int minVal = *minIt, maxVal = *maxIt;
    const int range = maxVal - minVal;
    if (range == 0) return true;             // all equal
    if (range % (n - 1) != 0) return false;  // difference not integer
    const int diff = range / (n - 1);

    // Check
    auto seen = vector<Bool>(n);
    for (const auto num : arr) {
      const int d = num - minVal;
      if (d % diff != 0) return false;  // invalid number
      const int idx = d / diff;
      if (seen[idx]) return false;  // duplicated number
      seen[idx] = true;
    }

    return true;
  }
};

// Swap Sort
//
// Find the maximum and the minimum number.
// The difference is equal to (max-min)/(n-1).
// Assume that the array can be rearranged to arithmetic series.
// For each number in the array, we can compute its index in the sorted array.
//
// We start from the first slot and swap the number to its destination.
// Keep swapping until the current number is already at currect position.
// Next move on to the number slot until the array is sorted.
//
// This sort only cost O(n) since each swap will eliminate one unsorted number.
class Solution3 {
  using Bool = unsigned char;

 public:
  bool canMakeArithmeticProgression(vector<int>& arr) {
    // Trivial
    const int n = arr.size();
    if (n <= 2) return true;

    // Count
    const auto [minIt, maxIt] = minmax_element(arr.cbegin(), arr.cend());
    const int minVal = *minIt, maxVal = *maxIt;
    const int range = maxVal - minVal;
    if (range == 0) return true;             // all equal
    if (range % (n - 1) != 0) return false;  // difference not integer
    const int diff = range / (n - 1);

    // Sort
    for (int i = 0; i < n; ++i) {
      while (arr[i] != minVal + i * diff) {
        const int d = arr[i] - minVal;
        if (d % diff != 0) return false;  // invalid number
        const int dst = d / diff;
        if (arr[i] == arr[dst]) return false;  // duplicated number
        swap(arr[i], arr[dst]);
      }
    }

    return true;
  }
};
