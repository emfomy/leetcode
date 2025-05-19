// Source: https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid
// Title: Check if a Parentheses String Can Be Valid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A parentheses string is a **non-empty** string consisting only of `'('` and `')'`. It is valid if **any** of the following conditions is **true** :
//
// - It is `()`.
// - It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are valid parentheses strings.
// - It can be written as `(A)`, where `A` is a valid parentheses string.
//
// You are given a parentheses string `s` and a string `locked`, both of length `n`. `locked` is a binary string consisting only of `'0'`s and `'1'`s. For **each** index `i` of `locked`,
//
// - If `locked[i]` is `'1'`, you **cannot** change `s[i]`.
// - But if `locked[i]` is `'0'`, you **can** change `s[i]` to either `'('` or `')'`.
//
// Return `true` if you can make `s` a valid parentheses string. Otherwise, return `false`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/11/06/eg1.png
//
// ```
// Input: s = "))()))", locked = "010100"
// Output: true
// Explanation: locked[1] == '1' and locked[3] == '1', so we cannot change s[1] or s[3].
// We change s[0] and s[4] to '(' while leaving s[2] and s[5] unchanged to make s valid.```
//
// **Example 2:**
//
// ```
// Input: s = "()()", locked = "0000"
// Output: true
// Explanation: We do not need to make any changes because s is already valid.
// ```
//
// **Example 3:**
//
// ```
// Input: s = ")", locked = "0"
// Output: false
// Explanation: locked permits us to change s[0].
// Changing s[0] to either '(' or ')' will not make s valid.
// ```
//
// **Constraints:**
//
// - `n == s.length == locked.length`
// - `1 <= n <= 10^5`
// - `s[i]` is either `'('` or `')'`.
// - `locked[i]` is either `'0'` or `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import "fmt"

func canBeValid(s string, locked string) bool {
	n := len(s)

	// Not valid for odd string
	if n%2 == 1 {
		return false
	}

	// Mark free slots as `-`
	parens := []byte(s)
	for i := range n {
		if locked[i] == '0' {
			parens[i] = '-'
		}
	}

	// Scan left to right for `)`
FORWARD:
	for i, j, leftCount := 0, 0, 0; i < n; i++ {
		if parens[i] == '-' {
			continue
		}
		if parens[i] == '(' {
			leftCount++
			continue
		}

		// Use a locked `(`
		if leftCount > 0 {
			leftCount--
			continue
		}

		// Find free slot and make it `(`
		for ; j < i; j++ {
			if parens[j] == '-' {
				parens[j] = '('
				continue FORWARD
			}
		}
		return false
	}

	// Scan right to left for `(`
BACKWARD:
	for i, j, rightCount := n-1, n-1, 0; i >= 0; i-- {
		if parens[i] == '-' {
			continue
		}
		if parens[i] == ')' {
			rightCount++
			continue
		}

		// Use a locked `)`
		if rightCount > 0 {
			rightCount--
			continue
		}

		// Find free slot and make it `)`
		for ; j > i; j-- {
			if parens[j] == '-' {
				parens[j] = ')'
				continue BACKWARD
			}
		}
		return false
	}

	return true
}

// Forward loop, treat `0` and `(` as possible `(` and check balanceness
// Backward loop, treat `0` and `)` as possible `)` and check balanceness
//
// Note that we don't need to worry about if a free slot is used in both directions.
// Assume that a slot is used in both directions.
// Which means a `(` at left wants this slot to be `)`,
// and another `)` at right wants this slot to be `(`.
// However, in this case the left `(` and the right `)` are already balanced.
// Therefore this slot should be free.
func canBeValid2(s string, locked string) bool {
	n := len(s)

	// Not valid for odd string
	if n%2 == 1 {
		return false
	}

	// Forward loop, treat `0` and `(` as possible `(`
	freeCount := 0
	for i := range n {
		if locked[i] == '0' || s[i] == '(' {
			freeCount++
		} else if freeCount > 0 {
			freeCount--
		} else {
			return false
		}
	}

	// Backward loop, treat `0` and `)` as possible `)`
	freeCount = 0
	for i := n - 1; i >= 0; i-- {
		if locked[i] == '0' || s[i] == ')' {
			freeCount++
		} else if freeCount > 0 {
			freeCount--
		} else {
			return false
		}
	}

	return true
}

func main() {
	fmt.Println(canBeValid2("))()))", "010100"))
}
