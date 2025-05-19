// Source: https://leetcode.com/problems/total-characters-in-string-after-transformations-ii
// Title: Total Characters in String After Transformations II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` consisting of lowercase English letters, an integer `t` representing the number of **transformations** to perform, and an array `nums` of size 26. In one **transformation**, every character in `s` is replaced according to the following rules:
//
// - Replace `s[i]` with the **next** `nums[s[i] - 'a']` consecutive characters in the alphabet. For example, if `s[i] = 'a'` and `nums[0] = 3`, the character `'a'` transforms into the next 3 consecutive characters ahead of it, which results in `"bcd"`.
// - The transformation **wraps** around the alphabet if it exceeds `'z'`. For example, if `s[i] = 'y'` and `nums[24] = 3`, the character `'y'` transforms into the next 3 consecutive characters ahead of it, which results in `"zab"`.
//
// Return the length of the resulting string after **exactly** `t` transformations.
//
// Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
// Output: 7
// Explanation:
// - **First Transformation (t = 1):**
//   - `'a'` becomes `'b'` as `nums[0] == 1`
//   - `'b'` becomes `'c'` as `nums[1] == 1`
//   - `'c'` becomes `'d'` as `nums[2] == 1`
//   - `'y'` becomes `'z'` as `nums[24] == 1`
//   - `'y'` becomes `'z'` as `nums[24] == 1`
//   - String after the first transformation: `"bcdzz"`
// - **Second Transformation (t = 2):**
//   - `'b'` becomes `'c'` as `nums[1] == 1`
//   - `'c'` becomes `'d'` as `nums[2] == 1`
//   - `'d'` becomes `'e'` as `nums[3] == 1`
//   - `'z'` becomes `'ab'` as `nums[25] == 2`
//   - `'z'` becomes `'ab'` as `nums[25] == 2`
//   - String after the second transformation: `"cdeabab"`
// - **Final Length of the string:** The string is `"cdeabab"`, which has 7 characters.
//
// **Example 2:**
//
// ```
// Input: s = "azbk", t = 1, nums = [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
// Output: 8
// Explanation:
// - **First Transformation (t = 1):**
//   - `'a'` becomes `'bc'` as `nums[0] == 2`
//   - `'z'` becomes `'ab'` as `nums[25] == 2`
//   - `'b'` becomes `'cd'` as `nums[1] == 2`
//   - `'k'` becomes `'lm'` as `nums[10] == 2`
//   - String after the first transformation: `"bcabcdlm"`
// - **Final Length of the string:** The string is `"bcabcdlm"`, which has 8 characters.
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` consists only of lowercase English letters.
// - `1 <= t <= 10^9`
// - `nums.length == 26`
// - `1 <= nums[i] <= 25`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)

// TLE
func lengthAfterTransformations(s string, t int, nums []int) int {
	curr := [26]int{}
	next := [26]int{}
	for _, ch := range s {
		curr[ch-'a']++
	}

	for range t {
		for i := range 26 {
			next[i] = 0
		}
		for i, num := range nums {
			for j := range num {
				next[(i+j+1)%26] += curr[i]
				next[(i+j+1)%26] %= modulo
			}
		}
		curr, next = next, curr
	}

	ans := 0
	for _, count := range curr {
		ans += count
		ans %= modulo
	}

	return ans
}

// Markov chain, TLE
func lengthAfterTransformations2(s string, t int, nums []int) int {
	curr := [26]int{}
	for _, ch := range s {
		curr[ch-'a']++
	}

	matrix := [26][26]int{}
	for i, num := range nums {
		for j := range num {
			matrix[(i+j+1)%26][i] = 1
		}
	}

	next := [26]int{}
	for range t {
		for i, row := range matrix {
			next[i] = 0
			for j, val := range row {
				next[i] += curr[j] * val
				next[i] %= modulo
			}
		}
		curr, next = next, curr
	}

	ans := 0
	for _, count := range curr {
		ans += count
		ans %= modulo
	}

	return ans
}

// Markov chain, compute matrix power
func lengthAfterTransformations3(s string, t int, nums []int) int {
	vector := [26]int{}
	for _, ch := range s {
		vector[ch-'a']++
	}

	// Markov matrix
	matrix := [26][26]int{}
	for i, num := range nums {
		for j := range num {
			matrix[(i+j+1)%26][i] = 1
		}
	}

	// Operators
	gemm := func(a, b, c *[26][26]int) { // c = a * b
		for i := range 26 {
			for j := range 26 {
				c[i][j] = 0
				for k := range 26 {
					c[i][j] += a[i][k] * b[k][j]
					c[i][j] %= modulo
				}
			}
		}
	}
	gemm2 := func(a, c *[26][26]int) { // c = a * a
		for i := range 26 {
			for j := range 26 {
				c[i][j] = 0
				for k := range 26 {
					c[i][j] += a[i][k] * a[k][j]
					c[i][j] %= modulo
				}
			}
		}
	}

	// Fast matrix power
	result := [26][26]int{}
	temp := [26][26]int{}
	for i := range 26 {
		result[i][i] = 1
	}
	for true {
		if (t & 1) != 0 {
			gemm(&matrix, &result, &temp) // result *= matrix
			result, temp = temp, result
		}
		t >>= 1
		if t == 0 {
			break
		}
		gemm2(&matrix, &temp) // matrix *= matrix
		matrix, temp = temp, matrix
	}

	// Compute matrix vector multiplication
	ans := 0
	for _, row := range result {
		for j, v := range row {
			ans += v * vector[j]
			ans %= modulo
		}
	}

	return ans
}
