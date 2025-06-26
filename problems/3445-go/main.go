// Source: https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i
// Title: Maximum Difference Between Even and Odd Frequency II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` and an integer `k`. Your task is to find the **maximum** difference between the frequency of **two** characters, `freq[a] - freq[b]`, in a <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:rs:" data-state="closed" class="">substring</button> `subs` of `s`, such that:
//
// - `subs` has a size of **at least** `k`.
// - Character `a` has an odd frequency in `subs`.
// - Character `b` has an even frequency in `subs`.
//
// Return the **maximum** difference.
//
// **Note** that `subs` can contain more than 2 **distinct** characters.
//
// **Example 1:**
//
// ```
// Input: s = "12233", k = 4
// Output: -1
// Explanation:
// For the substring `"12233"`, the frequency of `'1'` is 1 and the frequency of `'3'` is 2. The difference is `1 - 2 = -1`.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "1122211", k = 3
// Output: 1
// Explanation:
// For the substring `"11222"`, the frequency of `'2'` is 3 and the frequency of `'1'` is 2. The difference is `3 - 2 = 1`.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "110", k = 3
// Output: -1
// ```
//
// **Constraints:**
//
// - `3 <= s.length <= 3 * 10^4`
// - `s` consists only of digits `'0'` to `'4'`.
// - The input is generated that at least one substring has a character with an even frequency and a character with an odd frequency.
// - `1 <= k <= s.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Let #(x, i) be the number of x in s[0:i) (left-inclusive, right-exclusive)
//
// Given a & b,
// freq(a) in s[i:j) is #(a, j) - #(a, i)
// freq(b) in s[i:j) is #(b, j) - #(b, i)
//
// We want to maximum:
// freq(a) - freq(b)
// = ( #(a, j) - #(a, i) ) - ( #(b, j) - #(b, i) )
// = ( #(a, j) - #(b, j) ) - ( #(a, i) - #(b, i) )
//
// Therefore, we only need to find the maximum & minimal value of difference:
// d(a, b, i) = #(a, i) - #(b, i)
//
// Note that we also have the parity constraint for a and b.
// There are 4 possible parity state of a & b.
// Let d(a, b, i) be the parity of #(a, i) and #(b, i).
// Case 0: d(a, b, j) = (odd, even),  d(a, b, i) = (even, even)
// Case 1: d(a, b, j) = (odd, odd),   d(a, b, i) = (even, odd)
// Case 2: d(a, b, j) = (even, even), d(a, b, i) = (odd, even)
// Case 3: d(a, b, j) = (even, odd),  d(a, b, i) = (odd, odd)
//
// Note that from now on, we fix one of the parity case for simplicity.
// In the real implementation, we use 4 extra space to store different parities.
//
// Finally, we use sliding window of size k to loop though the array.
// Say the window is [l:r), where l+k = r.
// We track the minimal of the left value: m(a, b, l) = min[i<=l] d(a, b, i)
//
// For each window, we compare the difference between the right value and m(a, b, l):
// d(a, b, r) - m(a, b, l)
// = d(a, b, r) - min[i<=l] d(a, b, i)
// = max[i<=l] d(a, b, r) - d(a, b, i)
//
// We maximum above difference:
// max[r] d(a, b, r) - m(a, b, l)
// max[r] max[i<=l] d(a, b, r) - d(a, b, i) // note that l+k = r
// max[r] max[i+k<=r] d(a, b, r) - d(a, b, i) // combine both max and rewrite j=r
// max[i+k <= j] d(a, b, r) - d(a, b, i)
//
// Now if we get the maximum frequency difference of a and b.
// Next max though all (a, b) pair, we obtain the answer.
func maxDifference(s string, k int) int {
	n := len(s)

	INF := int(1e5)

	// Prefix sum each characters
	preSum := make([][5]int, n+1) // preSum[x][i] be the number of x in s[0:i]
	for i := range n {
		preSum[i+1] = preSum[i]
		preSum[i+1][s[i]-'0']++
	}

	// Loop for all character combination
	ans := -INF
	for a := range 5 {
		for b := range 5 {
			if a == b {
				continue
			}

			// Min values for each parity
			minVals := [4]int{INF, INF, INF, INF}
			minBs := [4]int{} // avoid empty b

			// Loop
			for left := range n - k + 1 {
				leftA, leftB := preSum[left][a], preSum[left][b]
				leftVal := leftA - leftB
				leftParity := (leftA%2)*2 + (leftB % 2)

				if leftVal < minVals[leftParity] {
					minVals[leftParity] = leftVal
					minBs[leftParity] = leftB
				}

				right := left + k
				rightA, rightB := preSum[right][a], preSum[right][b]
				rightVal := rightA - rightB
				rightParity := (1-rightA%2)*2 + (rightB % 2) // here we need to flip the parity of a

				if minBs[rightParity] < rightB {
					ans = max(ans, rightVal-minVals[rightParity])
				}
			}
		}
	}

	return ans
}
