// Source: https://leetcode.com/problems/trapping-rain-water
// Title: Trapping Rain Water
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png
//
// ```
// Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
// Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
// ```
//
// **Example 2:**
//
// ```
// Input: height = [4,2,0,3,2,5]
// Output: 9
// ```
//
// **Constraints:**
//
// - `n == height.length`
// - `1 <= n <= 2 * 10^4`
// - `0 <= height[i] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"slices"
)

// First, move from left to right until the highest point
// Next, do this in reserve direction.
func trap(height []int) int {
	n := len(height)

	res := 0

	// Left to right
	// Here we use `val >= maxVal` since there might be multiple highest points
	{
		maxVal, water := 0, 0
		for idx := 0; idx < n; idx++ {
			val := height[idx]
			if val >= maxVal {
				res += water
				maxVal, water = val, 0
			} else {
				water += maxVal - val
			}
		}
	}

	// Right to left
	// Here we use `val > maxVal` since the `=` case is handled in previous loop
	{
		maxVal, water := 0, 0
		for idx := n - 1; idx >= 0; idx-- {
			val := height[idx]
			if val > maxVal {
				res += water
				maxVal, water = val, 0
			} else {
				water += maxVal - val
			}
		}
	}

	return res
}

// Two pointers
func trap2(height []int) int {
	n := len(height)

	res := 0
	left, right := 0, n-1
	leftMax, rightMax := 0, 0

	for left < right {
		if height[left] < height[right] {
			if height[left] >= leftMax {
				leftMax = height[left]
			} else {
				res += leftMax - height[left]
			}
			left++
		} else {
			if height[right] >= rightMax {
				rightMax = height[right]
			} else {
				res += rightMax - height[right]
			}
			right--
		}
	}

	return res
}

// Use array
func trap3(height []int) int {
	n := len(height)

	// Find heightest point
	maxVal := slices.Max(height)

	// Fill water with max val
	water := make([]int, n)
	for i := range n {
		water[i] = maxVal
	}

	// Flow out water from left
	water[0] = height[0]
	for i := 1; i < n; i++ {
		if water[i] > water[i-1] {
			water[i] = max(water[i-1], height[i])
		}
	}

	// Flow out water from right
	water[n-1] = height[n-1]
	for i := n - 2; i >= 0; i-- {
		if water[i] > water[i+1] {
			water[i] = max(water[i+1], height[i])
		}
	}

	// Count water
	res := 0
	for i := range n {
		res += water[i] - height[i]
	}

	return res
}
