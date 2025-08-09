// Source: https://leetcode.com/problems/maximum-size-subarray-sum-equals-k
// Title: Maximum Size Subarray Sum Equals k
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums` and an integer `k`, return the maximum length of a <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:rs:" data-state="closed" class="">subarray</button> that sums to `k`. If there is not one, return `0` instead.
//
// **Example 1:**
//
// ```
// Input: nums = [1,-1,5,-2,3], k = 3
// Output: 4
// Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [-2,-1,2,1], k = 1
// Output: 2
// Explanation: The subarray [-1, 2] sums to 1 and is the longest.
// ```
//
// **Constraints:**
//
// - `1 <= nums.length <= 2 * 10^5`
// - `-10^4 <= nums[i] <= 10^4`
// - `-10^9<= k <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Prefix sum (TLE)
func maxSubArrayLen(nums []int, k int) int {
	n := len(nums)

	pre := make([]int, n+1)
	for i, num := range nums {
		pre[i+1] = pre[i] + num
	}

	for l := n; l >= 1; l-- { // loop through length
		for i := 0; i <= n-l; i++ {
			if pre[i+l]-pre[i] == k {
				return l
			}
		}
	}
	return 0
}

// Prefix sum + Hash table
func maxSubArrayLen2(nums []int, k int) int {
	n := len(nums)

	preMap := make(map[int]int, n) // map prefix sum to right most index
	{
		sum := 0
		for i, num := range nums {
			sum += num
			preMap[sum] = i + 1
		}
	}

	ans := 0
	{
		sum := 0
		for i, num := range nums {
			if j, ok := preMap[sum+k]; ok {
				ans = max(ans, j-i)
			}
			sum += num
		}
	}
	return ans
}
