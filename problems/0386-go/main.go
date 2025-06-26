// Source: https://leetcode.com/problems/lexicographical-numbers
// Title: Lexicographical Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, return all the numbers in the range `[1, n]` sorted in lexicographical order.
//
// You must write an algorithm that runs in`O(n)`time and uses `O(1)` extra space.
//
// **Example 1:**
//
// ```
// Input: n = 13
// Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
// ```
//
// **Example 2:**
//
// ```
// Input: n = 2
// Output: [1,2]
// ```
//
// **Constraints:**
//
// - `1 <= n <= 5 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Construct
func lexicalOrder(n int) []int {
	ans := make([]int, 0, n)

	for i1 := 1; i1 < 10; i1++ {
		num := i1
		if num > n {
			break
		}
		ans = append(ans, num)
		for i2 := range 10 {
			num2 := num*10 + i2
			if num2 > n {
				break
			}
			ans = append(ans, num2)
			for i3 := range 10 {
				num3 := num2*10 + i3
				if num3 > n {
					break
				}
				ans = append(ans, num3)
				for i4 := range 10 {
					num4 := num3*10 + i4
					if num4 > n {
						break
					}
					ans = append(ans, num4)
					for i5 := range 10 {
						num5 := num4*10 + i5
						if num5 > n {
							break
						}
						ans = append(ans, num5)
					}
				}
			}
		}
	}

	return ans
}
