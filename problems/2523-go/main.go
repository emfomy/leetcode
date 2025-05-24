// Source: https://leetcode.com/problems/closest-prime-numbers-in-range
// Title: Closest Prime Numbers in Range
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two positive integers `left` and `right`, find the two integers `num1` and `num2` such that:
//
// - `left <= num1 < num2 <= right`.
// - Both `num1` and `num2` are **prime numbers**.
// - A **prime number** is a natural number greater than 1 with only two factors, 1 and itself.
// - `num2 - num1` is the **minimum** amongst all other pairs satisfying the above conditions.
//
// Return the positive integer array `ans = [num1, num2]`. If there are multiple pairs satisfying these conditions, return the one with the **smallest** `num1` value. If no such numbers exist, return `[-1, -1]`.
//
// **Example 1:**
//
// ```
// Input: left = 10, right = 19
// Output: [11,13]
// Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
// The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
// Since 11 is smaller than 17, we return the first pair.
// ```
//
// **Example 2:**
//
// ```
// Input: left = 4, right = 6
// Output: [-1,-1]
// Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.
// ```
//
// **Constraints:**
//
// - `1 <= left <= right <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func closestPrimes(left int, right int) []int {
	res := []int{-1, -1}
	minDiff := right - left + 1

	prime1 := _nextPrime(left, right)
	if prime1 == -1 {
		return res
	}
	for {
		prime2 := _nextPrime(prime1+1, right)
		if prime2 == -1 {
			return res
		}
		diff := prime2 - prime1
		if minDiff > diff {
			minDiff = diff
			res[0], res[1] = prime1, prime2
			if diff <= 2 {
				return res
			}
		}
		prime1 = prime2
	}
	return nil
}

func _nextPrime(left, right int) int {
	for num := left; num <= right; num++ {
		if _isPrime(num) {
			return num
		}
	}
	return -1
}

func _isPrime(num int) bool {
	if num < 2 {
		return false
	}
	if num == 2 || num == 3 {
		return true
	}
	if num%2 == 0 {
		return false
	}

	for i := 3; i*i <= num; i += 2 {
		if num%i == 0 {
			return false
		}
	}
	return true
}
