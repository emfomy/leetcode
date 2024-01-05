// Source: https://leetcode.com/problems/count-vowels-permutation/
// Title: Count Vowels Permutation
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer n, your task is to count how many strings of length n can be formed under the following rules:
//
//   Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
//   Each vowel 'a' may only be followed by an 'e'.
//   Each vowel 'e' may only be followed by an 'a' or an 'i'.
//   Each vowel 'i' may not be followed by another 'i'.
//   Each vowel 'o' may only be followed by an 'i' or a 'u'.
//   Each vowel 'u' may only be followed by an 'a'.
//
// Since the answer may be too large, return it modulo 10^9 + 7.
//
// Example 1:
//
//   Input: n = 1
//   Output: 5
//   Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
//
// Example 2:
//
//   Input: n = 2
//   Output: 10
//   Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
//
// Example 3:
//
//   Input: n = 5
//   Output: 68
//
// Constraints:
//   1 <= n <= 2 * 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

const modulo = int(1e9 + 7)

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
func countVowelPermutation(n int) int {
	aCount, eCount, iCount, oCount, uCount := 1, 1, 1, 1, 1

	for i := 1; i < n; i++ {
		aCount, eCount, iCount, oCount, uCount =
			(eCount+iCount+uCount)%modulo,
			(aCount+iCount)%modulo,
			(eCount+oCount)%modulo,
			(iCount)%modulo,
			(iCount+oCount)%modulo
	}

	return (aCount + eCount + iCount + oCount + uCount) % modulo
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Its an markov chain
// A = [
//
//	0   1   1   0   1
//	1   0   1   0   0
//	0   1   0   1   0
//	0   0   1   0   0
//	0   0   1   1   0
//
// ]
// Find eigen system of A in Zp where p = 1e9+7
func countVowelPermutation2(n int) int {
	return (62759413*_fastPow(44051588, n) +
		784439686*_fastPow(419376480, n) +
		638771916*_fastPow(653592850, n) +
		514029000*_fastPow(882979097, n)) % modulo
}

func _fastPow(x int, n int) int {
	res := 1
	for true {
		if (n & 1) != 0 {
			res = (res * x) % modulo
		}
		n >>= 1
		if n == 0 {
			break
		}
		x = (x * x) % modulo
	}
	return res
}

// func _fastPow(x int, n int) int {
// 	if n == 1 {
// 		return x
// 	}
// 	y := _fastPow(x, n/2)
// 	y2 := y * y % modulo
// 	if n&1 == 1 {
// 		return (x * y2) % modulo
// 	} else {
// 		return y2
// 	}
// }
