// Source: https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair
// Title: Maximize Subarrays After Removing One Conflicting Pair
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n` which represents an array `nums` containing the numbers from 1 to `n` in order. Additionally, you are given a 2D array `conflictingPairs`, where `conflictingPairs[i] = [a, b]` indicates that `a` and `b` form a conflicting pair.
//
// Remove **exactly** one element from `conflictingPairs`. Afterward, count the number of **non-empty subarrays** of `nums` which do not contain both `a` and `b` for any remaining conflicting pair `[a, b]`.
//
// A subarray is a contiguous **non-empty** sequence of elements within an array.
//
// Return the **maximum** number of subarrays possible after removing **exactly** one conflicting pair.
//
// **Example 1:**
//
// ```
// Input: n = 4, conflictingPairs = [[2,3],[1,4]]
// Output: 9
// Explanation:
// - Remove `[2, 3]` from `conflictingPairs`. Now, `conflictingPairs = [[1, 4]]`.
// - There are 9 subarrays in `nums` where `[1, 4]` do not appear together. They are `[1]`, `[2]`, `[3]`, `[4]`, `[1, 2]`, `[2, 3]`, `[3, 4]`, `[1, 2, 3]` and `[2, 3, 4]`.
// - The maximum number of subarrays we can achieve after removing one element from `conflictingPairs` is 9.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5, conflictingPairs = [[1,2],[2,5],[3,5]]
// Output: 12
// Explanation:
// - Remove `[1, 2]` from `conflictingPairs`. Now, `conflictingPairs = [[2, 5], [3, 5]]`.
// - There are 12 subarrays in `nums` where `[2, 5]` and `[3, 5]` do not appear together.
// - The maximum number of subarrays we can achieve after removing one element from `conflictingPairs` is 12.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^5`
// - `1 <= conflictingPairs.length <= 2 * n`
// - `conflictingPairs[i].length == 2`
// - `1 <= conflictingPairs[i][j] <= n`
// - `conflictingPairs[i][0] != conflictingPairs[i][1]`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

// Use DP
//
// We first simplify the problem by get rit of the removing process.
//
// Define F[i] = q if [i, q] is the longest valid subarray starting from i.
// The total number of subarrays is equal to sum_i (i - F[i] + 1).
//
// In order to find F, we define
// B1[i] be the right closest conflicting index for index i.
// B2[i] be the right 2nd-closest conflicting index for index i.
// Note that we will use B2 is the closest pair is removed.
//
// Now if we doesn't remove any pair, the sum will be sum_i ()
func maxSubarrays(n int, conflictingPairs [][]int) int64 {
	start1s := make([]int, n+1) // largest pair end at i
	start2s := make([]int, n+1) // 2nd-largest pair end at i
	for _, pair := range conflictingPairs {
		p := min(pair[0], pair[1])
		q := max(pair[0], pair[1])
		if p > start1s[q] {
			start2s[q] = start1s[q]
			start1s[q] = p
		} else if p > start2s[q] {
			start2s[q] = p
		}
	}

	ans := int64(0)
	for k := 1; k <= n; k++ { // remove pair end at k
		if start1s[k] == start2s[k] {
			continue
		}
		subans := int64(0)
		dp := 0
		for i := 1; i <= n; i++ {
			if i != k {
				dp = max(dp, start1s[i]+1)
			} else {
				dp = max(dp, start2s[i]+1)
			}
			subans += int64(i - dp + 1)
		}
		ans = max(ans, subans)
	}

	return ans
}

func main() {
	fmt.Println(maxSubarrays(
		// 4, [][]int{{2, 3}, {1, 4}},
		// 5, [][]int{{1, 2}, {2, 5}, {3, 5}},

		// 4, [][]int{{1, 4}},
		// 5, [][]int{{2, 5}, {3, 5}},

		5, [][]int{{1, 2}, {2, 5}, {3, 5}},
	))
}
