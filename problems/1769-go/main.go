// Source: https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box
// Title: Minimum Number of Operations to Move All Balls to Each Box
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have `n` boxes. You are given a binary string `boxes` of length `n`, where `boxes[i]` is `'0'` if the `i^th` box is **empty** , and `'1'` if it contains **one** ball.
//
// In one operation, you can move **one** ball from a box to an adjacent box. Box `i` is adjacent to box `j` if `abs(i - j) == 1`. Note that after doing so, there may be more than one ball in some boxes.
//
// Return an array `answer` of size `n`, where `answer[i]` is the **minimum** number of operations needed to move all the balls to the `i^th` box.
//
// Each `answer[i]` is calculated considering the **initial** state of the boxes.
//
// **Example 1:**
//
// ```
// Input: boxes = "110"
// Output: [1,1,3]
// Explanation: The answer for each box is as follows:
// 1) First box: you will have to move one ball from the second box to the first box in one operation.
// 2) Second box: you will have to move one ball from the first box to the second box in one operation.
// 3) Third box: you will have to move one ball from the first box to the third box in two operations, and move one ball from the second box to the third box in one operation.
// ```
//
// **Example 2:**
//
// ```
// Input: boxes = "001011"
// Output: [11,8,5,4,3,4]```
//
// **Constraints:**
//
// - `n == boxes.length`
// - `1 <= n <= 2000`
// - `boxes[i]` is either `'0'` or `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

// Time: O(n^2); Space: O(1)
func minOperations(boxes0 string) []int {
	n := len(boxes0)
	boxes := make([]int, n)
	for i, box := range boxes0 {
		boxes[i] = int(box - '0')
	}

	res := make([]int, n)
	for i, box := range boxes {
		for j := 0; j < n; j++ {
			res[j] += _abs(i-j) * box
		}
	}

	return res
}

func _abs(v int) int {
	if v >= 0 {
		return v
	}
	return -v
}

// Time: O(n); Space: O(n)
//
// Res(i)
// = Sum abs(i-j) * B(j)
// = Sum[j<i] (i-j) * B(j) + Sum[j>i] (j-i) * B(j)
// = Sum[j<i] (i-j) * B(j) - Sum[j>i] (i-j) * B(j)
// = 2 * Sum[j<i] (i-j) * B(j) - Sum (i-j) * B(j)
// = 2i * Sum[j<i] B(j) - 2 * Sum[j<i] j*B(j) - i * Sum B(j) + Sum j*B(j)
// We only need to precompute these sums
func minOperations2(boxes string) []int {
	n := len(boxes)
	presum1 := make([]int, n) // Sum[j<i] B(j)
	presum2 := make([]int, n) // Sum[j<i] j * B(j)

	sum1 := 0
	sum2 := 0
	for i := 0; i < n; i++ {
		if boxes[i] == '1' {
			sum1++
			sum2 += i
		}
		presum1[i] = sum1
		presum2[i] = sum2
	}

	res := make([]int, n)
	for i := 0; i < n; i++ {
		res[i] = 2*i*presum1[i] - 2*presum2[i] - i*presum1[n-1] + presum2[n-1]
	}

	return res
}

// Time: O(n); Space: O(1)
//
// Just move from left to right and right to left
func minOperations3(boxes string) []int {
	n := len(boxes)
	res := make([]int, n)

	{
		balls := 0
		moves := 0
		for i := 0; i < n; i++ {
			moves += balls
			res[i] += moves
			if boxes[i] == '1' {
				balls++
			}
		}
	}

	{
		balls := 0
		moves := 0
		for i := n - 1; i >= 0; i-- {
			moves += balls
			res[i] += moves
			if boxes[i] == '1' {
				balls++
			}
		}
	}

	return res
}

func main() {
	fmt.Println(minOperations3("110"))
}
