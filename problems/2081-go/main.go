// Source: https://leetcode.com/problems/sum-of-k-mirror-numbers
// Title: Sum of k-Mirror Numbers
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **k-mirror number** is a **positive** integer **without leading zeros** that reads the same both forward and backward in base-10 **as well as** in base-k.
//
// - For example, `9` is a 2-mirror number. The representation of `9` in base-10 and base-2 are `9` and `1001` respectively, which read the same both forward and backward.
// - On the contrary, `4` is not a 2-mirror number. The representation of `4` in base-2 is `100`, which does not read the same both forward and backward.
//
// Given the base `k` and the number `n`, return the **sum** of the `n` **smallest** k-mirror numbers.
//
// **Example 1:**
//
// ```
// Input: k = 2, n = 5
// Output: 25
// **Explanation:
// **The 5 smallest 2-mirror numbers and their representations in base-2 are listed as follows:
//   base-10    base-2
//     1          1
//     3          11
//     5          101
//     7          111
//     9          1001
// Their sum = 1 + 3 + 5 + 7 + 9 = 25.
// ```
//
// **Example 2:**
//
// ```
// Input: k = 3, n = 7
// Output: 499
// **Explanation:
// **The 7 smallest 3-mirror numbers are and their representations in base-3 are listed as follows:
//   base-10    base-3
//     1          1
//     2          2
//     4          11
//     8          22
//     121        11111
//     151        12121
//     212        21212
// Their sum = 1 + 2 + 4 + 8 + 121 + 151 + 212 = 499.
// ```
//
// **Example 3:**
//
// ```
// Input: k = 7, n = 17
// Output: 20379000
// Explanation: The 17 smallest 7-mirror numbers are:
// 1, 2, 3, 4, 5, 6, 8, 121, 171, 242, 292, 16561, 65656, 2137312, 4602064, 6597956, 6958596
// ```
//
// **Constraints:**
//
// - `2 <= k <= 9`
// - `1 <= n <= 30`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func kMirror(k int, n int) int64 {
	k64 := int64(k)

	palindrome10 := func(upper int64, isOdd bool) int64 {
		num := upper
		if isOdd {
			upper /= 10
		}
		for upper > 0 {
			num *= 10
			num += upper % 10
			upper /= 10
		}
		return num
	}

	checkPalindromeK := func(num int64) bool {
		if num%k64 == 0 {
			return false
		}
		inv := int64(0)
		for num > inv {
			inv *= k64
			inv += num % k64
			if num == inv {
				return true
			}
			num /= k64
			if num == inv {
				return true
			}
		}
		return false
	}

	tenfolds := []int64{1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12, 1e13, 1e14, 1e15}
	count := 0
	ans := int64(0)
LOOP:
	for _, start := range tenfolds {
		for _, isOdd := range []bool{true, false} {
			for upper := start; upper < 10*start; upper++ {
				num := palindrome10(upper, isOdd)
				if checkPalindromeK(num) {
					ans += num
					count++
					if count >= n {
						break LOOP
					}
				}
			}
		}
	}

	return ans
}

func kMirror2(k int, n int) int64 {
	ans := [][]int64{
		nil,
		nil,
		{1, 3, 5, 7, 9, 33, 99, 313, 585, 717, 7447, 9009, 15351, 32223, 39993, 53235, 53835, 73737, 585585, 1758571, 1934391, 1979791, 3129213, 5071705, 5259525, 5841485, 13500531, 719848917, 910373019, 939474939},
		{1, 2, 4, 8, 121, 151, 212, 242, 484, 656, 757, 29092, 48884, 74647, 75457, 76267, 92929, 93739, 848848, 1521251, 2985892, 4022204, 4219124, 4251524, 4287824, 5737375, 7875787, 7949497, 27711772, 83155138},
		{1, 2, 3, 5, 55, 373, 393, 666, 787, 939, 7997, 53235, 55255, 55655, 57675, 506605, 1801081, 2215122, 3826283, 3866683, 5051505, 5226225, 5259525, 5297925, 5614165, 5679765, 53822835, 623010326, 954656459, 51717171715},
		{1, 2, 3, 4, 6, 88, 252, 282, 626, 676, 1221, 15751, 18881, 10088001, 10400401, 27711772, 30322303, 47633674, 65977956, 808656808, 831333138, 831868138, 836131638, 836181638, 2512882152, 2596886952, 2893553982, 6761551676, 12114741121, 12185058121},
		{1, 2, 3, 4, 5, 7, 55, 111, 141, 191, 343, 434, 777, 868, 1441, 7667, 7777, 22022, 39893, 74647, 168861, 808808, 909909, 1867681, 3097903, 4232324, 4265624, 4298924, 4516154, 4565654},
		{1, 2, 3, 4, 5, 6, 8, 121, 171, 242, 292, 16561, 65656, 2137312, 4602064, 6597956, 6958596, 9470749, 61255216, 230474032, 466828664, 485494584, 638828836, 657494756, 858474858, 25699499652, 40130703104, 45862226854, 61454945416, 64454545446},
		{1, 2, 3, 4, 5, 6, 7, 9, 121, 292, 333, 373, 414, 585, 3663, 8778, 13131, 13331, 26462, 26662, 30103, 30303, 207702, 628826, 660066, 1496941, 1935391, 1970791, 4198914, 55366355},
		{1, 2, 3, 4, 5, 6, 7, 8, 191, 282, 373, 464, 555, 646, 656, 6886, 25752, 27472, 42324, 50605, 626626, 1540451, 1713171, 1721271, 1828281, 1877781, 1885881, 2401042, 2434342, 2442442},
	}

	sum := int64(0)
	for _, num := range ans[k][:n] {
		sum += num
	}
	return sum
}
