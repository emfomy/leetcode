// Source: https://leetcode.com/problems/count-the-number-of-ideal-arrays
// Title: Count the Number of Ideal Arrays
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integers `n` and `maxValue`, which are used to describe an **ideal** array.
//
// A **0-indexed** integer array `arr` of length `n` is considered **ideal** if the following conditions hold:
//
// - Every `arr[i]` is a value from `1` to `maxValue`, for `0 <= i < n`.
// - Every `arr[i]` is divisible by `arr[i - 1]`, for `0 < i < n`.
//
// Return the number of **distinct** ideal arrays of length `n`. Since the answer may be very large, return it modulo `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: n = 2, maxValue = 5
// Output: 10
// Explanation: The following are the possible ideal arrays:
// - Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
// - Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
// - Arrays starting with the value 3 (1 array): [3,3]
// - Arrays starting with the value 4 (1 array): [4,4]
// - Arrays starting with the value 5 (1 array): [5,5]
// There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5, maxValue = 3
// Output: 11
// Explanation: The following are the possible ideal arrays:
// - Arrays starting with the value 1 (9 arrays):
//    - With no other distinct values (1 array): [1,1,1,1,1]
//    - With 2^nd distinct value 2 (4 arrays): [1,1,1,1,2], [1,1,1,2,2], [1,1,2,2,2], [1,2,2,2,2]
//    - With 2^nd distinct value 3 (4 arrays): [1,1,1,1,3], [1,1,1,3,3], [1,1,3,3,3], [1,3,3,3,3]
// - Arrays starting with the value 2 (1 array): [2,2,2,2,2]
// - Arrays starting with the value 3 (1 array): [3,3,3,3,3]
// There are a total of 9 + 1 + 1 = 11 distinct ideal arrays.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^4`
// - `1 <= maxValue <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Use Combination
//
// Loop for all possible end value and the prime factorization.
//
// Define P(v, p) to be the power of prime `p“ in the prime factorization of number `v“.
// Let [v1, v2, ..., vn] be an ideal array, and P(vi, p) = ki.
// Then 0 <= k1 <= k2 <= ... <= kn = k.
// Here we can easy to find out that with given `n` and `k`,
// there are H^n_k = C^(n+k-1)_k possible series [k1, ..., kn]
//
// Hence we can compute the possible ideal arrays end the number `v`
// by multiplying the combination numbers of all primes of `v`.

const (
	modulo = int(1e9 + 7)

	MAX_N     = 10000
	MAX_K     = 13
	MAX_VALUE = 10000
	MAX_COUNT = 6
)

var (
	minPrimes [MAX_VALUE + 1]int
	powers    [MAX_VALUE + 1][]int
	binoms    [MAX_N + MAX_K + 1][MAX_K + 1]int
)

func init() {
	// Find minimal prime of given number.
	for prime := 2; prime <= MAX_VALUE; prime++ {
		if minPrimes[prime] == 0 {
			for num := prime; num <= MAX_VALUE; num += prime {
				if minPrimes[num] == 0 {
					minPrimes[num] = prime
				}
			}
		}
	}

	// Find prime primePowers.
	// Note that we don't need the primes; we only need the powers.
	for num := 2; num <= MAX_VALUE; num++ {
		x := num
		for x > 1 {
			p := minPrimes[x]
			k := 0
			for x%p == 0 {
				x /= p
				k++
			}
			powers[num] = append(powers[num], k)
		}
	}

	// Find combination numbers
	binoms[0][0] = 1
	for i := 1; i < MAX_N+MAX_K; i++ {
		binoms[i][0] = 1
		for j := 1; j <= MAX_K && j <= i; j++ {
			binoms[i][j] = (binoms[i-1][j] + binoms[i-1][j-1]) % modulo
		}
	}
}

func idealArrays(n int, maxValue int) int {
	res := 0
	for num := 1; num <= maxValue; num++ {
		// compute combinations
		mul := 1
		for _, k := range powers[num] {
			mul *= binoms[n+k-1][k]
			mul %= modulo
		}
		res += mul
		res %= modulo
	}

	return res
}
