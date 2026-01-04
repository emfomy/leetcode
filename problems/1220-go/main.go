// Source: https://leetcode.com/problems/count-vowels-permutation
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Math, Eigen Decomposition in Finite Field
//
// Define the transition matrix
// A = [
// 0   1   1   0   1
// 1   0   1   0   0
// 0   1   0   1   0
// 0   0   1   0   0
// 0   0   1   1   0
// ]
//
// Find the eigen-system in Fp (p = 1e9+7)
// A = U * D * U^{-1}, U is the right eigenvectors
// Write e = (1, 1, 1, 1, 1), u = U' * e, v = U^{-1} * e
// The solution is
// e' * A^(n-1) * e
// = e' * U * D^(n-1) * U^{-1} * e
// = (U' * e)' * D^(n-1) * (U^{-1} * e)
// = u' * D^(n-1) * v
// = sum(u @ v @ d^(n-1)), where @ is element-wise product
// = sum(c @ d^(n-1)), Write c = (u @ v)
//
// Use sage:
//
// F = GF(1_000_000_007)
// A = Matrix(F, [...])
// e = vector(F, (1, 1, 1, 1, 1))
// d = A.eigenvalues()
// _, U = A.eigenmatrix_right()
// u = U.transpose() * e
// v = U.inverse() * e
// c = vector([a * b for a, b in zip(u, v)])
//
// d = (1000000006, 882979097, 653592850, 419376480, 44051588)
// U = [
//          1          1          1          1          1
//          0  515412670  273651538  907301038  303634775
// 1000000006  753268719  376306490  953281255  917143548
//          1  129710377  277286359  466095231  126908046
//          0  614297715    3634822  558794201  823273279
// ]
// u = (1, 12689468, 930879210, 885471712, 170959635)
// v = (0, 459873583, 779875704, 153844979, 606405749)
// c = (0, 74674987, 155923322, 984156423, 785245287)
//

func countVowelPermutation2(n int) int {
	return (74674987*_fastPow(882979097, n-1) +
		155923322*_fastPow(653592850, n-1) +
		984156423*_fastPow(419376480, n-1) +
		785245287*_fastPow(44051588, n-1)) % modulo
}

func countVowelPermutation3(n int) int {
	return (514029000*_fastPow(882979097, n) +
		638771916*_fastPow(653592850, n) +
		784439686*_fastPow(419376480, n) +
		62759413*_fastPow(44051588, n)) % modulo
}

func _fastPow(x int, n int) int {
	res := 1
	for n > 0 {
		if (n & 1) != 0 {
			res = (res * x) % modulo
		}
		n >>= 1
		x = (x * x) % modulo
	}
	return res
}
