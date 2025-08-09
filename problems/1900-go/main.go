// Source: https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete
// Title: The Earliest and Latest Rounds Where Players Compete
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a tournament where `n` players are participating. The players are standing in a single row and are numbered from `1` to `n` based on their **initial** standing position (player `1` is the first player in the row, player `2` is the second player in the row, etc.).
//
// The tournament consists of multiple rounds (starting from round number `1`). In each round, the `i^th` player from the front of the row competes against the `i^th` player from the end of the row, and the winner advances to the next round. When the number of players is odd for the current round, the player in the middle automatically advances to the next round.
//
// - For example, if the row consists of players `1, 2, 4, 6, 7`
//
// - Player `1` competes against player `7`.
// - Player `2` competes against player `6`.
// - Player `4` automatically advances to the next round.
//
// After each round is over, the winners are lined back up in the row based on the **original ordering** assigned to them initially (ascending order).
//
// The players numbered `firstPlayer` and `secondPlayer` are the best in the tournament. They can win against any other player before they compete against each other. If any two other players compete against each other, either of them might win, and thus you may **choose** the outcome of this round.
//
// Given the integers `n`, `firstPlayer`, and `secondPlayer`, return an integer array containing two values, the **earliest** possible round number and the**latest** possible round number in which these two players will compete against each other, respectively.
//
// **Example 1:**
//
// ```
// Input: n = 11, firstPlayer = 2, secondPlayer = 4
// Output: [3,4]
// Explanation:
// One possible scenario which leads to the earliest round number:
// First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
// Second round: 2, 3, 4, 5, 6, 11
// Third round: 2, 3, 4
// One possible scenario which leads to the latest round number:
// First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
// Second round: 1, 2, 3, 4, 5, 6
// Third round: 1, 2, 4
// Fourth round: 2, 4
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5, firstPlayer = 1, secondPlayer = 5
// Output: [1,1]
// Explanation: The players numbered 1 and 5 compete in the first round.
// There is no way to make them compete in any other round.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 28`
// - `1 <= firstPlayer < secondPlayer <= n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

// Backtracking + DP
//
// Say these two players are p & q. (zero based index)
// Denote S(n, p, q) as the state.
//
// Notice that if we reverse all players, the result is the same.
// That is, S(n, p, q) = S(n, n-q, n-p).
// Therefore, WLOG, we may assume that p < n/2.
// Now we only need to consider two cases: q <= n/2 or q > n/2
// Note that
//
// Case 1: q <= n/2
// Let d = q-p.
// Notice that after a round, the index of p & q & d won't increase.
// We loop though p' in [0, p] and d' in [1, d]. Let q' = p'+d'.
//
// Case 2: q > n/2
// Let r = n-q.
// Note that since we can reverse all players, we may assume p < r.
// We loop though p' in [0, p] and d' in [1, d]. Let r' = p'+d' and q' = r' + (n/2-r)
func earliestAndLatest(n int, firstPlayer int, secondPlayer int) []int {
	minDp := make(map[[3]int]int)
	maxDp := make(map[[3]int]int)

	var dp func(n int, p, q int) (int, int)
	dp = func(n, p, q int) (int, int) {
		state := [3]int{n, p, q}

		if minDp[state] > 0 {
			return minDp[state], maxDp[state]
		}

		if p+q == n+1 {
			return 1, 1
		}

		if p+q > n+1 {
			x, y := dp(n, n+1-q, n+1-p)
			minDp[state], maxDp[state] = x, y
			return x, y
		}

		x, y := 10, 0        // earliest & latest
		nHalf := (n + 1) / 2 // half
		if q <= nHalf {
			d := q - p
			for p2 := 1; p2 <= p; p2++ {
				for d2 := 1; d2 <= d; d2++ {
					x2, y2 := dp(nHalf, p2, p2+d2)
					x = min(x, x2)
					y = max(y, y2)
				}
			}
		} else {
			r := n + 1 - q
			d := r - p
			for p2 := 1; p2 <= p; p2++ {
				for d2 := 1; d2 <= d; d2++ {
					x2, y2 := dp(nHalf, p2, p2+d2+nHalf-r)
					x = min(x, x2)
					y = max(y, y2)
				}
			}
		}

		minDp[state], maxDp[state] = x+1, y+1
		return x + 1, y + 1
	}

	x, y := dp(n, firstPlayer, secondPlayer)
	return []int{x, y}
}
