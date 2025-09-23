// Source: https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero
// Title: Minimum Operations to Make Array Elements Zero
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D array `queries`, where `queries[i]` is of the form `[l, r]`. Each `queries[i]` defines an array of integers `nums` consisting of elements ranging from `l` to `r`, both **inclusive**.
//
// In one operation, you can:
//
// - Select two integers `a` and `b` from the array.
// - Replace them with `floor(a / 4)` and `floor(b / 4)`.
//
// Your task is to determine the **minimum** number of operations required to reduce all elements of the array to zero for each query. Return the sum of the results for all queries.
//
// **Example 1:**
//
// ```
// Input: queries = [[1,2],[2,4]]
// Output: 3
// Explanation:
// For `queries[0]`:
// - The initial array is `nums = [1, 2]`.
// - In the first operation, select `nums[0]` and `nums[1]`. The array becomes `[0, 0]`.
// - The minimum number of operations required is 1.
// For `queries[1]`:
// - The initial array is `nums = [2, 3, 4]`.
// - In the first operation, select `nums[0]` and `nums[2]`. The array becomes `[0, 3, 1]`.
// - In the second operation, select `nums[1]` and `nums[2]`. The array becomes `[0, 0, 0]`.
// - The minimum number of operations required is 2.
// The output is `1 + 2 = 3`.
// ```
//
// **Example 2:**
//
// ```
// Input: queries = [[2,6]]
// Output: 4
// Explanation:
// For `queries[0]`:
// - The initial array is `nums = [2, 3, 4, 5, 6]`.
// - In the first operation, select `nums[0]` and `nums[3]`. The array becomes `[0, 3, 4, 1, 6]`.
// - In the second operation, select `nums[2]` and `nums[4]`. The array becomes `[0, 3, 1, 1, 1]`.
// - In the third operation, select `nums[1]` and `nums[2]`. The array becomes `[0, 0, 0, 1, 1]`.
// - In the fourth operation, select `nums[3]` and `nums[4]`. The array becomes `[0, 0, 0, 0, 0]`.
// - The minimum number of operations required is 4.
// The output is 4.
// ```
//
// **Constraints:**
//
// - `1 <= queries.length <= 10^5`
// - `queries[i].length == 2`
// - `queries[i] == [l, r]`
// - `1 <= l < r <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <cstdint>
#include <vector>

using namespace std;

// Use Math
//
// floor(a / 4) is exactly a >> 2.
//
// We first compute the S = Sum log4(x)+1 for x in [l, r].
// The number of operations requires is ceil(S/2).
// We need S operations to make all numbers to zero.
//
// Note that since l < r, we can easily accomplish if using ceil(S/2),
// since we can always start from the largest number and find another number to work with it.
//
// Denote S(l, r) = Sum log4(x)+1 for x in [l, r].
// S(0, 0) = 0.
// S(1, 3) = 1 * 3.
// S(4, 15) = 2 * 12.
// S(4^(k-1), 4^k-1) = k * (4^k - 4^(k-1)).
//
// S(0, 4^k-1) = sum_[i = 1 to k] i * (4^i - 4^(i-1))
//             = k * 4^k - k * 4^(k-1) + (k-1) * 4^(k-1) - ... - 1 * 4^0
//             = k * 4^k - 4^(k-1) - 4^(k-2) - ... - 4^0
//             = k * 4^k - (4^k - 1) / 3
//
// Say k = floor(log4(r+1))
// S(0, r) = S(0, 4^k-1) + S(4^k, r)
//         = S(0, 4^k-1) + (k+1) * (r-4^k+1)
//
// S(l, r) = S(0, r) - S(0, l-1)
class Solution {
 public:
  int64_t minOperations(vector<vector<int>>& queries) {
    int64_t ans = 0;
    for (auto& query : queries) {
      auto l = query[0], r = query[1];
      ans += (getOps(l, r) + 1) / 2;
    }
    return ans;
  }

  int64_t getOps(int64_t l, int64_t r) {  // 0 <= l <= r, 0 < r
    if (l != 0) {
      return getOps(0, r) - getOps(0, l - 1);
    }

    int64_t k = ilog4(r + 1);
    auto pow4k = 1ll << (2 * k);
    return (k + 1) * (r - pow4k + 1) + k * pow4k - (pow4k - 1) / 3;
  }

  inline int64_t ilog4(uint64_t x) {  // floor(log4(x))
    return (bit_width(x) - 1) / 2;
  }
};
