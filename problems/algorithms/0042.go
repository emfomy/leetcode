//  Source: https://leetcode.com/problems/trapping-rain-water/
//  Title: Trapping Rain Water
//  Difficulty: Hard
//  Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
//
//  Example 1:
//
//    https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png
//    Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
//    Output: 6
//    Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
//
//  Example 2:
//
//    Input: height = [4,2,0,3,2,5]
//    Output: 9
//
// Constraints:
//
//   n == height.length
//   1 <= n <= 2 * 10^4
//   0 <= height[i] <= 10^5
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use two pointers
func trap(height []int) int {
	n := len(height)
	if n == 1 {
		return 0
	}

	i := 0     // left index
	j := n - 1 // right index

	res := 0
	waterLevel := 0

	for i < j {
		var currVal int
		if height[i] <= height[j] {
			currVal = height[i]
			i++
		} else {
			currVal = height[j]
			j--
		}

		if currVal > waterLevel {
			waterLevel = currVal
		} else {
			res += waterLevel - currVal
		}
	}

	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use two arrays
func trap2(height []int) int {
	n := len(height)
	if n == 1 {
		return 0
	}

	leftLevel := make([]int, n)
	rightLevel := make([]int, n)

	currMax := 0
	for i := 0; i < n; i++ {
		currMax = _max(currMax, height[i])
		leftLevel[i] = currMax
	}

	currMax = 0
	for i := n - 1; i >= 0; i-- {
		currMax = _max(currMax, height[i])
		rightLevel[i] = currMax
	}

	res := 0
	for i := 0; i < n; i++ {
		res += _min(leftLevel[i], rightLevel[i]) - height[i]
	}

	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
