// Source: https://leetcode.com/problems/find-the-count-of-good-integers
// Title: Find the Count of Good Integers
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two **positive** integers `n` and `k`.
//
// An integer `x` is called **k-palindromic** if:
//
// - `x` is a **palindrome**.
// - `x` is divisible by `k`.
//
// An integer is a **palindrome** when it reads the same forward and backward.
// For example, 121 is a palindrome while 123 is not.
//
// An integer is called **good** if its digits can be rearranged to form a **k-palindromic** integer. For example, for `k = 2`, 2020 can be rearranged to form the k-palindromic integer 2002, whereas 1010 cannot be rearranged to form a k-palindromic integer.
//
// Return the count of **good** integers containing `n` digits.
//
// **Note** that any integer must **not** have leading zeros, **neither** before **nor** after rearrangement. For example, 1010 cannot be rearranged to form 101.
//
// **Example 1:**
//
// ```
// Input: n = 3, k = 5
// Output: 27
// Explanation:
// Some of the good integers are:
// - 551 because it can be rearranged to form 515.
// - 525 because it is already k-palindromic.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1, k = 4
// Output: 2
// Explanation:
// The two good integers are 4 and 8.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 5, k = 6
// Output: 2468
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10`
// - `1 <= k <= 9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func countGoodIntegers(n int, k int) int64 {
	type digitsType [10]int // count of digits
	newDigits := func(num int) digitsType {
		var digits digitsType
		for range n {
			digits[num%10]++
			num /= 10
		}
		return digits
	}

	palindromics := make(map[digitsType]bool, 0)
	// Construct palindromic
	if n%2 == 0 {
		makePalindromic := func(upper int) int {
			num := upper
			for upper > 0 {
				num *= 10
				num += upper % 10
				upper /= 10
			}
			return num
		}

		start := 1
		for range n/2 - 1 {
			start *= 10
		}
		end := start * 10

		for upper := start; upper < end; upper++ {
			num := makePalindromic(upper)
			if num%k == 0 {
				palindromics[newDigits(num)] = true
			}
		}
	} else {
		makePalindromic := func(upper int) int {
			num := upper
			upper /= 10
			for upper > 0 {
				num *= 10
				num += upper % 10
				upper /= 10
			}
			return num
		}

		start := 1
		for range n / 2 {
			start *= 10
		}
		end := start * 10

		for upper := start; upper < end; upper++ {
			num := makePalindromic(upper)
			if num%k == 0 {
				palindromics[newDigits(num)] = true
			}
		}
	}

	factorials := []int64{1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800}
	res := int64(0)
	for pal := range palindromics {
		count := factorials[n-1] * int64(n-pal[0]) // first digit can't be zero
		for _, digitCount := range pal {
			count /= factorials[digitCount]
		}
		res += count
	}

	return res
}
