// Source: https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together
// Title: Minimum Swaps to Group All 1's Together
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given abinary array `data`, return the minimum number of swaps required to group all `1`’s present in the array together in **any place** in the array.
//
// **Example 1:**
//
// ```
// Input: data = [1,0,1,0,1]
// Output: 1
// Explanation: There are 3 ways to group all 1's together:
// [1,1,1,0,0] using 1 swap.
// [0,1,1,1,0] using 2 swaps.
// [0,0,1,1,1] using 1 swap.
// The minimum is 1.
// ```
//
// **Example 2:**
//
// ```
// Input: data = [0,0,0,1,0]
// Output: 0
// Explanation: Since there is only one 1 in the array, no swaps are needed.
// ```
//
// **Example 3:**
//
// ```
// Input: data = [1,0,1,0,1,0,0,1,1,0,1]
// Output: 3
// Explanation: One possible solution that uses 3 swaps is [0,0,0,0,0,1,1,1,1,1,1].
// ```
//
// **Constraints:**
//
// - `1 <= data.length <= 10^5`
// - `data[i]` is either `0` or `1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <numeric>
#include <vector>

using namespace std;

// Sliding window
//
// First count the number of ones (say there are k ones).
// Using sliding window with size k ans count zeros (i.e. number of swaps).
class Solution {
 public:
  int minSwaps(vector<int>& data) {
    int n = data.size();

    auto k = accumulate(data.cbegin(), data.cend(), 0);
    if (k == 0) return 0;

    auto ans = n;
    auto swaps = 0;
    for (auto i = 0; i < n; ++i) {
      swaps += (data[i] == 0);
      if (i + 1 >= k) {
        ans = min(ans, swaps);
        swaps -= (data[i - k + 1] == 0);
      }
    }

    return ans;
  }
};
