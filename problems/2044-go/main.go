// Source: https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets
// Title: Count Number of Maximum Bitwise-OR Subsets
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer array `nums`, find the **maximum** possible **bitwise OR** of a subset of `nums` and return the **number of different non-empty subsets** with the maximum bitwise OR.
//
// An array `a` is a **subset** of an array `b` if `a` can be obtained from `b` by deleting some (possibly zero) elements of `b`. Two subsets are considered **different** if the indices of the elements chosen are different.
//
// The bitwise OR of an array `a` is equal to `a[0] **OR** a[1] **OR** ... **OR** a[a.length - 1]` (**0-indexed**).
//
// **Example 1:**
//
// ```
// Input: nums = [3,1]
// Output: 2
// Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
// - [3]
// - [3,1]
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [2,2,2]
// Output: 7
// Explanation: All non-empty subsets of [2,2,2] have a bitwise OR of 2. There are 2^3 - 1 = 7 total subsets.
// ```
//
// **Example 3:**
//
// ```
// Input: nums = [3,2,1,5]
// Output: 6
// Explanation: The maximum possible bitwise OR of a subset is 7. There are 6 subsets with a bitwise OR of 7:
// - [3,5]
// - [3,1,5]
// - [3,2,5]
// - [3,2,1,5]
// - [2,5]
// - [2,1,5]```
//
// **Constraints:**
//
// - `1 <= nums.length <= 16`
// - `1 <= nums[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Brute-Force
func countMaxOrSubsets(nums []int) int {
	n := len(nums)
	m := 1 << n

	counter := make(map[int]int)

	maxVal := 0
	for b := range m {
		val := 0
		for i, num := range nums {
			if b&(1<<i) > 0 {
				val |= num
			}
		}
		counter[val]++
		maxVal = max(maxVal, val)
	}

	return counter[maxVal]
}

// Brute-Force
func countMaxOrSubsets2(nums []int) int {
	n := len(nums)
	m := 1 << n

	maxVal := 0
	for _, num := range nums {
		maxVal |= num
	}

	ans := 0
	for b := range m {
		val := 0
		for i, num := range nums {
			if b&(1<<i) > 0 {
				val |= num
			}
		}
		if val == maxVal {
			ans++
		}
	}

	return ans
}

// DFS
//
// Use DFS to loop through all subset.
func countMaxOrSubsets3(nums []int) int {
	n := len(nums)

	maxVal := 0
	for _, num := range nums {
		maxVal |= num
	}

	var dfs func(i, val int) int
	dfs = func(i, val int) int {
		if val == maxVal {
			return 1 << (n - i)
		}
		if i == n {
			return 0
		}

		return dfs(i+1, val) + dfs(i+1, val|nums[i])
	}

	return dfs(0, 0)
}

// DFS + DP
//
// Use DFS to loop through all subset.
// Use DP to cache result.
//
// Define DP(i, v) be the number of max subsets,
// where the bit-OR of nums[0:i] is v.
func countMaxOrSubsets4(nums []int) int {
	n := len(nums)

	maxVal := 0
	for _, num := range nums {
		maxVal |= num
	}

	dp := make(map[[2]int]int)
	for i := range n {
		dp[[2]int{i, maxVal}] = 1 << (n - i)
	}

	var dfs func(i, val int) int
	dfs = func(i, val int) int {
		if i == n {
			if val == maxVal {
				return 1
			}
			return 0
		}

		key := [2]int{i, val}
		if dp[key] != 0 {
			return dp[key]
		}

		count := dfs(i+1, val) + dfs(i+1, val|nums[i])
		dp[key] = count
		return count
	}

	return dfs(0, 0)
}
